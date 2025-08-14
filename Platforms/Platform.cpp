#include "Platform.h"

Platform::WindowHandle Platform::CreateWindow(
	const WindowMsgProcessor in_msg_processor,
	const std::wstring& in_window_name)
{
#ifdef _WINDOWS
	const WindowHandle handle = WinAPI::Win_CreateWindow(
		in_window_name.c_str(),
		sOsHandle,
		in_msg_processor);
	ShowWindow(handle, SW_SHOW);
	UpdateWindow(handle);
	return handle;
#elif 
	return nullptr;
#endif
	
}

void Platform::SetOSInstanceHandle(OsInstanceHandle in_instance_handle)
{
	sOsHandle = in_instance_handle;
}
