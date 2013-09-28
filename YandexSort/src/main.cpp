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

    size_t chunk_size = std::min(file_size, mem_limit);
    char*  chunk      = new char[chunk_size];

    for (size_t s = 0; s < file_size; )
    {
        int* int_chunk = reinterpret_cast<int*>(chunk);

        for (size_t i = 0; i < chunk_size / sizeof(int); ++i)
            int_chunk[i] = std::rand();

        ofstream.write(chunk, chunk_size);

        s += chunk_size;

        if ((file_size - s) > 0 && (file_size - s) < chunk_size)
        {
            chunk_size = file_size - s;
            delete[] chunk;
            chunk = new char[chunk_size];
        }
    }

    delete[] chunk;

    // opened file is automatically closed when the ofstream object is destroyed
}

static void sort(
    size_t const& mem_limit,
    std::string const& from_file,
    std::string const& to_file)
{
    std::ifstream ifstream;
    std::ofstream ofstream;

    ifstream.open(from_file.c_str(), std::ifstream::binary);
    ofstream.open(to_file.c_str(), std::ofstream::binary);

    ifstream.seekg(0, ifstream.end);
    size_t file_size = ifstream.tellg();
    ifstream.seekg(0, ifstream.beg);

    size_t chunk_size = std::min(file_size, mem_limit);
    char*  chunk      = new char[chunk_size];

    for (size_t s = 0; s < file_size; )
    {
        int* int_chunk = reinterpret_cast<int*>(chunk);

        ifstream.read(chunk, chunk_size);

        std::sort(int_chunk, int_chunk + (chunk_size / sizeof(int)));

        ofstream.write(chunk, chunk_size);

        s += chunk_size;

        if ((file_size - s) > 0 && (file_size - s) < chunk_size)
        {
            chunk_size = file_size - s;
            delete[] chunk;
            chunk = new char[chunk_size];
        }
    }

    delete[] chunk;

    // opened files are automatically closed when the ofstream object is destroyed
}

int main(int argc, char* argv[])
{
    // Restrictions
//     const size_t file_size = 1 << 30; // 1G
//     const size_t mem_limit = 100 * (1 << 20); // 100M
    const size_t file_size = 1024;
    const size_t mem_limit = 1024;

    assert (0 == (file_size % sizeof(int)));
    assert (0 == (mem_limit % sizeof(int)));

    generate(file_size, mem_limit, argv[1]);
    sort(mem_limit, argv[1], argv[2]);

	return 0;
}
