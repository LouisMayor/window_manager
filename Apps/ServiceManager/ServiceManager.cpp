#include "ServiceManager.h"

ServiceManager::ServiceManager()
{
	if (_service_manager_singleton == nullptr)
	{
		_service_manager_singleton = this;
	}
}

ServiceManager* ServiceManager::GetInstance()
{
	return _service_manager_singleton;
}

Service* ServiceManager::GetService(const TypeId& id)
{
	if (const auto it = _services.find(id); it != _services.end())
	{
		return it->second.get();
	}

	return nullptr;
}
