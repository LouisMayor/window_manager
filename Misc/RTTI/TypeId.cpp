#include "TypeId.h"

size_t std::hash<TypeId>::operator()(const TypeId& id) const noexcept
{
	// already hashed
	return id.id;
}
