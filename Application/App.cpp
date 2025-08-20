#include "App.h"

#include "../Apps/TestApps/CreateWindowApp.h"

bool App::OnInit()
{
	_app_service.RegisterApp
	(
		AppRegistery
		{
			EAppType::WindowCreationTest,
			L"",
			StaticCallbackContainer::sMake(&CreateWindowApp::AppEntry)
		}
	);

	const bool wx_res = WxApp::OnInit();
	_launcher_window = std::make_unique<LauncherWindow>(_app_service);

	return wx_res;
}
