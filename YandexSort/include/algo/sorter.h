/*
    @author Ilnaz Nizametdinov (c)

    @project YandexSort

    @description
        Implementation of sorter.
 */

#ifndef __ALGO_SORTER_HPP__
#define __ALGO_SORTER_HPP__

#include <cstdio>

template<class T>
class sorter
{
public:
    sorter(size_t const& mem_limit) : _mem_limit(mem_limit / sizeof(T))
    {}

    inline void sort(std::istream& from, std::ostream& to)
    {
        std::vector<std::string> chunk_names;

        make_sorted_chunks(from, chunk_names);
    }

    inline void sort(std::string const& from, std::string const& to)
    {
        std::ifstream ifstream;
        std::ofstream ofstream;

        ifstream.open(from.c_str(), std::fstream::binary);
        ofstream.open(to.c_str(), std::fstream::binary);

        sort(ifstream, ofstream);

        // files are automatically closed when the ofstream objects are destroyed
    }

protected:
    inline size_t make_sorted_chunks(std::istream& from, std::vector<std::string>& chunk_names)
    {
        size_t file_size = stream_size(from) / sizeof(T);
        std::vector<T> chunk(std::min(file_size, _mem_limit));

        for (size_t s = 0; s < file_size; s += chunk.size())
        {
            // additional check for last chunk
            if ((file_size - s) < chunk.size())
            {
                chunk.resize(file_size - s);
            }

            from.read(reinterpret_cast<char*>(&chunk[0]), chunk.size() * sizeof(T));

            std::sort(chunk.begin(), chunk.end());

            // write each chunk into a separate temporary file
            chunk_names.push_back(tmpnam(NULL));

            std::ofstream to;
            to.open(chunk_names.back().c_str(), std::fstream::binary);

            to.write(reinterpret_cast<char*>(&chunk[0]), chunk.size() * sizeof(T));
        }

        return chunk_names.size();
    }

private:
    size_t _mem_limit;

    inline static size_t stream_size(std::istream& stream)
    {
        // remember pos
        std::istream::pos_type pos = stream.tellg();

        stream.seekg(0, stream.end);
        size_t size = stream.tellg();

        // restore pos
        stream.seekg(pos);

        return size;
    }

//     inline void merge(std::istream& from1, std::istream& from2, std::ostream& to)
//     {
//         size_t size1 = stream_size(from1) / sizeof(T);
//         size_t size2 = stream_size(from2) / sizeof(T);
//         size_t size  = std::max(size1, size2);
// 
//         std::vector<T> chunk1(std::min(size1, _mem_limit) / 4);
//         std::vector<T> chunk2(std::min(size2, _mem_limit) / 4);
//         std::vector<T> chunk (std::min(size,  _mem_limit) / 2);
// 
//         for (size_t c = 0; c < 4; ++c)
//         {
//             from1.read(reinterpret_cast<char*>(&chunk1[0]), chunk1.size() * sizeof(T));
//             from2.read(reinterpret_cast<char*>(&chunk2[0]), chunk2.size() * sizeof(T));
// 
//             std::merge(chunk1.begin(), chunk1.end(), chunk2.begin(), chunk2.end(), chunk.begin());
//             to.write(reinterpret_cast<char*>(&chunk[0]), chunk.size() * sizeof(T));
//         }
//     }
//     inline void merge(std::string const& from1, std::string const& from2, std::string const& to)
//     {
//         std::ifstream ifstream1, ifstream2;
//         std::ofstream ofstream;
// 
//         ifstream1.open(from1.c_str(), std::fstream::binary);
//         ifstream2.open(from2.c_str(), std::fstream::binary);
//         ofstream.open(to.c_str(), std::fstream::binary);
// 
//         merge(ifstream1, ifstream2, ofstream);
//     }

}; // class sorter

#endif // __ALGO_SORTER_HPP__
