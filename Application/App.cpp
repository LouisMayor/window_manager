#include "App.h"

bool App::OnInit()
{
	const bool wx_res = WxApp::OnInit();
	_launcher_window = std::make_unique<LauncherWindow>();
	return wx_res;
}
