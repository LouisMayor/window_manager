#include <cstdio>
#include <process.h>

#include "WinMain.h"
#include "framework.h"
#include "types.h"
#include "Application/App.h"
#include "Apps/AppService/AppService.h"
#include "Platforms/Win/WinAPI.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;	// current instance

// Forward declarations of functions included in this code module:
// BOOL				InitInstance(HINSTANCE, i32);
// LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
u32 __stdcall		ConsoleInputThread(void* arg);

// console app entry point
// i32 main()
// {
// 	return 0;
// }

// windows app entry point
i32 APIENTRY wWinMain(
	_In_ HINSTANCE		hInstance,
	_In_opt_ HINSTANCE	hPrevInstance,
	_In_ LPWSTR			lpCmdLine,
	_In_ i32			nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	ALLOC_CONSOLE_OPTIONS opts = {
		ALLOC_CONSOLE_MODE::ALLOC_CONSOLE_MODE_DEFAULT,
		TRUE,
		SW_SHOW
	};

	ALLOC_CONSOLE_RESULT result;
	AllocConsoleWithOptions(&opts, &result);

	// pass io to the console from this process
	FILE* console_file = nullptr;
	freopen_s(&console_file, "CONOUT$", "w", stdout);
	freopen_s(&console_file, "CONOUT$", "w", stderr);
	freopen_s(&console_file, "CONIN$", "r", stdin);

	ALLOC_CONSOLE_RESULT log_console_alloc_result;
	AllocConsoleWithOptions(&opts, &log_console_alloc_result);

	// pass input directly to the console
	_beginthreadex(NULL, 0, ConsoleInputThread, NULL, 0, NULL);

	// Perform application initialization:
	// if (!InitInstance(hInstance, nCmdShow))
	// {
	// 	return FALSE;
	// }

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWMANAGER));

	Platform::SetOSInstanceHandle(hInstance);
	AppService app_service;
	App app = App(app_service);
	app.OnInit();

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (i32)msg.wParam;
}

// Saves instance handle and creates main window
// BOOL InitInstance(
// 	HINSTANCE hInstance,
// 	i32 nCmdShow)
// {
// 	hInst = hInstance; // Store instance handle in our global variable
//
// 	const HWND hWnd = WinAPI::Win_CreateWindow(
// 		L"MainWindow",
// 		hInstance,
// 		&WndProc);
//
// 	if (!hWnd)
// 	{
// 		return FALSE;
// 	}
//
// 	ShowWindow(hWnd, nCmdShow);
// 	UpdateWindow(hWnd);
//
// 	return TRUE;
// }

// Processes messages for the main window.
LRESULT CALLBACK WndProc(
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
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			TextOut(hdc, 10, 10, L"Hello World", 12);
			EndPaint(hWnd, &ps);
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

// Message handler for about box.
INT_PTR CALLBACK About(
	HWND hDlg,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

u32 __stdcall ConsoleInputThread(void* arg)
{
	char buffer[256];
	while (1)
	{
		if (fgets(buffer, sizeof(buffer), stdin) != NULL)
		{
			// Remove trailing newline
			size_t len = strlen(buffer);
			if (len > 0 && buffer[len - 1] == '\n') 
			{
				buffer[len - 1] = '\0';
			}

			printf("[Terminal] You typed: %s\n", buffer);
			// todo: parse as commands

			if (_stricmp(buffer, "exit") == 0)
			{
				// printf("Exiting console thread...\n");
				break;
			}
		}
	}

	return 0;
}