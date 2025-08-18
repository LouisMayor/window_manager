#include "App.h"

#include "../Apps/TestApps/CreateWindowApp.h"

App::App(AppService& app_service): _app_service(app_service)
{
}

bool App::OnInit()
{
	// _app_service.RegisterApp
	AppService& inst = AppService::GetInstance();
	inst.RegisterApp
	(
		AppRegistery
		{
			EAppType::WindowCreationTest,
			L"",
			StaticCallbackContainer::sMake(&CreateWindowApp::AppEntry)
		}
	);

	const bool wx_res = WxApp::OnInit();
	_launcher_window = std::make_unique<LauncherWindow>();

	return wx_res;
}
