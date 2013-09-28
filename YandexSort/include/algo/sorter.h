/*
    @author Ilnaz Nizametdinov (c)

    @project YandexSort

    @description
        Implementation of sorter.
 */

#ifndef __ALGO_SORTER_HPP__
#define __ALGO_SORTER_HPP__

template<class T>
class sorter
{
    size_t _mem_limit;

    inline static size_t stream_size(std::istream& stream)
    {
        std::istream::pos_type pos = stream.tellg(); // remember pos

        stream.seekg(0, stream.end);
        size_t size = stream.tellg();

        stream.seekg(pos); // restore pos

        return size;
    }

public:
    sorter(size_t const& mem_limit) : _mem_limit(mem_limit / sizeof(T))
    {}

    inline void sort(std::istream& from, std::ostream& to)
    {
        size_t file_size = stream_size(from) / sizeof(T);

        std::vector<T> chunk(std::min(file_size, _mem_limit));
    
        for (size_t s = 0; s < file_size; s += chunk.size())
        {
            if (0 < (file_size - s) && (file_size - s) < chunk.size())
            {
                chunk.resize(file_size - s);
            }

            from.read(reinterpret_cast<char*>(&chunk[0]), chunk.size() * sizeof(T));

            std::sort(chunk.begin(), chunk.end());

            to.write(reinterpret_cast<char*>(&chunk[0]), chunk.size() * sizeof(T));
        }
    }

    inline void sort(std::string const& from, std::string const& to)
    {
        std::ifstream ifstream;
        std::ofstream ofstream;

        ifstream.open(from.c_str(), std::fstream::binary);
        ofstream.open(to.c_str(), std::fstream::binary);

        sort(ifstream, ofstream);
    }
};

#endif // __ALGO_SORTER_HPP__
