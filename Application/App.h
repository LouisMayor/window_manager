#pragma once

#ifdef _WX
#include "wx/WxApp.h"
#endif

#include "../Apps/AppService/AppService.h"
#include "../Launcher/LauncherWindow.h"

#ifdef _WX

class AppService;

class App : public WxApp
#endif
{
public:
	[[nodiscard]] explicit App(AppService& app_service);

	virtual bool OnInit();

private:
	std::unique_ptr<LauncherWindow> _launcher_window = nullptr;
	AppService& _app_service;
};
