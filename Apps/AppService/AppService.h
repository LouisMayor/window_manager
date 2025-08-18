#pragma once

#include <future>
#include <string>
#include <thread>
#include <vector>

#include "../../Misc/StaticCallbacks.h"

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

class AppRegistery
{
public:
	[[nodiscard]] explicit AppRegistery(
		EAppType in_app_type,
		std::wstring in_icon_path,
		StaticCallbackContainer in_app_main);

	EAppType GetAppType() const;
	StaticCallbackContainer& GetAppMain();
	std::wstring_view GetIconPath() const;

private:
	EAppType _app_type;
	std::wstring _icon_path;
	StaticCallbackContainer _on_app_start;
};

class AppService
{
public:
	// todo: maybe put reg code into the registry and then you can just ask to run an app through the service
	// that way, we aren't exposing too much to the view/controller
	void RegisterApp(AppRegistery app);
	void UnregisterApp(AppRegistery app);

	std::wstring_view GetAppIconPath(EAppType app_type);
	void LaunchApp(EAppType app_type);

	static AppService& GetInstance();

private:
	static inline std::unique_ptr<AppService> sInstance = nullptr;
	std::vector<AppRegistery> _apps;
	std::vector<std::future<void>> _app_threads;
};
