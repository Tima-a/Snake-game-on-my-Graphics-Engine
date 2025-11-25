static void clear_screen(unsigned int color) {
	unsigned int* pixel = (unsigned int*)render.memory;
	for (int y = 0; y < render.height; y++) {
		for (int x = 0; x < render.width; x++) {
			*pixel++ = color;
		}
	}
}

static void draw_rect_in_pixels(int x0, int y0, int x1, int y1, unsigned int color)
{

	x0 = clamp(0, x0, render.width);
	x1 = clamp(0, x1, render.width);
	y0 = clamp(0, y0, render.height);
	y1 = clamp(0, y1, render.height);
	for (int y = y0; y < y1; y++)
	{
		unsigned int* pixel = (unsigned int*)render.memory + x0 + y * render.width;
		for (int x = x0; x < x1; x++)
		{
			*pixel++ = color;
		}
	}
}
static float render_scale = 0.01f;


static void draw_rect(float x, float y, float half_size_x, float half_size_y, unsigned int color)
{

	x *= render.height * render_scale;
	y *= render.height * render_scale;
	half_size_x *= render.height * render_scale;
	half_size_y *= render.height * render_scale;

	x += (float)render.width / 2.0f;
	y += (float)render.height / 2.0f;

	// Change to pixels
	int x0 = (int)x - (int)half_size_x;
	int x1 = (int)x + (int)half_size_x;
	int y0 = (int)y - (int)half_size_y;
	int y1 = (int)y + (int)half_size_y;

	draw_rect_in_pixels(x0, y0, x1, y1, color);
}
//
//
void draw_numbers(int number, float x, float y, int color)
{
	if (number == 0)
	{
		draw_rect(x, y + 5.0f / 1.5f, 5 / 1.5f, 1, color);
		draw_rect(x, y - 5.0f / 1.5f, 5 / 1.5f, 1, color);
		draw_rect(x + 3.4f / 1.5f, y, 1, 5 / 1.5f, color);
		draw_rect(x - 3.4f / 1.5f, y, 1, 5 / 1.5f, color);
	}
	if (number == 1)
	{
		draw_rect(x, y, 1, 4.65f, color);
	}
	if (number == 2)
	{
		draw_rect(x+2.4f, y + 3.7f, 2.8f, 1, color);
		draw_rect(x + 4.1f, y + 1.7f, 1, 1.4f, color);
		draw_rect(x + 3.1f, y-0.4f, 2, 1, color);
		draw_rect(x + 0.2f, y - 1.4f, 1, 2, color);
		draw_rect(x + 2.1f, y - 3.5f, 3, 1, color);
	}
	if (number == 3)
	{
		draw_rect(x + 1.1f, y + 3.75f, 3, 0.75f, color);
		draw_rect(x + 4.1f, y+0.1f, 1, 4.4f, color);
		draw_rect(x + 1.5f, y, 2.5f, 0.75f, color);
		draw_rect(x + 1.1f, y - 3.5f, 3, 0.75f, color);
	}
	if (number == 4)
	{
		draw_rect(x - 2.9f, y + 1.5f, 1, 2.5f, 0xffffff);
		draw_rect(x + 2.9f, y - 0.5f, 1, 4.3f, 0xffffff);
		draw_rect(x, y, 2, 1, 0xffffff);
	}
	if (number == 5)
	{
		draw_rect(x, y, 3.5f, 1.0f, 0xffffff);
		draw_rect(x-2.5f, y+2.5f, 1.0f, 1.85f, 0xffffff);
		draw_rect(x, y+3.4f, 2.5f, 1.0f, 0xffffff);
		draw_rect(x + 2.5f, y-2.0f, 1.0f, 2.45f, 0xffffff);
		draw_rect(x, y-3.5f, 3.0f, 1.0f, 0xffffff);
	}
	if (number == 6)
	{
		draw_rect(x, y + 1.8f / 2.0f, 6.0f / 2.0f, 1, color);
		draw_rect(x, y - 3.75f, 6.0f / 2.0f, 1, color);
		draw_rect(x + 4.0f / 2.0f, y-2.2f, 1, 5.0f / 2.0f, color);
		draw_rect(x - 3.9f / 2.0f, y - 0.8f, 1, 4.0f, color);
		draw_rect(x, y + 3.8f, 6.0f / 2.0f, 1, color);
	}
	if (number == 7)
	{
		draw_rect(x, y, 1.0f, 4.3f, 0xffffff);
		draw_rect(x-2.0f, y+3.6f, 3.0f, 1.0f, 0xffffff);
	}
	if (number == 8)
	{
		draw_rect(x - 2.0f, y, 1.0f, 5.0f, color);
		draw_rect(x + 2.0f, y, 1.0f, 5.0f, color);
		draw_rect(x, y, 3.0f, 1.0f, color);
		draw_rect(x, y-4.1f, 3.0f, 1.0f, color);
		draw_rect(x, y+4.0f, 3.0f, 1.0f, color);
	}
	if (number == 9)
	{
		draw_rect(x + 2.0f, y+0.5f, 1.0f, 4.5f, 0xffffff);
		draw_rect(x - 2.0f, y+2.0f, 1.0f, 3.0f, 0xffffff);
		draw_rect(x, y, 3.0f, 1.0f, 0xffffff);
		draw_rect(x, y + 4.0f, 2.0f, 1.0f, 0xffffff);
		draw_rect(x, y - 3.0f, 2.0f, 1.0f, 0xffffff);
	}
}
static void draw_score(int digit1, int digit2, float x, float y, int color)
{
	if (digit1 == 0 || digit2 == 0)
	{
		draw_numbers(0, x, y, color);
	}
	if (digit1 == 1 || digit2 == 1)
	{
		float curx = x;
		if (digit2 == 1)
		{
			draw_numbers(1, curx - 10.0f, y, color);
		}
		else
		{
			draw_numbers(1, curx, y, color);
		}
	}
	if (digit1 == 2 || digit2 == 2)
	{
		float curx = x;
		if (digit2 == 2)
		{
			draw_numbers(2, curx - 10.0f, y, color);
		}
		else
		{
			draw_numbers(2, curx, y, color);
		}
	}
	if (digit1 == 3 || digit2 == 3)
	{
		float curx = x;
		if (digit2 == 3)
		{
			draw_numbers(3, curx - 10.0f, y, color);
		}
		else
		{
			draw_numbers(3, curx, y, color);
		}
	}
	if (digit1 == 4 || digit2 == 4)
	{
		float curx = x;
		if (digit2 == 4)
		{
			draw_numbers(4, curx - 10.0f, y, color);
		}
		else
		{
			draw_numbers(4, curx, y, color);
		}
	}
	if (digit1 == 5 || digit2 == 5)
	{
		float curx = x;
		if (digit2 == 5)
		{
			draw_numbers(5, curx - 10.0f, y, color);
		}
		else
		{
			draw_numbers(5, curx, y, color);
		}
	}
	if (digit1 == 6 || digit2 == 6)
	{
		float curx = x;
		if (digit2 == 6)
		{
			draw_numbers(6, curx - 10.0f, y, color);
		}
		else
		{
			draw_numbers(6, curx, y, color);
		}
	}
	if (digit1 == 7 || digit2 == 7)
	{
		float curx = x;
		if (digit2 == 7)
		{
			draw_numbers(7, curx - 10.0f, y, color);
		}
		else
		{
			draw_numbers(7, curx, y, color);
		}
	}
	if (digit1 == 8 || digit2 == 8)
	{
		float curx = x;
		if (digit2 == 8)
		{
			draw_numbers(8, curx - 10.0f, y, color);
		}
		else
		{
			draw_numbers(8, curx, y, color);
		}
	}
	if (digit1 == 9 || digit2 == 9)
	{
		float curx = x;
		if (digit2 == 9)
		{
			draw_numbers(9, curx - 10.0f, y, color);
		}
		else
		{
			draw_numbers(9, curx, y, color);
		}
	}
}