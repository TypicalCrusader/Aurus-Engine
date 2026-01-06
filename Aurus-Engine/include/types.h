/*
 * SPDX-FileCopyrightText: 2010 =Lennart Poettering
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <uchar.h>

#define DATA __attribute__((section(".data")))
#define USE_SSE_PARAM __attribute__ ((sseregparm))
#define USE_FASTCALL __attribute__((fastcall))
#define HOT_FUNC __attribute__((hot))
#define CLEANUP(func) __attribute__ ((__cleanup__(func)))

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
typedef char32_t    chr;

typedef uintptr_t   gpEvent;

//taken from systemd
#define DEFINE_TRIVIAL_CLEANUP_FUNC(type, func)                 \
        static inline void func##p(type *p) {                   \
                if (*p)                                         \
                        func(*p);                               \
        }                                                       \
        struct __useless_struct_to_allow_trailing_semicolon__
#define _likely_(x) (__builtin_expect(!!(x),1))
#define _unlikely_(x) (__builtin_expect(!!(x),0))

inline void free_buffer(char **buffer)
{
  free(*buffer);
}