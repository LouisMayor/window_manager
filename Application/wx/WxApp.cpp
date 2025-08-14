#include "WxApp.h"

// wxIMPLEMENT_APP(WxApp);
wxIMPLEMENT_APP_NO_MAIN(WxApp);

bool WxApp::OnInit()
{
	// required to load images
	wxInitAllImageHandlers();
	return wxApp::OnInit();
}
