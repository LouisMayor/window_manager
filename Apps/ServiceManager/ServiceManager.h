#pragma once

#include <memory>
#include <unordered_map>

#include "../misc/RTTI/TypeId.h"
#include "../Service/Service.h"

template<typename T>
concept is_service_type = std::is_base_of_v<Service, T>;

class ServiceManager
{
public:
	ServiceManager();

	static ServiceManager* GetInstance();

	template<typename TService>
	requires is_service_type<TService>
	void RegisterService();

	template<typename TService>
	requires is_service_type<TService>
	TService* GetService();

private:
	Service* GetService(const TypeId& id);
	std::unordered_map<TypeId, std::unique_ptr<Service>> _services;

	// todo: I don't want singletons, but I also don't want to DI everything
	static inline ServiceManager* _service_manager_singleton = nullptr;
};

template <typename TService>
requires is_service_type<TService>
void ServiceManager::RegisterService()
{
	auto type_id = GetTypeId<TService>();
	if (!GetService(type_id))
	{
		_services.emplace(type_id, std::make_unique<TService>());
	}
}

template <typename TService>
requires is_service_type<TService>
TService* ServiceManager::GetService()
{
	auto type_id = GetTypeId<TService>();
	if (GetService(type_id))
	{
		return static_cast<TService*>(_services[type_id].get());
	}

	return nullptr;
}
