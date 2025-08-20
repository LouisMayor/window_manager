#pragma once

#include "LauncherMVC.h"

// todo: probably rename to just be 'Launcher'
class LauncherWindow
{
public:
	LauncherWindow(AppService& in_app_service);
	~LauncherWindow();

	LauncherMVC _mvc;
};
