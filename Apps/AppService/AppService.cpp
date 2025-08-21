#include "AppService.h"

#include <algorithm>
#include <utility>

AppRegistery::AppRegistery(
	EAppType in_app_type,
	std::wstring in_icon_path,
	StaticCallbackContainer in_app_main)
	: _app_type(in_app_type), _icon_path(std::move(in_icon_path)), _on_app_start(std::move(in_app_main))
{
}

EAppType AppRegistery::GetAppType() const
{
	return _app_type;
}

StaticCallbackContainer& AppRegistery::GetAppMain() 
{
	return _on_app_start;
}

std::wstring_view AppRegistery::GetIconPath() const
{
	return _icon_path;
}

AppService::~AppService()
{
	for (std::future<void>& future : _app_threads)
	{
		future.wait();
	}

	_app_threads.clear();
}

void AppService::RegisterApp(AppRegistery app)
{
	auto it = std::ranges::find_if(_apps, [&app](AppRegistery& a)
	{
		return a.GetAppType() == app.GetAppType();
	});

	if (it == _apps.end())
	{
		_apps.push_back(std::move(app));
	}
}

void AppService::UnregisterApp(AppRegistery app)
{
	auto it = std::ranges::find_if(_apps, [&app](AppRegistery& a)
	{
		return a.GetAppType() == app.GetAppType();
	});

	if (it != _apps.end())
	{
		_apps.erase(it);
	}
}

std::wstring_view AppService::GetAppIconPath(EAppType app_type)
{
	auto it = std::ranges::find_if(_apps, [app_type](AppRegistery& a)
	{
		return a.GetAppType() == app_type; 
	});

	if (it != _apps.end())
	{
		return it->GetIconPath();
	}

	return {};
}

void AppService::LaunchApp(EAppType app_type)
{
	auto it = std::ranges::find_if(_apps, [app_type](AppRegistery& a)
	{
		return a.GetAppType() == app_type;
	});

	// many design questions about how best manage
	if (it != _apps.end())
	{
		// trigger app on a new thread
		auto launch = [](AppRegisteryView in_app_registery)
		{
			in_app_registery.GetAppMain().Invoke();
		};

		_app_threads.push_back(std::async(std::launch::async, launch, it->ToView()));
	}
}
