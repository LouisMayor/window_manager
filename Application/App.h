#pragma once

#ifdef _WX
#include "wx/WxApp.h"
#endif

#include "../Apps/AppService/AppService.h"
#include "../Launcher/LauncherWindow.h"

#ifdef _WX

class App : public WxApp
#endif
{
public:
	explicit App() = default;
	virtual bool OnInit();

private:
	std::unique_ptr<LauncherWindow> _launcher_window = nullptr;
	AppService _app_service;
};
