#pragma once

#include "../MVC/MVC.h"
#include "../Platforms/Platform.h"

#include <wx/frame.h>

#include "../Apps/AppService/AppService.h"

enum class EAppType;
class wxBitmapButton;
class wxTaskBarIcon;
class wxButton;
class wxPanel;
class wxCommandEvent;

class LauncherModel;
class LauncherView;
class LauncherController;

// todo: abstract this, and write callbacks to specific events that fire into the window instance
// e.g. OnMouseUp/Down Destroy, etc...
inline LRESULT CALLBACK LauncherWndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		{
			i32 wmId = LOWORD(wParam);
			switch (wmId)
			{
				// case IDM_ABOUT:
				// DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				// break;
			// case IDM_EXIT:
				// DestroyWindow(hWnd);
				// break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

class LauncherWxFrame : public wxFrame
{
public:
	LauncherWxFrame(WXHWND inHWND);

protected:
	WXLRESULT MSWWindowProc(WXUINT msg, WXWPARAM wParam, WXLPARAM lParam) override;
};

class LauncherModel : public Model
{
public:
	void IncrementCounter();
	i32 GetCounter() const { return _counter; }

private:
	i32 _counter = 0;
};

class LauncherView : public View<LauncherController>
{
public:
	void Init(LauncherController& in_controller) override;

	~LauncherView() override;

	void RefreshCounterView(i32 in_counter) const;
	void OnButtonClick(wxCommandEvent& event);
	void OnAppButtonClick(wxCommandEvent& event);

	Platform::WindowHandle _window_handle;

	LauncherWxFrame* _frame = nullptr;
	wxTaskBarIcon* _taskbar_icon = nullptr;

	wxBitmapButton* _image_button = nullptr;
	wxButton* _button = nullptr;
	wxPanel* _panel = nullptr;
};

class LauncherController : public Controller<LauncherModel, LauncherView>
{
public:
	explicit LauncherController(AppService& in_app_service);
	void IncrementCounter();
	void LaunchApp(EAppType in_app_type);

private:
	AppService& _app_service;
};

class LauncherMVC : public MVC<LauncherController, LauncherView, LauncherModel>
{
public:
	// public scope for templated variadic argument constructor
	using MVC<LauncherController, LauncherView, LauncherModel>::MVC;
};
