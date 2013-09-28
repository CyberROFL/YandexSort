/*
    @author Ilnaz Nizametdinov (c)

    @project YandexSort

    @description
        Include file for standard system include files, or project specific
        include files that are used frequently, but are changed infrequently.
 */

#ifndef __PRECOMPILLED_HEADER_H__
#define __PRECOMPILLED_HEADER_H__

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
    #define _WIN32_WINNT 0x0600 // Change this to the appropriate value to target other versions of Windows.
#endif

#include <fstream>
#include <algorithm>
#include <cassert>

#include <vector>

#endif // __PRECOMPILLED_HEADER_H__
