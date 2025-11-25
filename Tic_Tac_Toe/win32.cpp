#include <windows.h>
#include "utility.cpp"
#include <cmath>
#include <time.h>

#define white 0xffffff
#define green 0x00ff00
#define red 0xff0000
#define blue 0x0000ff
#define yellow 0xffff00
#define black 0
#define PIXEL_SIZE 0.28f

static bool running = true;
static HWND WindoW_HWND;

struct Render
{
	void* memory;
	int width, height;
	BITMAPINFO bitmap_info;
};
Render render;

#include "rendering.cpp"
#include "game.cpp"



LRESULT CALLBACK Window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//This is function which sends a message when something important is happened(input, minimize, maximize, size changed
	LRESULT result = 0;
	switch (uMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
	{
		running = false;
	}
	break;
	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hwnd, &rect);
		render.width = rect.right - rect.left;
		render.height = rect.bottom - rect.top;
		int size = render.width * render.height * sizeof(unsigned int);
		if (render.memory)
		{
			VirtualFree(render.memory, 0, MEM_RELEASE);
		}
		render.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		render.bitmap_info.bmiHeader.biSize = sizeof(render.bitmap_info.bmiHeader);
		render.bitmap_info.bmiHeader.biWidth = render.width;
		render.bitmap_info.bmiHeader.biHeight = render.height;
		render.bitmap_info.bmiHeader.biPlanes = 1;
		render.bitmap_info.bmiHeader.biBitCount = 32;
		render.bitmap_info.bmiHeader.biCompression = BI_RGB;
	}
	default:
	{
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
	return result;
}
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//Creating Window(or Window class)
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW || CS_VREDRAW; //CS_HREDRAW - Horizontal; CS_VREDRAW - Vertical 
	window_class.lpszClassName = "Game Window Class";
	window_class.lpfnWndProc = Window_callback;

	//Register Class
	RegisterClass(&window_class);

	WindoW_HWND = CreateWindow(window_class.lpszClassName, "Tic Tac Toe", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1200, 768, 0, 0, hInstance, 0);
	HDC hdc = GetDC(WindoW_HWND);
	while (running)
	{
		//Input
		MSG message;
		while (PeekMessage(&message, WindoW_HWND, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		//Simulate
		simulategame();
		//Game
		//Moving
		//Creating Window
		StretchDIBits(hdc, 0, 0, render.width, render.height, 0, 0, render.width, render.height, render.memory, &render.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}
}