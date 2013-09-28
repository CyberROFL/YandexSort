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

#include <vector>

static void generate(
    size_t const& file_size,
    size_t const& mem_limit,
    std::string const& to_file)
{
    // convert all sizes to ints
    size_t const _file_size = file_size / sizeof(int);
    size_t const _mem_limit = mem_limit / sizeof(int);

    std::ofstream ofstream;

    ofstream.open(to_file.c_str(), std::fstream::binary);

    // use current time as seed for random generator
    std::srand(static_cast<unsigned int>(std::time(0)));

    std::vector<int> chunk(std::min(_file_size, _mem_limit));

    for (size_t s = 0; s < file_size; )
    {
        for (std::vector<int>::iterator it = chunk.begin();
             it != chunk.end(); ++it)
        {
            *it = std::rand();
        }

        ofstream.write(reinterpret_cast<char*>(&chunk[0]), chunk.size());

        s += chunk.size();

        if ((_file_size - s) > 0 && (_file_size - s) < chunk.size())
        {
            chunk.resize(_file_size - s);
        }
    }

    // opened file is automatically closed when the ofstream object is destroyed
}

static void sort(
    size_t const& mem_limit,
    std::string const& from_file,
    std::string const& to_file)
{
    std::ifstream ifstream;
    std::ofstream ofstream;

    ifstream.open(from_file.c_str(), std::fstream::binary);
    ofstream.open(to_file.c_str(), std::fstream::binary);

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
