#pragma once

#include <typeinfo>

#include "../Hashing.h"

// hashed id
struct TypeId
{
	constexpr bool operator==(const TypeId& other) const { return this->id == other.id; }
	u64 id;
};

// todo: make it match the other impls, seen below
template <typename T>
consteval std::string_view GetTypeName_ct() {
#if defined(__clang__) || defined(__GNUC__)
	return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
	return __FUNCSIG__;
#endif
}

#define TYPE_NAME(x) #x

/* type id generator - compile time.
 * note: this isn't comparable to the TypeId generated at runtime
 * due to the nature of GetTypeName_ct impl
 *
 * https://rodusek.com/posts/2021/03/09/getting-an-unmangled-type-name-at-compile-time/ */
template<typename T>
consteval TypeId GetTypeId_ct()
{
	return TypeId{ Hashing::fnv1_ct(GetTypeName_ct<T>()) };
};

template<typename T>
consteval TypeId GetTypeId_pp()
{
	return TypeId{ Hashing::fnv1_ct(TYPE_NAME(T)) };
};

template<typename T>
TypeId GetTypeId()
{
	return TypeId{ Hashing::fnv1(typeid(T).name()) };
};
