// types.h
#pragma once

#include <cstdint>
#include <cstddef>

// Fixed-width signed integers
using int8  = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

// Fixed-width unsigned integers
using uint8  = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

// Short aliases
using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

// Floating-point
using f32 = float;
using f64 = double;

// Pointer-sized integers
using isize = std::ptrdiff_t;
using usize = std::size_t;

// Optional: boolean byte alias (1 byte)
using b8 = bool;

// Sanity checks (platform-agnostic guarantees)
static_assert(sizeof(i8)  == 1,  "int8 must be 8 bits");
static_assert(sizeof(u8)  == 1,  "uint8 must be 8 bits");
static_assert(sizeof(i16) == 2,  "int16 must be 16 bits");
static_assert(sizeof(u16) == 2,  "uint16 must be 16 bits");
static_assert(sizeof(i32) == 4,  "int32 must be 32 bits");
static_assert(sizeof(u32) == 4,  "uint32 must be 32 bits");
static_assert(sizeof(i64) == 8,  "int64 must be 64 bits");
static_assert(sizeof(u64) == 8,  "uint64 must be 64 bits");
static_assert(sizeof(f32) == 4,  "f32 must be 32-bit float");
static_assert(sizeof(f64) == 8,  "f64 must be 64-bit float");

#ifdef _WINDOWS
#define _AMD64_ // hack to not require include windows.h
#include <WinDef.h>
#include <WinUser.h>
#endif
