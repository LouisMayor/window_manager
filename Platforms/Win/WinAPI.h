#pragma once

#ifdef _WINDOWS

// #include <Windows.h>
#include "../../types.h"

namespace WinAPI
{
	HWND Win_CreateWindow(LPCWSTR in_window_name, HINSTANCE in_instance_handle, WNDPROC in_window_msg_processor);
}

#endif