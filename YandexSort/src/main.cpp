/*
    @author Ilnaz Nizametdinov (c)

    @project YandexSort

    @description
        Application entry point.
 */

#include <pch.h>

#include <algo/generator.hpp>

int main(int argc, char* argv[])
{
    typedef int value_type;

    // Restrictions
    const size_t file_size = 1 << 30; // 1G
    const size_t mem_limit = 100 * (1 << 20); // 100M

    assert (0 == (file_size % sizeof(value_type)));
    assert (0 == (mem_limit % sizeof(value_type)));

    generator<value_type> gen(file_size, mem_limit);
    gen.generate(argv[1]);

	return 0;
}

// static void sort(
//     size_t const& mem_limit,
//     std::string const& from_file,
//     std::string const& to_file)
// {
//     std::ifstream ifstream;
//     std::ofstream ofstream;
// 
//     ifstream.open(from_file.c_str(), std::fstream::binary);
//     ofstream.open(to_file.c_str(), std::fstream::binary);
// 
//     ifstream.seekg(0, ifstream.end);
//     size_t file_size = ifstream.tellg();
//     ifstream.seekg(0, ifstream.beg);
// 
//     size_t chunk_size = std::min(file_size, mem_limit);
//     char*  chunk      = new char[chunk_size];
// 
//     for (size_t s = 0; s < file_size; )
//     {
//         int* int_chunk = reinterpret_cast<int*>(chunk);
// 
//         ifstream.read(chunk, chunk_size);
// 
//         std::sort(int_chunk, int_chunk + (chunk_size / sizeof(int)));
// 
//         ofstream.write(chunk, chunk_size);
// 
//         s += chunk_size;
// 
//         if ((file_size - s) > 0 && (file_size - s) < chunk_size)
//         {
//             chunk_size = file_size - s;
//             delete[] chunk;
//             chunk = new char[chunk_size];
//         }
//     }
// 
//     delete[] chunk;
// 
//     // opened files are automatically closed when the ofstream object is destroyed
// }
