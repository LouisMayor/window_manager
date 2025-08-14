#pragma once

#ifdef _WINDOWS
#include "Win/WinAPI.h"
#endif

#include <string>

namespace Platform
{
#ifdef _WINDOWS
	using WindowHandle = HWND;
	using OsInstanceHandle = HINSTANCE;
	using WindowMsgProcessor = WNDPROC;
#undef CreateWindow // stop stupid name clashing
					// todo: move to windows specific header
#else
	using WindowHandle = void*;
	using OsInstanceHandle = void*;
	using WindowMsgProcessor = void*;
#endif

	WindowHandle CreateWindow(
		WindowMsgProcessor in_msg_processor,
		const std::wstring& in_window_name);

	// lazily store shouldn't really have public access
	void SetOSInstanceHandle(OsInstanceHandle in_instance_handle);
	static OsInstanceHandle sOsHandle;
}
