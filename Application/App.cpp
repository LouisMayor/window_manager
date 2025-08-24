#include "App.h"

#include "../Apps/TestApps/CreateWindowApp.h"
#include "../Misc/RTTI/TypeCacheService.h"

bool App::OnInit()
{
	_service_manager.RegisterService<TypeCacheService>();
	_service_manager.RegisterService<AppService>();

	_service_manager.GetService<AppService>()->RegisterApp
	(
		AppRegistry
		{
			EAppType::WindowCreationTest,
			L"",
			StaticCallbackContainer::sMake(&CreateWindowApp::AppEntry)
		}
	);

	const bool wx_res = WxApp::OnInit();
	_launcher_window = std::make_unique<LauncherWindow>(*_service_manager.GetService<AppService>());

	return wx_res;
}
