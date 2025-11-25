#include <windows.h>
#include "utility.cpp"
#include <random>
bool running = true;
struct Render
{
	void* memory;
	int width, height;
	BITMAPINFO bitmap_info;
};
Render render;

#include "renderering.cpp"
#include "gamecpp.cpp"

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
void Draw_not_filled_square(float x, float y, float xscale, float yscale, unsigned int color)
{
	//Generating square
	float ycenterpos = yscale / 200.0f;
	float ycentersize = 200.0f;
	for (int i = 0; i < 3; i++)
	{
		if (i == 1)
		{
			draw_rect(x + yscale, y, xscale, yscale, color);
			draw_rect(x, y - yscale, yscale, xscale, color);
		}
		if (i == 2)
		{
			draw_rect(x - yscale, y, xscale, yscale, color);
			draw_rect(x, y + yscale, yscale, xscale, color);
		}
	}
	draw_rect(x, y + ycenterpos, xscale, yscale / ycentersize, color);
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

	HWND window = CreateWindow(window_class.lpszClassName, "My First Game!", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);
	while (running)
	{
		//Input
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		//Simulate
		clear_screen(0);
		simulategame();
		//Game
		//Moving
		//Creating Window
		StretchDIBits(hdc, 0, 0, render.width, render.height, 0, 0, render.width, render.height, render.memory, &render.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}
}