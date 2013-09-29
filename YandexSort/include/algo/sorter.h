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

        ifstream.open(from_file.c_str(), std::ios::in | std::fstream::binary);
        ofstream.open(to_file.c_str(),  std::ios::out | std::fstream::binary);

        sort(ifstream, ofstream);

        // files are automatically closed when the fstream objects are destroyed
    }

    inline void sort(std::fstream& from_stream, std::fstream& to_stream)
    {
        std::vector<std::string> chunk_names;

        make_sorted_chunks (from_stream, chunk_names);
        merge_sorted_chunks(chunk_names, to_stream);
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
            // additional check for last chunk
            if ((file_size - s) < chunk_.size())
            {
                chunk_.resize(file_size - s);
            }

            chunk_.read(from_stream);

            std::sort(chunk_.begin(), chunk_.end());

            // write each chunk into a separate temporary file
            chunk_names.push_back(tmpnam(NULL));

            std::fstream to_stream;
            to_stream.open(chunk_names.back().c_str(), std::ios::out | std::fstream::binary);

            chunk_.write(to_stream);
        }
    }

    inline void merge_sorted_chunks(
        std::vector<std::string>& chunk_names,
        std::fstream& to_stream)
    {
        if (1 == chunk_names.size())
        {
            std::fstream from;
            from.open(chunk_names[0].c_str(), std::ios::in | std::fstream::binary);

            to_stream << from.rdbuf();
        }
        else
        {
            // +1 for output chunk
            size_t chunk_size = _mem_limit / (chunk_names.size() + 1);

            typedef std::vector<chunk<T> > chunks;

            chunks chunks_(chunk_names.size() + 1, chunk<T>(chunk_size));

            for (chunks::iterator it = chunks_.begin(), end = chunks_.end();
                 it != end; ++it)
            {
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
