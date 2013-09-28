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

template<class T>
class generator
{
    size_t _file_size;
    size_t _mem_limit;

public:
    generator(size_t const& file_size, size_t const& mem_limit) :

        _file_size(file_size / sizeof(T)),
        _mem_limit(mem_limit / sizeof(T))
    {
        // use current time as seed for random generator
        std::srand(unsigned(std::time(0)));
    }

    inline void generate(std::ostream& to)
    {
        std::vector<T> chunk(std::min(_file_size, _mem_limit));

        for (size_t s = 0; s < _file_size; s += chunk.size())
        {
            if (0 < (_file_size - s) && (_file_size - s) < chunk.size())
            {
                chunk.resize(_file_size - s);
            }

            std::generate(chunk.begin(), chunk.end(), std::rand);

            to.write(reinterpret_cast<char*>(&chunk[0]), chunk.size() * sizeof(T));
        }
    }

    inline void generate(std::string const& to)
    {
        std::ofstream ofstream;
        ofstream.open(to.c_str(), std::fstream::binary);

        generate(ofstream);
    }
};

#endif // __ALGO_GENERATOR_HPP__
