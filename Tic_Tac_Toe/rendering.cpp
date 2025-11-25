static float render_scale = 0.01f;
static float pi = 3.1415f;
static float gravity = -9.81f;
static float Gravitational_constant = 0.000000000016f;

static void clear_screen(unsigned int color)
{
	unsigned int* pixel = (unsigned int*)render.memory;
	for (int y = 0; y < render.height; y++)
	{
		for (int x = 0; x < render.width; x++)
		{
			*pixel++ = color;
		}
	}
}
static void draw_pixel(float x, float y, float pixelsizex, float pixelsizey, unsigned int color)
{
	float x_pixel_size = pixelsizex;
	float y_pixel_size = pixelsizey;
	x *= render.height * render_scale;
	y *= render.height * render_scale;
	x_pixel_size *= render.height * render_scale;
	y_pixel_size *= render.height * render_scale;

	x += (float)render.width / 2.0f;
	y += (float)render.height / 2.0f;

	// Change to pixels
	int x0 = (int)x - (int)x_pixel_size;
	int x1 = (int)x + (int)x_pixel_size;
	int y0 = (int)y - (int)y_pixel_size;
	int y1 = (int)y + (int)y_pixel_size;

	x0 = clamp(0, x0, render.width);
	x1 = clamp(0, x1, render.width);
	y0 = clamp(0, y0, render.height);
	y1 = clamp(0, y1, render.height);

	for (int y = y0; y < y1; y++)
	{
		unsigned int* pixel = (unsigned int*)render.memory + x0 + y*render.width;
		for (int x = x0; x < x1; x++)
		{
			*pixel++ = color;
		}
	}
}
namespace rectangle
{
	void draw_rect(float x, float y, float half_size_x, float half_size_y, unsigned int color)
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
	class RECT
	{
	public:
		float x;
		float y;
		float a;
		float b;
		unsigned int color;
		RECT(float x_, float y_, float a_, float b_, unsigned int color_)
		{
			x = x_;
			y = y_;
			a = a_;
			b = b_;
			color = color_;
		}
		float size(float x, float y)
		{
			return x * y;
		}
		void draw()
		{
			rectangle::draw_rect(x, y, a, b, color);
		}
	};
}
namespace vector2d
{
	void check(float x1, float x2, float y1, float y2, float x_modifier, float y_modifier, float& x_increasement, float& y_increasement, bool directions[4])
	{
		float differencex;
		float differencey;
		if (x2 > x1)
		{
			if (directions[0] == true || directions[2] == true)
			{
				differencex = x2 - (x1 + x_modifier);
			}
			if (directions[1] == true || directions[3] == true)
			{
				differencex = x2 - (x1 - x_modifier);
			}
		}
		if (x1 > x2)
		{
			if (directions[0] == true || directions[2] == true)
			{
				differencex = x1 - (x2 + x_modifier);
			}
			if (directions[1] == true || directions[3] == true)
			{
				differencex = x1 - (x2 - x_modifier);
			}
		}
		if (y2 > y1)
		{
			if (directions[0] == true || directions[1] == true)
			{
				differencey = y2 - (y1 + y_modifier);
			}
			if (directions[2] == true || directions[3] == true)
			{
				differencey = y2 - (y1 - y_modifier);
			}
		}
		if (y1 > y2)
		{
			if (directions[0] == true || directions[1] == true)
			{
				differencey = y1 - (y2 + y_modifier);
			}
			if (directions[2] == true || directions[3] == true)
			{
				differencey = y1 - (y2 - y_modifier);
			}
		}
		if (differencex < 0.0f)
		{
			x_increasement = 0.0f;
		}
		if (differencey < 0.0f)
		{
			y_increasement = 0.0f;
		}
	}
	static void draw_vector(float x1, float y1, float x2, float y2, float pixelsize, unsigned int color)
	{
		bool x_y_outweight = false, xy_swap = false; // if x2>y2, false, y2>x2, true; if x2&&y2 < x1&&y1 swap them
		bool straight_line_drawing = false;
		bool draw_just_pixel = false;
		int straight_line_type = -1;
		//0 - up
		//1 - down
		//2 - right
		//3 - left
		if (x1 == y1 && x1 == x2 && x1 && y1 && x2 != y2 && neg_or_pos_num(y2))
		{
			straight_line_drawing = true;
			straight_line_type = 0;
		}
		if (x1 == y1 && x1 == x2 && x1 && y1 && x2 != y2 && !neg_or_pos_num(y2))
		{
			straight_line_drawing = true;
			straight_line_type = 1;
		}
		if (x1 == y1 && x1 == y2 && x1 && y1 && y2 != x2 && neg_or_pos_num(x2))
		{
			straight_line_drawing = true;
			straight_line_type = 2;
		}
		if (x1 == y1 && x1 == y2 && x1 && y1 && y2 != x2 && !neg_or_pos_num(x2))
		{
			straight_line_drawing = true;
			straight_line_type = 3;
		}
		if (x1 == x2 && y2 > y1)
		{
			straight_line_drawing = true;
			straight_line_type = 0;
		}
		if (x1 == x2 && y1 > y2)
		{
			straight_line_drawing = true;
			straight_line_type = 1;
		}
		if (y1 == y2 && x2 > x1)
		{
			straight_line_drawing = true;
			straight_line_type = 2;
		}
		if (y1 == y2 && x1 > x2)
		{
			straight_line_drawing = true;
			straight_line_type = 3;
		}
		if (x1 == x2 && y1 == y2)
		{
			draw_pixel(x2, y2, PIXEL_SIZE, PIXEL_SIZE, color);
			draw_just_pixel = true;
		}
		fabs(x1) > fabs(x2) && fabs(y1) > fabs(y2) ? xy_swap = true : xy_swap = false;
		if (xy_swap == true)
		{
			swap(x2, x1);
			swap(y2, y1);
			//swapping function
		}
		bool directions[4]
		{
			false, // up_right
			false, // up_left
			false, // down_right
			false // down_left
		};
		float dx = x2 - x1;
		float dy = y2 - y1;
		float adx = fabs(x2 - x1);
		float ady = fabs(y2 - y1);
		dx > 0.0f && dy > 0.0f ? directions[0] = true : directions[0] = false; // if (dx > 0.0f && dy > 0.0f){directions[0]=true} else {directions=false}
		dx < 0.0f && dy > 0.0f ? directions[1] = true : directions[1] = false;
		dx > 0.0f && dy < 0.0f ? directions[2] = true : directions[2] = false;
		dx < 0.0f && dy < 0.0f ? directions[3] = true : directions[3] = false;
		float x_modifier = 0.0f, y_modifier = 0.0f;
		//for (int i = 0; i < 5; i++)
		//{
		//	draw_pixel(x1, y1 + i, PIXEL_SIZE, PIXEL_SIZE, rgb(255, 255, 0));
		//	draw_pixel(x2, y2 + i, PIXEL_SIZE, PIXEL_SIZE, rgb(255, 255, 0));
		//}
		//draw_pixel(0.0f, 0.0f, PIXEL_SIZE, PIXEL_SIZE, rgb(255, 255, 0));
		float x_addition = 1.0f, y_addition = 1.0f;
		int start_x = 0, start_y = 0;
		fabs(x2) > fabs(y2) ? x_addition = (fabs(adx) / fabs(ady)) * 2.0f : y_addition = (fabs(ady) / fabs(adx)) * 2.0f;
		fabs(x2) > fabs(y2) ? x_y_outweight = false : x_y_outweight = true;
		fabs(x2) > fabs(y2) ? start_x = 1 : start_y = 1;
		if (straight_line_drawing == false && draw_just_pixel == false)
		{
			//
			//
			//draw line
			int max;
			fabs(x2) > fabs(y2) ? max = (int)(fabs(x2) * fabs(x2)) : max = (int)(fabs(y2) * fabs(y2));
			for (int i = 0; i < (int)max; i++) // max value. x2*y2
			{
				bool x_cycle = false, y_cycle = false;
				i % 2 == start_y ? x_cycle = true : x_cycle = false;
				i % 2 == start_x ? y_cycle = true : y_cycle = false;
				if (x_cycle == true)
				{
					for (int j = 0; j < 4; j++)
					{
						if (directions[j] == true)
						{
							if (x_y_outweight == false)
							{
								for (int x = 0; x < (int)ceil(fabs(x_addition)); x++)
								{
									if (x != floor(fabs(x_addition)))
									{
										draw_pixel(x1 + x_modifier, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
									}
									float x_increasement = PIXEL_SIZE, y_increasement = PIXEL_SIZE;
									if (check_number_type(x_addition) == false)
									{
										if (x == floor(fabs(x_addition)))
										{
											x_increasement = (fabs(x_addition) - floor(fabs(x_addition))) * 0.28f;
										}
										if (x != floor(fabs(x_addition)))
										{
											x_increasement = 0.28f;
										}
									}
									check(x1, x2, y1, y2, x_modifier, y_modifier, x_increasement, y_increasement, directions);
									if (x_increasement == 0.0f && y_increasement == 0.0f)
									{
										max = i;
										break;
									}
									if (j == 0 || j == 2)
									{
										x_modifier += x_increasement;
									}
									if (j == 1 || j == 3)
									{
										x_modifier -= x_increasement;
									}
									if (x == floor(fabs(x_addition)))
									{
										draw_pixel(x1 + x_modifier, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
									}
								}
							}
							if (x_y_outweight == true)
							{
								for (int x = 0; x < 2; x++)
								{
									float x_increasement = PIXEL_SIZE, y_increasement = PIXEL_SIZE;
									draw_pixel(x1 + x_modifier, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
									check(x1, x2, y1, y2, x_modifier, y_modifier, x_increasement, y_increasement, directions);
									if (x_increasement == 0.0f && y_increasement == 0.0f)
									{
										max = i;
										break;
									}
									if (j == 0 || j == 2)
									{
										x_modifier += x_increasement;
									}
									if (j == 1 || j == 3)
									{
										x_modifier -= x_increasement;
									}
								}
							}
						}
					}
				}
				if (y_cycle == true)
				{
					for (int k = 0; k < 4; k++)
					{
						if (directions[k] == true)
						{
							if (x_y_outweight == true)
							{
								for (int y = 0; y < (int)round(y_addition); y++)
								{
									if (y != floor(fabs(y_addition)))
									{
										draw_pixel(x1 + x_modifier, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
									}
									float x_increasement = PIXEL_SIZE, y_increasement = PIXEL_SIZE;
									if (check_number_type(y_addition) == false)
									{
										if (y == floor(fabs(y_addition)))
										{
											y_increasement = (fabs(y_addition) - floor(fabs(y_addition))) * 0.28f;
										}
										if (y != floor(fabs(y_addition)))
										{
											y_increasement = 0.28f;
										}
									}
									check(x1, x2, y1, y2, x_modifier, y_modifier, x_increasement, y_increasement, directions);
									if (x_increasement == 0.0f && y_increasement == 0.0f)
									{
										max = i;
										break;
									}
									if (k == 0 || k == 1)
									{
										y_modifier += y_increasement;
									}
									if (k == 2 || k == 3)
									{
										y_modifier -= y_increasement;
									}
									if (y == floor(fabs(x_addition)))
									{
										draw_pixel(x1 + x_modifier, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
									}
								}
							}
							if (x_y_outweight == false)
							{
								for (int x = 0; x < 2; x++) //+2 because of < sign in for, and because when the first pixel generates at y1+y_modifier it will not be counted in for
								{
									float x_increasement = PIXEL_SIZE, y_increasement = PIXEL_SIZE;
									draw_pixel(x1 + x_modifier, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
									check(x1, x2, y1, y2, x_modifier, y_modifier, x_increasement, y_increasement, directions);
									if (x_increasement == 0.0f && y_increasement == 0.0f)
									{
										max = i;
										break;
									}
									if (k == 0 || k == 1)
									{
										y_modifier += y_increasement;
									}
									if (k == 2 || k == 3)
									{
										y_modifier -= y_increasement;
									}
								}
							}
						}
					}
				}
				float x_increasement = PIXEL_SIZE, y_increasement = PIXEL_SIZE;
				check(x1, x2, y1, y2, x_modifier, y_modifier, x_increasement, y_increasement, directions);
				if (x_increasement == 0.0f && y_increasement == 0.0f)
				{
					max = i;
					break;
				}
			}
		}
		if (straight_line_drawing == true)
		{
			float max;
			fabs(x2) > fabs(y2) ? max = fabs(x2) * fabs(x2) : max = fabs(y2) * fabs(y2);
			for (int x = 0; x < max; x++) // changing max
			{
				if (straight_line_type == 0)
				{
					float y_increasement = PIXEL_SIZE;
					draw_pixel(x1, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
					y_modifier += y_increasement;
					if (round(y1 + y_modifier) == round(y2))
					{
						draw_pixel(x1, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
						y_modifier += y_increasement;
						draw_pixel(x1, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
						y_modifier += y_increasement;
						y_increasement = 0.0f;
						break;
					}
				}
				if (straight_line_type == 1)
				{
					float y_increasement = PIXEL_SIZE;
					draw_pixel(x1, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
					y_modifier -= y_increasement;
					if (round(y1 + y_modifier) == round(y2))
					{
						draw_pixel(x1, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
						y_modifier -= y_increasement;
						draw_pixel(x1, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
						y_modifier -= y_increasement;
						y_increasement = 0.0f;
						break;
					}
				}
				if (straight_line_type == 2)
				{
					float x_increasement = PIXEL_SIZE;
					draw_pixel(x1 + x_modifier, y1, PIXEL_SIZE, PIXEL_SIZE, color);
					x_modifier += x_increasement;
					if (round(x1 + x_modifier) == round(x2))
					{
						draw_pixel(x1 + x_modifier, y1, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
						x_modifier += x_increasement;
						draw_pixel(x1 + x_modifier, y1, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
						x_modifier += x_increasement;
						x_increasement = 0.0f;
						break;
					}
				}
				if (straight_line_type == 3)
				{
					float x_increasement = PIXEL_SIZE;
					draw_pixel(x1 + x_modifier, y1, PIXEL_SIZE, PIXEL_SIZE, color);
					x_modifier -= x_increasement;
					if (round(x1 + x_modifier) == round(x2))
					{
						draw_pixel(x1 + x_modifier, y1, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
						x_modifier -= x_increasement;
						draw_pixel(x1 + x_modifier, y1, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
						x_modifier -= x_increasement;
						x_increasement = 0.0f;
						break;
					}
				}
			}
		}
	}

	class VECTOR
	{
	public:
		float pixelsposx[1000];
		float pixelsposy[1000];
		int pixelindex;
		float startx;
		float starty;
		float x2;
		float y2;
		float pixelsize;
		unsigned int color;

		VECTOR(float startx_, float starty_, float x2_, float y2_, unsigned int color_)
		{
			startx = startx_;
			starty = starty_;
			x2 = x2_;
			y2 = y2_;
			color = color_;
		}

		float centerx()
		{
			return (x2 - startx) / 2.0f;
		}
		float centery()
		{
			return (y2 - starty) / 2.0f;
		}
		float magnitude()
		{
			float adx = fabs(x2 - startx);
			float ady = fabs(y2 - starty);
			float mag = sqrt(adx * adx + ady * ady);
			return mag;
		}
		void draw()
		{
			vector2d::draw_vector(startx, starty, x2, y2, pixelsize, color);
		}
		void draw_vector(float x1, float y1, float x2, float y2, float pixelsize, unsigned int color, bool save_pixels_x = false, bool save_pixels_y = false /* made only for triangle */)
		{
			bool x_y_outweight = false, xy_swap = false; // if x2>y2, false, y2>x2, true; if x2&&y2 < x1&&y1 swap them
			bool straight_line_drawing = false;
			bool draw_just_pixel = false;
			int straight_line_type = -1;
			//0 - up
			//1 - down
			//2 - right
			//3 - left
			int g = 0;
			if (x1 == y1 && x1 == x2 && x1 && y1 && x2 != y2 && neg_or_pos_num(y2))
			{
				straight_line_drawing = true;
				straight_line_type = 0;
			}
			if (x1 == y1 && x1 == x2 && x1 && y1 && x2 != y2 && !neg_or_pos_num(y2))
			{
				straight_line_drawing = true;
				straight_line_type = 1;
			}
			if (x1 == y1 && x1 == y2 && x1 && y1 && y2 != x2 && neg_or_pos_num(x2))
			{
				straight_line_drawing = true;
				straight_line_type = 2;
			}
			if (x1 == y1 && x1 == y2 && x1 && y1 && y2 != x2 && !neg_or_pos_num(x2))
			{
				straight_line_drawing = true;
				straight_line_type = 3;
			}
			if (x1 == x2 && y2 > y1)
			{
				straight_line_drawing = true;
				straight_line_type = 0;
			}
			if (x1 == x2 && y1 > y2)
			{
				straight_line_drawing = true;
				straight_line_type = 1;
			}
			if (y1 == y2 && x2 > x1)
			{
				straight_line_drawing = true;
				straight_line_type = 2;
			}
			if (y1 == y2 && x1 > x2)
			{
				straight_line_drawing = true;
				straight_line_type = 3;
			}
			if (x1 == x2 && y1 == y2)
			{
				draw_pixel(x2, y2, PIXEL_SIZE, PIXEL_SIZE, color);
				pixelsposx[g] = x2;
				pixelsposy[g] = y2;
				g += 1;
				draw_just_pixel = true;
			}
			fabs(x1) > fabs(x2) && fabs(y1) > fabs(y2) ? xy_swap = true : xy_swap = false;
			if (xy_swap == true)
			{
				swap(x2, x1);
				swap(y2, y1);
				//swapping function
			}
			bool directions[4]
			{
				false, // up_right
				false, // up_left
				false, // down_right
				false // down_left
			};
			float dx = x2 - x1;
			float dy = y2 - y1;
			float adx = fabs(x2 - x1);
			float ady = fabs(y2 - y1);
			dx > 0.0f && dy > 0.0f ? directions[0] = true : directions[0] = false; // if (dx > 0.0f && dy > 0.0f){directions[0]=true} else {directions=false}
			dx < 0.0f && dy > 0.0f ? directions[1] = true : directions[1] = false;
			dx > 0.0f && dy < 0.0f ? directions[2] = true : directions[2] = false;
			dx < 0.0f && dy < 0.0f ? directions[3] = true : directions[3] = false;
			float x_modifier = 0.0f, y_modifier = 0.0f;
			//for (int i = 0; i < 5; i++)
			//{
			//	draw_pixel(x1, y1 + i, PIXEL_SIZE, PIXEL_SIZE, rgb(255, 255, 0));
			//	draw_pixel(x2, y2 + i, PIXEL_SIZE, PIXEL_SIZE, rgb(255, 255, 0));
			//}
			//draw_pixel(0.0f, 0.0f, PIXEL_SIZE, PIXEL_SIZE, rgb(255, 255, 0));
			float x_addition = 1.0f, y_addition = 1.0f;
			int start_x = 0, start_y = 0;
			fabs(x2) > fabs(y2) ? x_addition = (fabs(adx) / fabs(ady)) * 2.0f : y_addition = (fabs(ady) / fabs(adx)) * 2.0f;
			fabs(x2) > fabs(y2) ? x_y_outweight = false : x_y_outweight = true;
			fabs(x2) > fabs(y2) ? start_x = 1 : start_y = 1;
			if (straight_line_drawing == false && draw_just_pixel == false)
			{
				//
				//
				//draw line
				int max;
				fabs(x2) > fabs(y2) ? max = (int)(fabs(x2) * fabs(x2)) : max = (int)(fabs(y2) * fabs(y2));
				for (int i = 0; i < (int)max; i++) // max value. x2*y2
				{
					bool x_cycle = false, y_cycle = false;
					i % 2 == start_y ? x_cycle = true : x_cycle = false;
					i % 2 == start_x ? y_cycle = true : y_cycle = false;
					if (x_cycle == true)
					{
						for (int j = 0; j < 4; j++)
						{
							if (directions[j] == true)
							{
								if (x_y_outweight == false)
								{
									for (int x = 0; x < (int)ceil(fabs(x_addition)); x++)
									{
										if (x != floor(fabs(x_addition)))
										{
											draw_pixel(x1 + x_modifier, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
											pixelsposx[g] = x1 + x_modifier;
											pixelsposy[g] = y1 + y_modifier;
											g += 1;
										}
										float x_increasement = PIXEL_SIZE, y_increasement = PIXEL_SIZE;
										if (check_number_type(x_addition) == false)
										{
											if (x == floor(fabs(x_addition)))
											{
												x_increasement = (fabs(x_addition) - floor(fabs(x_addition))) * 0.28f;
											}
											if (x != floor(fabs(x_addition)))
											{
												x_increasement = 0.28f;
											}
										}
										check(x1, x2, y1, y2, x_modifier, y_modifier, x_increasement, y_increasement, directions);
										if (x_increasement == 0.0f && y_increasement == 0.0f)
										{
											max = i;
											break;
										}
										if (j == 0 || j == 2)
										{
											x_modifier += x_increasement;
										}
										if (j == 1 || j == 3)
										{
											x_modifier -= x_increasement;
										}
										if (x == floor(fabs(x_addition)))
										{
											draw_pixel(x1 + x_modifier, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
											pixelsposx[g] = x1 + x_modifier;
											pixelsposy[g] = y1 + y_modifier;
											g += 1;
										}
									}
								}
								if (x_y_outweight == true)
								{
									for (int x = 0; x < 2; x++)
									{
										float x_increasement = PIXEL_SIZE, y_increasement = PIXEL_SIZE;
										draw_pixel(x1 + x_modifier, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
										pixelsposx[g] = x1 + x_modifier;
										pixelsposy[g] = y1 + y_modifier;
										g += 1;
										check(x1, x2, y1, y2, x_modifier, y_modifier, x_increasement, y_increasement, directions);
										if (x_increasement == 0.0f && y_increasement == 0.0f)
										{
											max = i;
											break;
										}
										if (j == 0 || j == 2)
										{
											x_modifier += x_increasement;
										}
										if (j == 1 || j == 3)
										{
											x_modifier -= x_increasement;
										}
									}
								}
							}
						}
					}
					if (y_cycle == true)
					{
						for (int k = 0; k < 4; k++)
						{
							if (directions[k] == true)
							{
								if (x_y_outweight == true)
								{
									for (int y = 0; y < (int)round(y_addition); y++)
									{
										if (y != floor(fabs(y_addition)))
										{
											draw_pixel(x1 + x_modifier, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
											pixelsposx[g] = x1 + x_modifier;
											pixelsposy[g] = y1 + y_modifier;
											g += 1;
										}
										float x_increasement = PIXEL_SIZE, y_increasement = PIXEL_SIZE;
										if (check_number_type(y_addition) == false)
										{
											if (y == floor(fabs(y_addition)))
											{
												y_increasement = (fabs(y_addition) - floor(fabs(y_addition))) * 0.28f;
											}
											if (y != floor(fabs(y_addition)))
											{
												y_increasement = 0.28f;
											}
										}
										check(x1, x2, y1, y2, x_modifier, y_modifier, x_increasement, y_increasement, directions);
										if (x_increasement == 0.0f && y_increasement == 0.0f)
										{
											max = i;
											break;
										}
										if (k == 0 || k == 1)
										{
											y_modifier += y_increasement;
										}
										if (k == 2 || k == 3)
										{
											y_modifier -= y_increasement;
										}
										if (y == floor(fabs(x_addition)))
										{
											draw_pixel(x1 + x_modifier, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
											pixelsposx[g] = x1 + x_modifier;
											pixelsposy[g] = y1 + y_modifier;
											g += 1;
										}
									}
								}
								if (x_y_outweight == false)
								{
									for (int x = 0; x < 2; x++) //+2 because of < sign in for, and because when the first pixel generates at y1+y_modifier it will not be counted in for
									{
										float x_increasement = PIXEL_SIZE, y_increasement = PIXEL_SIZE;
										draw_pixel(x1 + x_modifier, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
										pixelsposx[g] = x1 + x_modifier;
										pixelsposy[g] = y1 + y_modifier;
										g += 1;
										check(x1, x2, y1, y2, x_modifier, y_modifier, x_increasement, y_increasement, directions);
										if (x_increasement == 0.0f && y_increasement == 0.0f)
										{
											max = i;
											break;
										}
										if (k == 0 || k == 1)
										{
											y_modifier += y_increasement;
										}
										if (k == 2 || k == 3)
										{
											y_modifier -= y_increasement;
										}
									}
								}
							}
						}
					}
					float x_increasement = PIXEL_SIZE, y_increasement = PIXEL_SIZE;
					check(x1, x2, y1, y2, x_modifier, y_modifier, x_increasement, y_increasement, directions);
					if (x_increasement == 0.0f && y_increasement == 0.0f)
					{
						max = i;
						break;
					}
				}
			}
			if (straight_line_drawing == true)
			{
				float max;
				fabs(x2) > fabs(y2) ? max = fabs(x2) * fabs(x2) : max = fabs(y2) * fabs(y2);
				for (int x = 0; x < max; x++) // changing max
				{
					if (straight_line_type == 0)
					{
						float y_increasement = PIXEL_SIZE;
						draw_pixel(x1, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
						y_modifier += y_increasement;
						if (round(y1 + y_modifier) == round(y2))
						{
							draw_pixel(x1, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
							pixelsposx[g] = x1;
							pixelsposy[g] = y1 + y_modifier;
							g += 1;
							y_modifier += y_increasement;
							draw_pixel(x1, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
							pixelsposx[g] = x1;
							pixelsposy[g] = y1 + y_modifier;
							g += 1;
							y_modifier += y_increasement;
							y_increasement = 0.0f;
							break;
						}
					}
					if (straight_line_type == 1)
					{
						float y_increasement = PIXEL_SIZE;
						draw_pixel(x1, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color);
						y_modifier -= y_increasement;
						if (round(y1 + y_modifier) == round(y2))
						{
							draw_pixel(x1, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
							pixelsposx[g] = x1 + x_modifier;
							pixelsposy[g] = y1;
							g += 1;
							y_modifier -= y_increasement;
							draw_pixel(x1, y1 + y_modifier, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
							pixelsposx[g] = x1 + x_modifier;
							pixelsposy[g] = y1;
							g += 1;
							y_modifier -= y_increasement;
							y_increasement = 0.0f;
							break;
						}
					}
					if (straight_line_type == 2)
					{
						float x_increasement = PIXEL_SIZE;
						draw_pixel(x1 + x_modifier, y1, PIXEL_SIZE, PIXEL_SIZE, color);
						x_modifier += x_increasement;
						if (round(x1 + x_modifier) == round(x2))
						{
							draw_pixel(x1 + x_modifier, y1, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
							pixelsposx[g] = x1 + x_modifier;
							pixelsposy[g] = y1;
							g += 1;
							x_modifier += x_increasement;
							draw_pixel(x1 + x_modifier, y1, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
							pixelsposx[g] = x1 + x_modifier;
							pixelsposy[g] = y1;
							g += 1;
							x_modifier += x_increasement;
							x_increasement = 0.0f;
							break;
						}
					}
					if (straight_line_type == 3)
					{
						float x_increasement = PIXEL_SIZE;
						draw_pixel(x1 + x_modifier, y1, PIXEL_SIZE, PIXEL_SIZE, color);
						x_modifier -= x_increasement;
						if (round(x1 + x_modifier) == round(x2))
						{
							draw_pixel(x1 + x_modifier, y1, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
							pixelsposx[g] = x1 + x_modifier;
							pixelsposy[g] = y1;
							g += 1;
							x_modifier -= x_increasement;
							draw_pixel(x1 + x_modifier, y1, PIXEL_SIZE, PIXEL_SIZE, color); // round function bug(rounding too much)
							pixelsposx[g] = x1 + x_modifier;
							pixelsposy[g] = y1;
							g += 1;
							x_modifier -= x_increasement;
							x_increasement = 0.0f;
							break;
						}
					}
				}
			}
			pixelindex = g;
		}
		float pixels()
		{
			return pixelindex;
		}
	};
}
namespace cube
{
	static void draw_cube(float x, float y, float a, int r, int g, int b) // size of each side of a cube
	{
		vector2d::draw_vector(x, y, x - (a / 2.0f), y - (a / 2.0f), PIXEL_SIZE, rgb(r - 10, g - 10, b - 10));
		vector2d::draw_vector(x - (a / 2.0f), y - (a / 2.0f), x + (a / 2.0f), y - (a / 2.0f), PIXEL_SIZE, rgb(r, g, b));
		vector2d::draw_vector(x - (a / 2.0f), y - (a / 2.0f), x - (a / 2.0f), y + (a / 2.0f), PIXEL_SIZE, rgb(r, g, b));
		vector2d::draw_vector(x - (a / 2.0f), y + (a / 2.0f), x + (a / 2.0f), y + (a / 2.0f), PIXEL_SIZE, rgb(r, g, b));
		vector2d::draw_vector(x + (a / 2.0f), y - (a / 2.0f), x + (a / 2.0f), y + (a / 2.0f), PIXEL_SIZE, rgb(r, g, b));
		vector2d::draw_vector(x, y, x, y + a, PIXEL_SIZE, rgb(r - 10, g - 10, b - 10));
		vector2d::draw_vector(x, y + a, x + a, y + a, PIXEL_SIZE, rgb(r, g, b));
		vector2d::draw_vector(x, y + a, x - (a / 2.0f), y + (a / 2.0f), PIXEL_SIZE, rgb(r, g, b));
		vector2d::draw_vector(x, y, x + a, y, PIXEL_SIZE, rgb(r - 10, g - 10, b - 10));
		vector2d::draw_vector(x + a, y + a, x + (a / 2.0f), y + (a / 2.0f), PIXEL_SIZE, rgb(r, g, b));
		vector2d::draw_vector(x + (a / 2.0f), y - (a / 2.0f), x + a, y, PIXEL_SIZE, rgb(r, g, b));
		vector2d::draw_vector(x + a, y + a, x + a, y, PIXEL_SIZE, rgb(r, g, b));
	}
	class CUBE
	{
	public:
		float x;
		float y;
		float a;
		float r;
		float g;
		float b;

		CUBE(float x_, float y_, float a_, float r_, float g_, float b_)
		{
			x = x_;
			y = y_;
			a = a_;
			r = r_;
			g = g_;
			b = b_;
		}
		float size()
		{
			return 6.0f * a * a;
		}
		void draw()
		{
			cube::draw_cube(x, y, a, r, g, b);
		}
	};
}
namespace triangle
{
	vector2d::VECTOR v1(NULL, NULL, NULL, NULL, NULL);
	vector2d::VECTOR v2(NULL, NULL, NULL, NULL, NULL);
	vector2d::VECTOR v3(NULL, NULL, NULL, NULL, NULL);
	float matrixpixelx[2][1000];
	float matrixpixelx2[2][1000];
	float matrixpixelx3[2][1000];
	int pixelscount;
	int pixelscount2;
	int pixelscount3;
	int max_pixels;
	//0 - x, y - 1 
	static void draw_triangle(float a, float b, float c, float h_apex, float x, float y, unsigned int color)
	{
		vector2d::draw_vector(0.0f, 0.0f, 0.0f, 0.0f, PIXEL_SIZE, green);
		v1.draw_vector(x - c / 2.0f, y - h_apex / 2.0f, x, y + h_apex / 2.0f, PIXEL_SIZE, color, true, true);
		v2.draw_vector(x + c / 2.0f, y - h_apex / 2.0f, x, y + h_apex / 2.0f, PIXEL_SIZE, color, true, true);
		v3.draw_vector(x - c / 2.0f, y - h_apex / 2.0f, x + c / 2.0f, y - h_apex / 2.0f, PIXEL_SIZE, color, true, true);
		for (int k = 0; k < 2; k++)
		{
			for (int j = 0; j < 1000; j++)
			{
				matrixpixelx[0][j] = v1.pixelsposx[k];
				matrixpixelx2[0][j] = v2.pixelsposx[k];
				matrixpixelx3[0][j] = v3.pixelsposx[k];
				matrixpixelx[1][j] = v1.pixelsposy[k];
				matrixpixelx2[1][j] = v2.pixelsposy[k];
				matrixpixelx3[1][j] = v3.pixelsposy[k];
			}
		}
		pixelscount = v1.pixels();
		pixelscount2 = v2.pixels();
		max_pixels = pixelscount + pixelscount2;
		for (int k = 0; k < max_pixels; k++)
		{
			if (matrixpixelx3[0][k] == matrixpixelx[0][k])
			{
				vector2d::draw_vector(matrixpixelx3[0][k], matrixpixelx3[1][k], matrixpixelx[0][k], matrixpixelx[1][k], PIXEL_SIZE, color);
			}
			if (matrixpixelx3[0][k] == matrixpixelx2[0][k])
			{
				vector2d::draw_vector(matrixpixelx3[0][k], matrixpixelx2[1][k], matrixpixelx3[0][k], matrixpixelx2[1][k], PIXEL_SIZE, color);
			}
		}
	}
}
namespace circle
{
	static void draw_circle(float x, float y, float a, float b, unsigned int color, bool filled = true)
	{
		float wx, wy;
		float thresh;
		float asq = a * a;
		float bsq = b * b;
		float xa, ya;
		float sortedxequalingpixels[200];
		float sortedyequalingpixels[200];
		int i = 0;
		bool grid_drawn = false;
		draw_pixel(x, y + b, PIXEL_SIZE, PIXEL_SIZE, color);
		draw_pixel(x, y - b, PIXEL_SIZE, PIXEL_SIZE, color);
		if (filled == true)
		{
			sortedxequalingpixels[i] = x;
			sortedyequalingpixels[i] = y + b;
			sortedxequalingpixels[i + 1] = x;
			sortedyequalingpixels[i + 1] = y - b;
			if (grid_drawn == false)
			{
				i += 2;
			}
		}
		wx = 0.0f;
		wy = b;
		xa = 0.0f;
		ya = asq * 2.0f * b;
		thresh = asq / 4.0f - asq * b;

		for (;;)
		{
			thresh += xa + bsq;

			if (thresh >= 0.0f)
			{
				ya -= asq * 2.0f;
				thresh -= ya;
				wy--;
			}

			xa += bsq * 2.0f;
			wx++;

			if (xa >= ya)
			{
				break;
			}

			draw_pixel(x + wx, y - wy, PIXEL_SIZE, PIXEL_SIZE, color);
			draw_pixel(x - wx, y - wy, PIXEL_SIZE, PIXEL_SIZE, color);
			draw_pixel(x + wx, y + wy, PIXEL_SIZE, PIXEL_SIZE, color);
			draw_pixel(x - wx, y + wy, PIXEL_SIZE, PIXEL_SIZE, color);
			if (filled == true)
			{

				sortedxequalingpixels[i] = x + wx;
				sortedyequalingpixels[i] = y - wy;
				sortedxequalingpixels[i + 1] = x - wx;
				sortedyequalingpixels[i + 1] = y - wy;
				sortedxequalingpixels[i + 2] = x + wx;
				sortedyequalingpixels[i + 2] = y + wy;
				sortedxequalingpixels[i + 3] = x - wx;
				sortedyequalingpixels[i + 3] = y + wy;
				if (grid_drawn == false)
				{
					i += 4;

				}
			}
		}

		draw_pixel(x + a, y, PIXEL_SIZE, PIXEL_SIZE, color);
		draw_pixel(x - a, y, PIXEL_SIZE, PIXEL_SIZE, color);
		if (filled == true)
		{

			sortedxequalingpixels[i] = x + a;
			sortedyequalingpixels[i] = y;
			sortedxequalingpixels[i + 1] = x - a;
			sortedyequalingpixels[i + 1] = y;
			if (grid_drawn == false)
			{
				i += 2;

			}
		}
		wx = a;
		wy = 0.0f;
		xa = bsq * 2.0f * a;

		ya = 0.0f;
		thresh = bsq / 4.0f - bsq * a;

		for (;;)
		{
			thresh += ya + asq;

			if (thresh >= 0.0f)
			{
				xa -= bsq * 2.0f;
				thresh = thresh - xa;
				wx--;
			}

			ya += asq * 2.0f;
			wy++;

			if (ya > xa)
			{
				break;
			}

			draw_pixel(x + wx, y - wy, PIXEL_SIZE, PIXEL_SIZE, color);
			draw_pixel(x - wx, y - wy, PIXEL_SIZE, PIXEL_SIZE, color);
			draw_pixel(x + wx, y + wy, PIXEL_SIZE, PIXEL_SIZE, color);
			draw_pixel(x - wx, y + wy, PIXEL_SIZE, PIXEL_SIZE, color);
			if (filled == true)
			{
				sortedxequalingpixels[i] = x + wx;
				sortedyequalingpixels[i] = y - wy;
				sortedxequalingpixels[i + 1] = x - wx;
				sortedyequalingpixels[i + 1] = y - wy;
				sortedxequalingpixels[i + 2] = x + wx;
				sortedyequalingpixels[i + 2] = y + wy;
				sortedxequalingpixels[i + 3] = x - wx;
				sortedyequalingpixels[i + 3] = y + wy;
				if (grid_drawn == false)
				{
					i += 4;
				}
			}
		}
		grid_drawn = true;
		if (filled == true)
		{
			for (int x = 0; x < i; x++)
			{
				for (int z = 0; z < i; z++)
				{
					if (sortedyequalingpixels[x] == sortedyequalingpixels[z])
					{
						vector2d::draw_vector(sortedxequalingpixels[x], sortedyequalingpixels[x] + 0.5f, sortedxequalingpixels[z], sortedyequalingpixels[z] + 0.5f, PIXEL_SIZE, color);
						vector2d::draw_vector(sortedxequalingpixels[x], sortedyequalingpixels[x], sortedxequalingpixels[z], sortedyequalingpixels[z], PIXEL_SIZE, color);
					}
				}
			}
		}
	}
	class CIRCLE
	{
	public:
		float x;
		float y;
		float a; // width, diameter
		float b; // height
		float mass;
		unsigned int color;
		CIRCLE(float x_, float y_, float a_, float b_, unsigned int color_)
		{
			x = x_;
			y = y_;
			a = a_;
			b = b_;
			color = color_;
		}
		float size()
		{
			return 4.0f * pi * a / 2.0f;
		}
		void draw()
		{
			circle::draw_circle(x, y, a, b, color);
		}
	};
}