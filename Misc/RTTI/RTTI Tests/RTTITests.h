#pragma once

#include "../TypeId.h"

namespace RTTITests
{
	inline bool TestBasicTypes()
	{
		[[maybe_unused]] TypeId int_id = GetTypeId<int>();
		[[maybe_unused]] TypeId int2_id = GetTypeId<int>();
		return int_id == int2_id;
	}

	consteval bool TestBasicTypes_ct()
	{
		[[maybe_unused]] TypeId int_id = GetTypeId_ct<int>();
		[[maybe_unused]] TypeId int2_id = GetTypeId_ct<int>();
		return int_id == int2_id;
	}

	consteval bool TestBasicTypes_pp()
	{
		[[maybe_unused]] TypeId int_id = GetTypeId_pp<int>();
		[[maybe_unused]] TypeId int2_id = GetTypeId_pp<int>();
		return int_id == int2_id;
	}
}
