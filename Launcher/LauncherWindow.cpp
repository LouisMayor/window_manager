#include "LauncherWindow.h"

#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../Apps/AppService/AppService.h"

LauncherWindow::LauncherWindow(AppService& in_app_service)
	: _mvc(in_app_service)
{
	_mvc.Init();
}

LauncherWindow::~LauncherWindow()
{

}
