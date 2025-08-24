#pragma once

#include <unordered_map>

#include "TypeId.h"
#include "TypeInfo.h"
#include "../../Apps/Service/Service.h"

class TypeCacheService : public Service 
{
public:
	void RegisterType(const TypeInfo& info);
	const TypeInfo* GetTypeInfo(const TypeId& id);

private:
	std::unordered_map<TypeId, TypeInfo> _type_infos;
};
