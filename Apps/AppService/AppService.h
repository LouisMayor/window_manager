#pragma once

#include <future>
#include <string>
#include <vector>

#include "../../Misc/StaticCallbacks.h"
#include "../Service/Service.h"

enum class EAppType
{
	WindowCreationTest
};

inline const char* to_string(EAppType e)
{
	switch (e)
	{
	case EAppType::WindowCreationTest: return "WindowCreationTest";
	default: return "unknown";
	}
}

struct AppRegistryView
{
	StaticCallbackContainerView& GetAppMain()
	{
		return _callback_view;
	}

	StaticCallbackContainerView _callback_view;
};

class AppRegistry
{
public:
	[[nodiscard]] explicit AppRegistry(
		EAppType in_app_type,
		std::wstring in_icon_path,
		StaticCallbackContainer in_app_main);

	EAppType GetAppType() const;
	StaticCallbackContainer& GetAppMain();
	std::wstring_view GetIconPath() const;

	AppRegistryView ToView() const
	{
		return {_on_app_start.ToView()};
	}

private:
	EAppType _app_type;
	std::wstring _icon_path;
	StaticCallbackContainer _on_app_start;
};

// todo: probably better design to split this into app registry and 'app service'
class AppService : public Service
{
public:
	explicit AppService() = default;
	virtual ~AppService();

	// todo: maybe put reg code into the registry and then you can just ask to run an app through the service
	// that way, we aren't exposing too much to the view/controller
	void RegisterApp(AppRegistry app);
	void UnregisterApp(AppRegistry app);

	std::wstring_view GetAppIconPath(EAppType app_type);
	void LaunchApp(EAppType app_type);

private:
	std::vector<AppRegistry> _apps;
	std::vector<std::future<void>> _app_threads;
};
