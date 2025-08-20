#include "LauncherMVC.h"

#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/icon.h>
#include <wx/log.h>
#include <wx/panel.h>
#include <wx/taskbar.h>

#include "../resource.h"
#include "../Apps/AppService/AppService.h"

LauncherWxFrame::LauncherWxFrame(WXHWND inHWND) : wxFrame()
{
	SetHWND(inHWND);
	wxWindow::AdoptAttributesFromHWND();
	SubclassWin(inHWND);
}

WXLRESULT LauncherWxFrame::MSWWindowProc(WXUINT msg, WXWPARAM wParam, WXLPARAM lParam)
{
	if (msg == WM_KEYDOWN && wParam == VK_F1)
	{
		wxLogMessage("F1 pressed in custom WndProc hook!");
		return 0;
	}

	switch (msg)
	{
	case WM_COMMAND: // todo: use commands?
		{
			i32 wmId = LOWORD(wParam);
			switch (wmId)
			{
				// case IDM_ABOUT:
				// 	DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				// 	break;
			case IDM_EXIT:
				DestroyWindow(GetHandle());
				break;
			default:
				return DefWindowProc(GetHandle(), msg, wParam, lParam);
			}
		}
		break;
		// case WM_PAINT:
		// 	{
		// 		PAINTSTRUCT ps;
		// 		HDC hdc = BeginPaint(hWnd, &ps);
		// 		EndPaint(hWnd, &ps);
		// 	}
		// 	break;
	case WM_CLOSE:
		DestroyWindow(GetHandle());
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: ;
		return wxFrame::MSWWindowProc(msg, wParam, lParam);
	}

	return wxFrame::MSWWindowProc(msg, wParam, lParam);
}

void LauncherModel::IncrementCounter()
{
	_counter++;
}

void LauncherView::Init(LauncherController& in_controller)
{
	View::Init(in_controller);

	// todo: won't actually need this WndProc, as we will be overriding it with the LauncherWxFrame
	// see constructor
	_window_handle = Platform::CreateWindow(
		LauncherWndProc,
		L"LauncherWindow");

	_frame = new LauncherWxFrame(_window_handle);
	_frame->CreateStatusBar();
	_frame->SetStatusText(L"Hello World");

	_panel = new wxPanel(
		_frame,
		wxID_ANY,
		wxDefaultPosition,
		wxSize(600, 800));

	_taskbar_icon = new wxTaskBarIcon();

	if (!_taskbar_icon->SetIcon(
		wxIcon("myIconImage2.ico", wxBITMAP_TYPE_ICO),
		"wxTaskBarIcon Sample\n"
		"With a very, very, very, very\n"
		"long tooltip whose length is\n"
		"greater than 64 characters."))
	{
		wxLogError("Could not set icon.");
	}

	_button = new wxButton(
		_panel,
		wxID_ANY,
		"Test",
		wxPoint(10, 10),
		wxSize(100, 30));

	_button->SetToolTip("TestTest");
	_button->Bind(wxEVT_BUTTON, &LauncherView::OnButtonClick, this);

	// AppService::GetInstance().GetAppIconPath(EAppType::WindowCreationTest);
	_image_button = new wxBitmapButton(
		_panel,
		wxID_ANY,
		wxBitmap("myIconImage2.ico", wxBITMAP_TYPE_ICO),
		wxPoint(110, 10),
		wxSize(100, 30));

	_image_button->Bind(wxEVT_BUTTON, &LauncherView::OnAppButtonClick, this);
}

LauncherView::~LauncherView()
{
	// todo: parent widgets and destroy root widget
	delete _button;
	delete _panel;
	delete _taskbar_icon;
	delete _frame;
}

void LauncherView::RefreshCounterView(i32 in_counter) const
{
	_frame->SetStatusText(wxString::Format(L"Counter: %d", in_counter));
}

void LauncherView::OnButtonClick(wxCommandEvent& event)
{
	_frame->SetStatusText(L"Button Clicked!");
	_controller->IncrementCounter();
}

void LauncherView::OnAppButtonClick(wxCommandEvent& event) 
{
	_controller->LaunchApp(EAppType::WindowCreationTest);
}

LauncherController::LauncherController(AppService& in_app_service)
	: _app_service(in_app_service)
{
}

void LauncherController::IncrementCounter()
{
	_model->IncrementCounter();
	_view->RefreshCounterView(_model->GetCounter());
}

void LauncherController::LaunchApp(EAppType in_app_type)
{
	_app_service.LaunchApp(in_app_type);
}
