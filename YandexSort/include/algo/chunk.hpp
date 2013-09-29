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
public:
    chunk(size_t const& size) : std::vector<T>(size)
    {}

    inline std::fstream& read(std::fstream& fstream)
    {
        fstream.read(reinterpret_cast<char*>(&(operator[](0))), size() * sizeof(T));
        return fstream;
    }

    inline std::fstream& write(std::fstream& fstream)
    {
        fstream.write(reinterpret_cast<char*>(&(operator[](0))), size() * sizeof(T));
        return fstream;
    }

}; // class chunk

#endif // __ALGO_CHUNK_HPP__
