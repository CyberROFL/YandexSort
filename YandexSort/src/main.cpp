/*
    @author Ilnaz Nizametdinov (c)

    @project YandexSort

    @description
        Application entry point.
 */

#include <pch.h>

#include <algo/generator.hpp>
#include <algo/sorter.h>

int main(int argc, char* argv[])
{
    typedef int value_type;

    // Restrictions
//     const size_t file_size = 1 << 30; // 1G
//     const size_t mem_limit = 100 * (1 << 20); // 100M
    const size_t file_size = 128;
    const size_t mem_limit = 32;

    assert (0 != file_size);
    assert (0 != mem_limit);

    assert (0 == (file_size % sizeof(value_type)));
    assert (0 == (mem_limit % sizeof(value_type)));

    try
    {
        if (3 != argc)
        {
            std::cout << "Usage: YandexSort <gen-file> <sorted-file>\n";
            std::cout << "Example:\n";
            std::cout << "  YandexSort gen sorted\n";
            return 1;
        }

        generator<value_type> gen(file_size, mem_limit);
        gen.generate(argv[1]);

//         sorter<value_type> srt(mem_limit);
//         srt.sort(argv[1], argv[2]);
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

	return 0;
}
