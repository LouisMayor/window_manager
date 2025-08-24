#include "TypeCacheService.h"

void TypeCacheService::RegisterType(const TypeInfo& info)
{
	if (!GetTypeInfo(info._id))
	{
		_type_infos.emplace(info._id, info);
	}
}

const TypeInfo* TypeCacheService::GetTypeInfo(const TypeId& id)
{
	if (auto it = _type_infos.find(id); it != _type_infos.end())
	{
		return &it->second;
	}

	return nullptr;
}
