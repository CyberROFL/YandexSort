/*
    @author Ilnaz Nizametdinov (c)

    @project YandexSort

    @description
        Application entry point.
 */

#include <pch.h>

#include <iostream>
#include <fstream>
#include <string>

#include <algorithm>

#include <cstdlib>
#include <ctime>

#include <cassert>

static void generate(
    size_t const& file_size,
    size_t const& mem_limit,
    std::string const& to_file)
{
    std::ofstream ofstream;

    ofstream.open(to_file.c_str(), std::ofstream::binary);

    // use current time as seed for random generator
    std::srand(static_cast<unsigned int>(std::time(0)));

    size_t chunk_size = std::min(file_size, mem_limit) / sizeof(int);
    int* chunk = new int[chunk_size];

    for (size_t s = 0; s < file_size; )
    {
        for (size_t i = 0; i < chunk_size; ++i)
            chunk[i] = std::rand();

        ofstream.write(reinterpret_cast<char*>(chunk), chunk_size * sizeof(int));

        s += chunk_size * sizeof(int);

        if ((file_size - s) > 0 && (file_size - s) < chunk_size * sizeof(int))
        {
            chunk_size = (file_size - s) / sizeof(int);
            delete[] chunk;
            chunk = new int[chunk_size];
        }
    }

    delete[] chunk;

    // open file is automatically closed when the ofstream object is destroyed
}

int main(int argc, char* argv[])
{
    // Restrictions
    const size_t file_size = 1 << 30; // 1G
    const size_t mem_limit = 100 * (1 << 20); // 100M

    generate(file_size, mem_limit, argv[1]);

	return 0;
}
