#pragma once
 
#ifndef WX_PRECOMP
#include <wx/wx.h>
#else
#include <wx/wxprec.h>
#endif

class WxApp : public wxApp
{
public:
	virtual bool OnInit();
};
