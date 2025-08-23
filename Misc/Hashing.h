#pragma once

#include <string>
#include <string_view>

#include "../types.h"

namespace Hashing
{
	// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
	consteval u64 fnv1_ct(const std::string_view in_string)
	{
		constexpr u64 fnv_prime = 0x100000001b3; // offset basis
		u64 hash = 0xcbf29ce484222325;

		for (const char c : in_string)
		{
			hash *= fnv_prime;
			hash ^= static_cast<unsigned char>(c);
		}

		return hash;
	}

	inline u64 fnv1(const std::string_view in_string)
	{
		constexpr u64 fnv_prime = 0x100000001b3; // offset basis
		u64 hash = 0xcbf29ce484222325;

		for (const char c : in_string)
		{
			hash *= fnv_prime;
			hash ^= static_cast<unsigned char>(c);
		}

		return hash;
	}
}

namespace HashingTests
{
	inline bool TestFNV1()
	{
		std::string test_string = "Hello World";

		u64 hash0 = Hashing::fnv1(test_string);
		u64 hash1 = Hashing::fnv1(test_string);

		test_string += "!";
		u64 hash2 = Hashing::fnv1(test_string);

		test_string += "^$^%$";
		u64 hash3 = Hashing::fnv1(test_string);

		return hash0 == hash1 && hash1 != hash2 && hash2 != hash3;
	}
}
