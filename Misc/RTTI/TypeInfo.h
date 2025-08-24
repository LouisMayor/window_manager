#pragma once

#include <vector>

#include "TypeId.h"

class TypeInfo
{
public:
	[[nodiscard]] TypeInfo(const TypeId& id, const std::string_view& name, const std::vector<TypeId>& inheritance)
		: _id(id),
		  _name(name),
		  _inheritance(inheritance)
	{
	}

// private:
	TypeId _id;
	std::string_view _name;
	std::vector<TypeId> _inheritance;
};
