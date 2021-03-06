/*
    @author Ilnaz Nizametdinov (c)

    @project YandexSort

    @description
        Application entry point.
 */

#include <pch.h>

#include <algo/generator.hpp>
#include <algo/sorter.hpp>

int main(int argc, char* argv[])
{
    typedef int value_type;

    // Restrictions
    const size_t file_size = 1 << 30; // 1G
    const size_t mem_limit = 100 * (1 << 20); // 100M

    assert (0 != file_size);
    assert (0 != mem_limit);

    assert (0 == (file_size % sizeof(value_type)));
    assert (0 == (mem_limit % sizeof(value_type)));

    // chunk size cannot be zero
    assert (0 != ((mem_limit / sizeof(value_type)) / ((file_size / mem_limit) + 1)));

    try
    {
        if (3 != argc)
        {
            std::cout << "Usage: YandexSort <gen-file> <sorted-file>\n";
            std::cout << "Example:\n";
            std::cout << "  YandexSort gen sorted\n";
            return 1;
        }

        std::cout << "Generating " << file_size << " byte(s) of data...\n";

        generator<value_type> gen(file_size, mem_limit);
        gen.generate(argv[1]);

        std::cout << "Sorting...\n";

        sorter<value_type> srt(mem_limit);
        srt.sort(argv[1], argv[2]);

        std::cout << "Done!\n";
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
