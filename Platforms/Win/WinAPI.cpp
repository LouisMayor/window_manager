#ifdef _WINDOWS

#include "WinAPI.h"

#include <Windows.h>
#include "../../resource.h"

constexpr int32 max_string_length = 256;

namespace
{
	[[maybe_unused]] DWORD Win_CreateWindowStyleDefault()
	{
		return 0;
	}

	void Win_GetClassName(
		HINSTANCE in_instance_handle,
		WCHAR* buffer)
	{
		LoadStringW(
			in_instance_handle,
			IDC_WINDOWMANAGER,
			buffer,
			max_string_length);
	}

	ATOM Win_RegisterClass(
		HINSTANCE in_instance_handle,
		WNDPROC in_window_msg_processor,
		LPCWSTR in_window_class)
	{
		WNDCLASSEXW wcex;

		wcex.cbSize			= sizeof(WNDCLASSEX);
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= in_window_msg_processor;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= in_instance_handle;
		wcex.hIcon			= LoadIcon(in_instance_handle, MAKEINTRESOURCE(IDI_WINDOWMANAGER));
		wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= MAKEINTRESOURCEW(IDC_WINDOWMANAGER);
		wcex.lpszClassName	= in_window_class;
		wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		return RegisterClassExW(&wcex);
	}
}

HWND WinAPI::Win_CreateWindow(
	LPCWSTR in_window_name,
	HINSTANCE in_instance_handle,
	WNDPROC in_window_msg_processor)
{
	WCHAR class_name[max_string_length];
	Win_GetClassName(in_instance_handle, class_name);
	[[maybe_unused]] DWORD style = Win_CreateWindowStyleDefault();

	Win_RegisterClass(
		in_instance_handle,
		in_window_msg_processor,
		class_name);

	const HWND res = CreateWindow(
		class_name,
		in_window_name,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		nullptr,
		nullptr,
		in_instance_handle,
		nullptr);

	return res;
}

#endif