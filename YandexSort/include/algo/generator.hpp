/*
    @author Ilnaz Nizametdinov (c)

    @project YandexSort

    @description
        Implementation of generator.
 */

#ifndef __ALGO_GENERATOR_HPP__
#define __ALGO_GENERATOR_HPP__

#include <cstdlib> // for random generator
#include <ctime>

#include <algo/chunk.hpp>

template<class T>
class generator
{
public:
    generator(size_t const& file_size, size_t const& mem_limit) :

        _file_size(file_size / sizeof(T)),
        _mem_limit(mem_limit / sizeof(T))
    {
        // use current time as seed for random generator
        std::srand(unsigned(std::time(0)));
    }

    inline void generate(std::string const& to_file)
    {
        std::fstream ofstream;

        ofstream.open(to_file.c_str(), std::ios::out | std::ios::binary);
        if (!ofstream)
            throw std::exception("Cannot open gen-file");

        generate(ofstream);
    }

    inline void generate(std::fstream& to_stream)
    {
        chunk<T> chunk_(std::min(_file_size, _mem_limit));

        for (size_t s = 0; s < _file_size; s += chunk_.size())
        {
            // additional check for last chunk
            if ((_file_size - s) < chunk_.size())
                chunk_.resize(_file_size - s);

            // fill chunk with std::rand() values
            std::generate(chunk_.begin(), chunk_.end(), std::rand);

            // write chunk to stream
            chunk_.write(to_stream);
        }
    }

private:
    size_t _file_size;
    size_t _mem_limit;

}; // class generator

#endif // __ALGO_GENERATOR_HPP__
