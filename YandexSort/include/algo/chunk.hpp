/*
    @author Ilnaz Nizametdinov (c)

    @project YandexSort

    @description
        Implementation of chunk.
 */

#ifndef __ALGO_CHUNK_HPP__
#define __ALGO_CHUNK_HPP__

template<class T>
class chunk : public std::vector<T>
{
    size_t _index;

public:
    chunk() : std::vector<T>(), _index(0)
    {}

    chunk(size_t const& size) : std::vector<T>(size), _index(0)
    {}

    inline bool read(std::fstream& fstream)
    {
        fstream.read(reinterpret_cast<char*>(&(operator[](0))), size() * sizeof(T));

        if (!fstream)
        {
            size_t gc = fstream.gcount() / sizeof(T);

            if (0 != gc)
            {
                resize(gc);
                read(fstream);

                return true;
            }
        }

        return !!fstream;
    }

    inline bool write(std::fstream& fstream)
    {
        fstream.write(reinterpret_cast<char*>(&(operator[](0))), size() * sizeof(T));
        return !!fstream;
    }

    // pop_front emulation
    inline T& pop_front()
    {
        return operator[](_index++);
    }

    inline bool emptyIndex()
    {
        return (_index == size());
    }

    inline void clearIndex()
    {
        _index = 0;
    }

}; // class chunk

#endif // __ALGO_CHUNK_HPP__
