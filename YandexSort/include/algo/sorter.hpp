/*
    @author Ilnaz Nizametdinov (c)

    @project YandexSort

    @description
        Implementation of sorter.
 */

#ifndef __ALGO_SORTER_HPP__
#define __ALGO_SORTER_HPP__

#include <algo/chunk.hpp>

template<class T>
class sorter
{
public:
    sorter(size_t const& mem_limit) : _mem_limit(mem_limit / sizeof(T))
    {}

    inline void sort(std::string const& from_file, std::string const& to_file)
    {
        std::fstream ifstream;
        std::fstream ofstream;

        ifstream.open(from_file.c_str(), std::ios::in | std::ios::binary);
        if (!ifstream)
            throw std::exception("Cannot open gen-file");

        ofstream.open(to_file.c_str(),  std::ios::out | std::ios::binary);
        if (!ofstream)
            throw std::exception("Cannot open sorted-file");

        sort(ifstream, ofstream);
    }

    inline void sort(std::fstream& from_stream, std::fstream& to_stream)
    {
        std::vector<std::string> chunk_names;

        make_sorted_chunks(from_stream, chunk_names);
        n_way_merge(chunk_names, to_stream);
    }

private:
    inline void make_sorted_chunks(
        std::fstream& from_stream,
        std::vector<std::string>& chunk_names)
    {
        size_t file_size = stream_size(from_stream) / sizeof(T);
        chunk<T> chunk_(std::min(file_size, _mem_limit));

        for (size_t s = 0; s < file_size; s += chunk_.size())
        {
            chunk_.read(from_stream);

            // in-memory sort chunk
            std::sort(chunk_.begin(), chunk_.end());

            // write each chunk into a separate temporary file
            chunk_names.push_back(tmpnam(NULL));

            std::fstream to_stream;
            to_stream.open(chunk_names.back().c_str(), std::ios::out | std::ios::binary);

            chunk_.write(to_stream);
        }
    }

    inline void n_way_merge(
        std::vector<std::string>& chunk_names,
        std::fstream& to_stream)
    {
        if (1 == chunk_names.size())
        {
            std::fstream from;
            from.open(chunk_names[0].c_str(), std::ios::in | std::ios::binary);

            to_stream << from.rdbuf();
        }
        else
        {
            typedef std::pair<T, size_t> value_index;
            typedef std::priority_queue<
                value_index,
                std::vector<value_index>,
                std::greater<value_index> > helper_queue;

            size_t const n_chunks   = chunk_names.size();
            size_t const chunk_size = _mem_limit / (n_chunks + 1); // +1 for out

            // It is better to use some smart pointer... but I cannot use boost
            // and VS 2008 does not support C++11
            std::vector<std::fstream*> streams(n_chunks);
            std::vector<chunk<T> > chunks(n_chunks, chunk<T>(chunk_size));

            helper_queue queue;
            chunk<T> out_chunk;

            // initialize
            for (size_t i = 0; i < n_chunks; ++i)
            {
                streams[i] = new std::fstream;
                streams[i]->open(chunk_names[i].c_str(), std::ios::in | std::ios::binary);

                chunks[i].read(*streams[i]);
                queue.push(std::make_pair(chunks[i].pop_front(), i));
            }

            while (!queue.empty())
            {
                if (chunk_size == out_chunk.size())
                {
                    out_chunk.write(to_stream);
                    chunk<T>().swap(out_chunk); // force clear
                }

                size_t index = queue.top().second; // chunk index

                out_chunk.push_back(queue.top().first); // add chunk value to out
                queue.pop(); // pop from queue

                bool can_push = true;

                if (chunks[index].empty())
                {
                    // clear & read next portion
                    chunks[index].clear();
                    can_push = chunks[index].read(*streams[index]);
                }

                // is there a new data to be pushed?
                if (can_push)
                    queue.push(std::make_pair(chunks[index].pop_front(), index));
            }

            // save unwritten data
            if (!out_chunk.empty())
                out_chunk.write(to_stream);

            // cleanup
            for (size_t i = 0; i < n_chunks; ++i)
            {
                delete streams[i];
                std::remove(chunk_names[i].c_str());
            }
        }
    }

    inline static size_t stream_size(std::fstream& stream)
    {
        // remember pos
        std::fstream::pos_type pos = stream.tellg();

        stream.seekg(0, stream.end);
        size_t size = stream.tellg();

        // restore pos
        stream.seekg(pos);

        return size;
    }

private:
    size_t _mem_limit;

}; // class sorter

#endif // __ALGO_SORTER_HPP__
