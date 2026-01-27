/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#define CLEANUP(func) __attribute__ ((__cleanup__(func)))

typedef uint8_t      u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;
typedef int8_t       s8;
typedef int16_t     s16;
typedef int32_t     s32;
typedef int64_t     s64;
typedef float       f32;
typedef double      f64;  

#define DATA __attribute__((section(".data")))
#define USE_SSE_PARAM __attribute__ ((sseregparm))
#define USE_FASTCALL __attribute__((fastcall))
#define HOT_FUNC __attribute__((hot))

typedef uint8_t      u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;
typedef int8_t       s8;
typedef int16_t     s16;
typedef int32_t     s32;
typedef int64_t     s64;
typedef float       f32;
typedef double      f64;
typedef char32_t    uni_chr;

typedef void (*gpEvent)(void);

//taken from systemd
#define DEFINE_TRIVIAL_CLEANUP_FUNC(type, func)                 \
        static inline void func##p(type *p) {                   \
                if (*p)                                         \
                        func(*p);                               \
        }                                                       \
        struct __useless_struct_to_allow_trailing_semicolon__
#define _likely_(x) (__builtin_expect(!!(x),1))
#define _unlikely_(x) (__builtin_expect(!!(x),0))
//end of code taken from systemd

static inline void free_number(void *p) {
        free(*(void**)p);
};

#define CLEANUP(func) __attribute__((cleanup(func)))
//because microsoft is antichrist, fuck you
#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
    #include <malloc.h>
    #define my_aligned_alloc(size, align)   _aligned_malloc((size), (align))
    #define my_aligned_free(ptr)            _aligned_free((ptr))
#else
    #define my_aligned_alloc(size, align)   aligned_alloc((align), (size))
    #define my_aligned_free(ptr)            free((ptr))
#endif

typedef void (*gSkillFunc)(u16 uSkillID);