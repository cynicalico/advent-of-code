#pragma once

#ifdef _WIN32
    #ifdef LIBAOC_EXPORTS
        #define LIBAOC_API __declspec(dllexport)
    #else
        #define LIBAOC_API __declspec(dllimport)
    #endif
#else
    #if defined(__GNUC__) || defined(__clang__)
        #define LIBAOC_API __attribute__((visibility("default")))
    #else
        #define LIBAOC_API
    #endif
#endif
