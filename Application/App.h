#pragma once

#ifdef _WX
#include "wx/WxApp.h"
#endif

#include "../Launcher/LauncherWindow.h"

#ifdef _WX
class App : public WxApp
#endif
{
public:
	virtual bool OnInit();

private:
	std::unique_ptr<LauncherWindow> _launcher_window = nullptr;
};
