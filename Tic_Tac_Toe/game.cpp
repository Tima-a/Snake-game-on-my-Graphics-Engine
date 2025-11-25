float x_ = 0.0f;
float y_ = 0.0f;
float a_ = 30.0f;

void create_cross(float x, float y, float a, unsigned int color)
{
	vector2d::draw_vector(x, y, x + a, y + a, PIXEL_SIZE, color);
	vector2d::draw_vector(x+a, y, x, y + a, PIXEL_SIZE, color);
}

void draw_grid(float x, float y, float a,unsigned int color)
{
	vector2d::draw_vector(x - a / 4.0f, y - a / 1.5f, x - a / 4.0f, y + a / 1.5f, PIXEL_SIZE, color);
	vector2d::draw_vector(x + a / 4.0f, y - a / 1.5f, x + a / 4.0f, y + a / 1.5f, PIXEL_SIZE, color);
	vector2d::draw_vector(x - a / 1.5f, y + a / 4.0f, x + a / 1.5f, y + a / 4.0f, PIXEL_SIZE, color);
	vector2d::draw_vector(x - a / 1.5f, y - a / 4.0f, x + a / 1.5f, y - a / 4.0f, PIXEL_SIZE, color);
}

float posxcross[3][3] = { {x_ - a_ / 1.5f, x_ - a_ / 4.65f, x_ + a_ / 3.5f}, {x_ - a_ / 1.5f, x_ - a_ / 4.65f, x_ + a_ / 3.5f}, {x_ - a_ / 1.5f, x_ - a_ / 4.65f, x_ + a_ / 3.5f} };
float posycross[3][3] = { {y_ + a_ / 3.55f, y_ + a_ / 3.55f, y_ + a_ / 3.55f}, {y_ - a_ / 4.65f, y_ - a_ / 4.65f, y_ - a_ / 4.65f}, {y_ - a_ / 1.5f, y_ - a_ / 1.5f, y_ - a_ / 1.5f} };
float posxcircle[3][3] = { {x_ - a_ / 2.1f, x_, x_ + a_ / 2.1f}, {x_ - a_ / 2.1f, x_, x_ + a_ / 2.1f}, {x_ - a_ / 2.1f, x_, x_ + a_ / 2.1f} };
float posycircle[3][3] = { {y_ + a_ /2.1f, y_ + a_ / 2.1f, y_ + a_ / 2.1f}, {y_, y_, y_}, {y_ - a_ / 2.1f, y_ - a_ / 2.1f, y_ - a_ / 2.1f} };

float posmousex[3][3] = { { 415.0f, 515.0f , 615.0f}, { 415.0f, 515.0f , 615.0f}, { 415.0f, 515.0f , 615.0f} };
float posmousexcheck[3][3] = { { 545.0f, 645.0f, 745.0f}, {545.0f, 645.0f, 745.0f}, {545.0f, 645.0f, 745.0f} };
float posmousey[3][3] = { { 200.0f, 200.0f, 200.0f}, {300.0f, 300.0f, 300.0f}, {400.0f, 400.0f, 400.0f} };
float posmouseycheck[3][3] = { { 340.0f, 340.0f, 340.0f}, {440.0f, 440.0f, 440.0f}, {540.0f, 540.0f, 540.0f} };

int matrixtable[3][3] // 1 - cross, 2 - circle
{
	{
		0,
		0,
		0
	},
	{
		0,
		0,
		0
	},
	{
		0,
		0,
		0
	}
};

//0 - computer, 1 - player
// 0 - nothing, 1 - cross, 2  - circle 
struct Game_Variables
{
	bool first_done = false;
	int default_structure_cross = 0;
	int default_structure_circle = 0;
	int structure_changed = true;
	int crossnum = 0;
	int circlenum = 0;
	int who_is_first = random(0,2);
	int who_is_first_assist = who_is_first;
	bool computer_won = false;
	bool player_won = false;
	bool end_game_ = false;
};
Game_Variables game_vars;

void simulategame()
{
	int stoploop = -1;
	int count_cross = 0;
	int count_circle = 0;
	bool turn_player = false;
	bool turn_computer = false;
	if (game_vars.first_done == false)
	{
		if (game_vars.who_is_first == 0)
		{
			turn_computer = true;
			turn_player = false;
		}
		if (game_vars.who_is_first == 1)
		{
			turn_computer = false;
			turn_player = true;
		}
		game_vars.first_done = true;
	}
	draw_grid(x_, y_, a_, green);
	float x = 0;
	float y = 0;
	HWND hWnd = FindWindow("Game Window Class", "Tic Tac Toe");
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(hWnd, &cursorPos);
	x = cursorPos.x;
	y = cursorPos.y;
	game_vars.crossnum = 0;
	game_vars.circlenum = 0;
	for (int h = 0; h < 3; h++)
	{
		for (int g = 0; g < 3; g++)
		{
			if (matrixtable[h][g] == 1)
			{
				game_vars.crossnum++;
			}
			if (matrixtable[h][g] == 2)
			{
				game_vars.circlenum++;
			}
			if (game_vars.who_is_first_assist == 0)
			{
				if (game_vars.crossnum == game_vars.circlenum)
				{
					turn_computer = true;
					turn_player = false;
				}
				if (game_vars.crossnum > game_vars.circlenum)
				{
					turn_computer = false;
					turn_player = true;
				}
			}
			if (game_vars.who_is_first_assist == 1)
			{
				if (game_vars.circlenum == game_vars.crossnum)
				{
					turn_computer = false;
					turn_player = true;
				}
				if (game_vars.crossnum > game_vars.circlenum)
				{
					turn_computer = true;
					turn_player = false;
				}
			}
		}
	}
	for (int k = 0; k < 3; k++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (matrixtable[k][j] != 0)
			{
				if (matrixtable[k][j] == 1)
				{
					create_cross(posxcross[k][j], posycross[k][j], 12.0f, red);
				}
				if (matrixtable[k][j] == 2)
				{
					circle::draw_circle(posxcircle[k][j], posycircle[k][j], 4.8f, 4.8f, red, false);
				}
			}
		}
	}
	if (game_vars.end_game_ == true)
	{
		turn_player = false;
		turn_computer = false;
		count_cross = -1;
		count_circle = -1;
		game_vars.crossnum = -1;
		game_vars.circlenum = -1;
	}
	if (turn_computer == true && turn_player == false)
	{
		if (game_vars.who_is_first_assist == 0)
		{
			int last_step = false;
			if (game_vars.crossnum == game_vars.circlenum)
			{
				count_cross = game_vars.crossnum;
			}
			for (int i = 0; i < 3; i++)
			{
				for (int a = 0; a < 3; a++)
				{
					for (int b = 0; b < 2; b++)
					{
						if (last_step == false)
						{
							if (count_cross == 3)
							{
								if (matrixtable[i][a] == b + 1 && matrixtable[i + 2][a + 2] == b + 1 && matrixtable[i + 1][a + 1] == 0)
								{
									if (a + 1 < 3 && a + 2 < 3 && i + 1 < 3 && i + 2 < 3)
									{
										if (b == 0)
										{
											last_step = true;
											create_cross(posxcross[i + 1][a + 1], posycross[i + 1][a + 1], 12.0f, red);
											matrixtable[i + 1][a + 1] = 1;
											count_cross = -1;
											game_vars.default_structure_cross = -1;
										}
										else if (b == 1)
										{
											last_step = true;
											create_cross(posxcross[i + 1][a + 1], posycross[i + 1][a + 1], 12.0f, red);
											matrixtable[i + 1][a + 1] = 1;
											count_cross = -1;
											game_vars.default_structure_cross = 1;
										}
										if (b == 1)
										{
											i = 2;
											a = 2;
											break;
										}
									}
								}
								if (matrixtable[i][a] == b + 1 && matrixtable[i - 1][a - 1] == b + 1 && matrixtable[i - 2][a - 2] == 0)
								{
									if (i - 1 > -1 && i - 2 > -1)
									{
										if (b == 0)
										{
											last_step = true;
											create_cross(posxcross[i - 2][a - 2], posycross[i - 2][a - 2], 12.0f, red);
											matrixtable[i - 2][a - 2] = 1;
											count_cross = -1;
											game_vars.default_structure_cross = -1;
										}
										else if (b == 1)
										{
											last_step = true;
											create_cross(posxcross[i + 2][a + 2], posycross[i + 2][a + 2], 12.0f, red);
											matrixtable[i + 2][a + 2] = 1;
											count_cross = -1;
											game_vars.default_structure_cross = 1;
										}
										if (b == 1)
										{
											i = 2;
											a = 2;
											break;

										}
									}
								}
								if (matrixtable[i][a] == b + 1 && matrixtable[i + 1][a + 1] == b + 1 && matrixtable[i + 2][a + 2] == 0)
								{
									if (a + 1 < 3 && a + 2 < 3 && i + 1 < 3 && i + 2 < 3)
									{
										if (b == 0)
										{
											last_step = true;
											create_cross(posxcross[i + 2][a + 2], posycross[i + 2][a + 2], 12.0f, red);
											matrixtable[i + 2][a + 2] = 1;
											count_cross = -1;
											game_vars.default_structure_cross = -1;
										}
										else if (b == 1)
										{
											last_step = true;
											create_cross(posxcross[i + 2][a + 2], posycross[i + 2][a + 2], 12.0f, red);
											matrixtable[i + 2][a + 2] = 1;
											count_cross = -1;
											game_vars.default_structure_cross = 1;
										}
										if (b == 1)
										{
											i = 2;
											a = 2;
											break;

										}
									}
								}
							}
							if (matrixtable[i][a] == b + 1 && matrixtable[i][a + 1] == b + 1 && matrixtable[i][a + 2] == 0)
							{
								if (a + 1 < 3 && a + 2 < 3)
								{
									if (b == 0)
									{
										last_step = true;
										create_cross(posxcross[i][a + 2], posycross[i][a + 2], 12.0f, red);
										matrixtable[i][a + 2] = 1;
										count_cross = -1;
										game_vars.default_structure_cross = -1;
									}
									else if (b == 1)
									{

										last_step = true;
										create_cross(posxcross[i][a + 2], posycross[i][a + 2], 12.0f, red);
										matrixtable[i][a + 2] = 1;
										count_cross = -1;
										game_vars.default_structure_cross = 1;
									}
									if (b == 1)
									{
										i = 2;
										a = 2;
										break;

									}
								}
							}
							if (matrixtable[i][a] == b + 1 && matrixtable[i][a - 1] == b + 1 && matrixtable[i][a - 2] == 0)
							{
								if (a - 2 > -1 && a - 1 > -1)
								{
									if (b == 0)
									{
										last_step = true;
										create_cross(posxcross[i][a - 2], posycross[i][a - 2], 12.0f, red);
										matrixtable[i][a - 2] = 1;
										count_cross = -1;
										game_vars.default_structure_cross = -1;
									}
									else if (b == 1)
									{
										last_step = true;
										create_cross(posxcross[i][a - 2], posycross[i][a - 2], 12.0f, red);
										matrixtable[i][a - 2] = 1;
										count_cross = -1;
										game_vars.default_structure_cross = 1;
									}
									if (b == 1)
									{
										i = 2;
										a = 2;
										break;

									}
								}
							}
							if (matrixtable[i][a] == b + 1 && matrixtable[i][a + 2] == b + 1 && matrixtable[i][a + 1] == 0)
							{
								if (a + 1 < 3 && a + 2 < 3)
								{
									if (b == 0)
									{
										last_step = true;
										create_cross(posxcross[i][a + 1], posycross[i][a + 1], 12.0f, red);
										matrixtable[i][a + 1] = 1;
										count_cross = -1;
										game_vars.default_structure_cross = -1;
									}
									else if (b == 1)
									{
										last_step = true;
										create_cross(posxcross[i][a + 1], posycross[i][a + 1], 12.0f, red);
										matrixtable[i][a + 1] = 1;
										count_cross = -1;
										game_vars.default_structure_cross = 1;
									}
									if (b == 1)
									{
										i = 2;
										a = 2;
										break;

									}
								}
							}
							if (matrixtable[i][a] == b + 1 && matrixtable[i + 1][a] == b + 1 && matrixtable[i + 2][a] == 0)
							{
								if (i + 1 < 3 && i + 2 < 3)
								{
									if (b == 0)
									{
										last_step = true;
										create_cross(posxcross[i + 2][a], posycross[i + 2][a], 12.0f, red);
										matrixtable[i + 2][a] = 1;
										count_cross = -1;
										game_vars.default_structure_cross = -1;
									}
									else if (b == 1)
									{
										last_step = true;
										create_cross(posxcross[i + 2][a], posycross[i + 2][a], 12.0f, red);
										matrixtable[i + 2][a] = 1;
										count_cross = -1;
										game_vars.default_structure_cross = 1;
									}
									if (b == 1)
									{
										i = 2;
										a = 2;
										break;

									}
								}
							}
							if (matrixtable[i][a] == b + 1 && matrixtable[i - 1][a] == b + 1 && matrixtable[i - 2][a] == 0)
							{
								if (i - 2 > -1 && i - 1 > -1)
								{
									if (b == 0)
									{
										last_step = true;
										create_cross(posxcross[i - 2][a], posycross[i - 2][a], 12.0f, red);
										matrixtable[i - 2][a] = 1;
										count_cross = -1;
										game_vars.default_structure_cross = -1;
									}
									else if (b == 1)
									{
										last_step = true;
										create_cross(posxcross[i - 2][a], posycross[i - 2][a], 12.0f, red);
										matrixtable[i - 2][a] = 1;
										count_cross = -1;
										game_vars.default_structure_cross = 1;
									}
									if (b == 1)
									{
										i = 2;
										a = 2;
										break;

									}
								}
							}
							if (matrixtable[i][a] == b + 1 && matrixtable[i + 2][a] == b + 1 && matrixtable[i + 1][a] == 0)
							{
								if (i + 1 < 3 && i + 2 < 3)
								{
									if (b == 0)
									{
										last_step = true;
										create_cross(posxcross[i + 1][a], posycross[i + 1][a], 12.0f, red);
										matrixtable[i + 1][a] = 1;
										count_cross = -1;
										game_vars.default_structure_cross = -1;
									}
									else if (b == 1)
									{
										last_step = true;
										create_cross(posxcross[i + 1][a], posycross[i + 1][a], 12.0f, red);
										matrixtable[i + 1][a] = 1;
										count_cross = -1;
										game_vars.default_structure_cross = 1;
									}
									if (b == 1)
									{
										i = 2;
										a = 2;
										break;
									}
								}
							}
						}
					}
				}
			}
			if (count_cross == 0)
			{
				if (game_vars.default_structure_cross == 0)
				{
					create_cross(posxcross[0][0], posycross[0][0], 12.0f, red);
					matrixtable[0][0] = 1;
				}
			}
			if (count_cross == 1)
			{
				if (game_vars.default_structure_cross == 0)
				{
					if (matrixtable[0][2] != 2)
					{
						create_cross(posxcross[0][2], posycross[0][2], 12.0f, red);
						matrixtable[0][2] = 1;
					}
					else if (matrixtable[0][2] == 2)
					{
						create_cross(posxcross[2][0], posycross[2][0], 12.0f, red);
						matrixtable[2][0] = 1;
						game_vars.structure_changed = true;
					}
				}
			}
			if (count_cross == 2)
			{
				if (game_vars.default_structure_cross == 0)
				{
					if (matrixtable[2][2] != 2)
					{
						create_cross(posxcross[2][2], posycross[2][2], 12.0f, red);
						matrixtable[2][2] = 1;
					}
					else if (matrixtable[2][2] == 2)
					{
						if (game_vars.structure_changed == false)
						{
							if (matrixtable[0][1] != 2)
							{
								create_cross(posxcross[0][1], posycross[0][1], 12.0f, red);
								matrixtable[0][1] = 1;
								last_step = true;
							}
							else
							{
								game_vars.structure_changed = true;
							}
						}
						if (game_vars.structure_changed == true)
						{
							create_cross(posxcross[1][0], posycross[1][0], 12.0f, red);
							matrixtable[1][0] = 1;
							last_step = true;
						}
					}
				}
			}
			if (count_cross == 3)
			{
				if (game_vars.default_structure_cross == 1)
				{
					for (int j = 0; j < 3; j++)
					{
						for (int k = 0; k < 3; k++)
						{
							if (matrixtable[j][k] == 0)
							{
								create_cross(posxcross[j][k], posycross[j][k], 12.0f, red);
								matrixtable[j][k] = 1;
								j = 2;
								k = 2;
							}
						}
					}
				}
			}
			if (count_cross == 4)
			{
				if (game_vars.default_structure_cross == 1)
				{
					for (int j = 0; j < 3; j++)
					{
						for (int k = 0; k < 3; k++)
						{
							if (matrixtable[j][k] == 0)
							{
								create_cross(posxcross[j][k], posycross[j][k], 12.0f, red);
								matrixtable[j][k] = 1;
								j = 2;
								k = 2;
							}
						}
					}
				}
				turn_computer = false;
				turn_player = true;
			}
		}
		if (game_vars.who_is_first_assist == 1)
		{
			int last_step = false;
			if (game_vars.crossnum > game_vars.circlenum)
			{
				count_circle = game_vars.circlenum;
			}
			for (int i = 0; i < 3; i++)
			{
				for (int a = 0; a < 3; a++)
				{
					int cannot = false;
					for (int b = 0; b < 2; b++)
					{
						if (last_step == 0)
						{
							if (count_circle == 2 || count_circle == 3)
							{
								if (matrixtable[i][a] == b + 1 && matrixtable[i + 2][a + 2] == b + 1 && matrixtable[i + 1][a + 1] == 0 && cannot == false)
								{
									if (a + 2 < 3 && i + 2 < 3)
									{
										cannot = true;
										if (b == 0)
										{
											last_step = true;
											circle::draw_circle(posxcircle[i + 1][a + 1], posycircle[i + 1][a + 1], 4.8f, 4.8f, red, false);
											matrixtable[i + 1][a + 1] = 2;
											count_circle = -1;
											game_vars.default_structure_circle = 1;
										}
										else if (b == 1)
										{
											last_step = true;
											circle::draw_circle(posxcircle[i + 1][a + 1], posycircle[i + 1][a + 1], 4.8f, 4.8f, red, false);
											matrixtable[i + 1][a + 1] = 2;
											count_circle = -1;
											game_vars.default_structure_circle = 1;
										}
										if (b == 1)
										{
											i = 2;
											a = 2;
											break;
										}
									}
								}
								if (matrixtable[i][a] == b + 1 && matrixtable[i - 1][a - 1] == b + 1 && matrixtable[i - 2][a - 2] == 0 && cannot == false)
								{
									if (a - 2 > -1 && i - 2 > -1)
									{
										cannot = true;
										if (b == 0)
										{
											last_step = true;
											circle::draw_circle(posxcircle[i - 2][a - 2], posycircle[i - 2][a - 2], 4.8f, 4.8f, red, false);
											matrixtable[i - 2][a - 2] = 2;
											count_circle = -1;
											game_vars.default_structure_circle = 1;
										}
										else if (b == 1)
										{
											last_step = true;
											circle::draw_circle(posxcircle[i - 2][a - 2], posycircle[i - 2][a - 2], 4.8f, 4.8f, red, false);
											matrixtable[i - 2][a - 2] = 2;
											count_circle = -1;
											game_vars.default_structure_circle = 1;
										}
										if (b == 1)
										{
											i = 2;
											a = 2;
											break;

										}
									}
								}
								if (matrixtable[i][a] == b + 1 && matrixtable[i + 1][a + 1] == b + 1 && matrixtable[i + 2][a + 2] == 0 && cannot == false)
								{
									if (a + 2 < 3 && i + 2 < 3)
									{
										cannot = true;
										if (b == 0)
										{
											last_step = true;
											circle::draw_circle(posxcircle[i + 2][a + 2], posycircle[i + 2][a + 2], 4.8f, 4.8f, red, false);
											matrixtable[i + 2][a + 2] = 2;
											count_circle = -1;
											game_vars.default_structure_circle = 1;
										}
										else if (b == 1)
										{
											last_step = true;
											circle::draw_circle(posxcircle[i + 2][a + 2], posycircle[i + 2][a + 2], 4.8f, 4.8f, red, false);
											matrixtable[i + 2][a + 2] = 2;
											count_circle = -1;
											game_vars.default_structure_circle = 1;
										}
										if (b == 1)
										{
											i = 2;
											a = 2;
											break;

										}
									}
								}
							}
							if (matrixtable[i][a] == b + 1 && matrixtable[i][a + 1] == b + 1 && matrixtable[i][a + 2] == 0 && cannot == false)
							{
								if (a + 2 < 3)
								{
									cannot = true;

									if (b == 0)
									{
										last_step = true;
										circle::draw_circle(posxcircle[i][a + 2], posycircle[i][a + 2], 4.8f, 4.8f, red, false);
										matrixtable[i][a + 2] = 2;
										count_circle = -1;
										game_vars.default_structure_circle = 1;
									}
									else if (b == 1)
									{

										last_step = true;
										circle::draw_circle(posxcircle[i][a + 2], posycircle[i][a + 2], 4.8f, 4.8f, red, false);
										matrixtable[i][a + 2] = 2;
										count_circle = -1;
										game_vars.default_structure_circle = 1;
									}
									if (b == 1)
									{
										i = 2;
										a = 2;
										break;

									}
								}
							}
							if (matrixtable[i][a] == b + 1 && matrixtable[i][a - 1] == b + 1 && matrixtable[i][a - 2] == 0 && cannot == false)
							{
								if (a - 2 > -1)
								{
									cannot = true;

									if (b == 0)
									{
										last_step = true;
										circle::draw_circle(posxcircle[i][a - 2], posycircle[i][a - 2], 4.8f, 4.8f, red, false);
										matrixtable[i][a - 2] = 2;
										count_circle = -1;
										game_vars.default_structure_circle = 1;
									}
									else if (b == 1)
									{
										last_step = true;
										circle::draw_circle(posxcircle[i][a - 2], posycircle[i][a - 2], 4.8f, 4.8f, red, false);
										matrixtable[i][a - 2] = 2;
										count_circle = -1;
										game_vars.default_structure_circle = 1;
									}
									if (b == 1)
									{
										i = 2;
										a = 2;
										break;

									}
								}
							}
							if (matrixtable[i][a] == b + 1 && matrixtable[i][a + 2] == b + 1 && matrixtable[i][a + 1] == 0 && cannot == false)
							{
								if (a + 2 < 3)
								{
									cannot = true;
									if (b == 0)
									{
										last_step = true;
										circle::draw_circle(posxcircle[i][a + 1], posycircle[i][a + 1], 4.8f, 4.8f, red, false);
										matrixtable[i][a + 1] = 2;
										count_circle = -1;
										game_vars.default_structure_circle = 1;
									}
									else if (b == 1)
									{
										last_step = true;
										create_cross(posxcross[i][a + 1], posycross[i][a + 1], 12.0f, red);
										matrixtable[i][a + 1] = 2;
										count_circle = -1;
										game_vars.default_structure_circle = 1;
									}
									if (b == 1)
									{
										i = 2;
										a = 2;
										break;

									}
								}
							}
							if (matrixtable[i][a] == b + 1 && matrixtable[i + 1][a] == b + 1 && matrixtable[i + 2][a] == 0 && cannot == false)
							{
								if (i + 2 < 3)
								{
									cannot = true;

									if (b == 0)
									{
										last_step = true;
										circle::draw_circle(posxcircle[i + 2][a], posycircle[i + 2][a], 4.8f, 4.8f, red, false);
										matrixtable[i + 2][a] = 2;
										count_circle = -1;
										game_vars.default_structure_circle = 1;
									}
									else if (b == 1)
									{
										last_step = true;
										circle::draw_circle(posxcircle[i + 2][a], posycircle[i + 2][a], 4.8f, 4.8f, red, false);
										matrixtable[i + 2][a] = 2;
										count_circle = -1;
										game_vars.default_structure_circle = 1;
									}
									if (b == 1)
									{
										i = 2;
										a = 2;
										break;

									}
								}
							}
							if (matrixtable[i][a] == b + 1 && matrixtable[i - 1][a] == b + 1 && matrixtable[i - 2][a] == 0 && cannot == false)
							{
								if (i - 2 > -1)
								{
									cannot = true;
									if (b == 0)
									{
										last_step = true;
										circle::draw_circle(posxcircle[i - 2][a], posycircle[i - 2][a], 4.8f, 4.8f, red, false);
										matrixtable[i - 2][a] = 2;
										count_circle = -1;
										game_vars.default_structure_circle = 1;
									}
									else if (b == 1)
									{
										last_step = true;
										circle::draw_circle(posxcircle[i - 2][a], posycircle[i - 2][a], 4.8f, 4.8f, red, false);
										matrixtable[i - 2][a] = 2;
										count_circle = -1;
										game_vars.default_structure_circle = 1;
									}
									if (b == 1)
									{
										i = 2;
										a = 2;
										break;

									}
								}
							}
							if (matrixtable[i][a] == b + 1 && matrixtable[i + 2][a] == b + 1 && matrixtable[i + 1][a] == 0 && cannot == false)
							{
								if (i + 2 < 3)
								{
									cannot = true;

									if (b == 0)
									{
										last_step = true;
										circle::draw_circle(posxcircle[i + 1][a], posycircle[i + 1][a], 4.8f, 4.8f, red, false);
										matrixtable[i + 1][a] = 2;
										count_circle = -1;
										game_vars.default_structure_circle = 1;
									}
									else if (b == 1)
									{
										last_step = true;
										circle::draw_circle(posxcircle[i + 1][a], posycircle[i + 1][a], 4.8f, 4.8f, red, false);
										matrixtable[i + 1][a] = 2;
										count_circle = -1;
										game_vars.default_structure_circle = 1;
									}
									if (b == 1)
									{
										i = 2;
										a = 2;
										break;
									}
								}
							}
						}
					}
				}
			}
			if (count_circle == 0)
			{
				if (game_vars.default_structure_circle == 0)
				{
					if (matrixtable[0][1] != 1)
					{
						circle::draw_circle(posxcircle[0][1], posycircle[0][1], 4.8f, 4.8f, red, false);
						matrixtable[0][1] = 2;
					}
					else if (matrixtable[0][1] == 1)
					{
						circle::draw_circle(posxcircle[0][0], posycircle[0][0], 4.8f, 4.8f, red, false);
						matrixtable[0][0] = 2;
					}
				}
			}
			if (count_circle == 1)
			{
				if (game_vars.default_structure_circle == 0)
				{
					if (matrixtable[2][2] != 1)
					{
						circle::draw_circle(posxcircle[2][2], posycircle[2][2], 4.8f, 4.8f, red, false);
						matrixtable[2][2] = 2;
					}
					else if (matrixtable[2][2] == 1)
					{
						if (matrixtable[0][2] != 1)
						{
							circle::draw_circle(posxcircle[0][2], posycircle[0][2], 4.8f, 4.8f, red, false);
							matrixtable[0][2] = 2;
						}
						else if (matrixtable[0][2] == 1)
						{
							circle::draw_circle(posxcircle[1][1], posycircle[1][1], 4.8f, 4.8f, red, false);
							matrixtable[1][1] = 2;
						}
					}
				}
			}
			if (count_circle == 2)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						if (matrixtable[j][k] == 0)
						{
							circle::draw_circle(posxcircle[j][k], posycircle[j][k], 4.8f, 4.8f, red, false);
							matrixtable[j][k] = 2;
							j = 2;
							k = 2;
						}
					}
				}
			}
			if (count_circle == 3)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						if (matrixtable[j][k] == 0)
						{
							circle::draw_circle(posxcircle[j][k], posycircle[j][k], 4.8f, 4.8f, red, false);
							matrixtable[j][k] = 2;
							j = 2;
							k = 2;
						}
					}
				}
			}
			if (count_circle == 4)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						if (matrixtable[j][k] == 0)
						{
							circle::draw_circle(posxcircle[j][k], posycircle[j][k], 4.8f, 4.8f, red, false);
							matrixtable[j][k] = 2;
							j = 2;
							k = 2;
						}
					}
				}
			}
			turn_player = true;
			turn_computer = false;
		}
	}
	if (turn_computer == false && turn_player == true)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int b = 0; b < 3; b++)
			{
				if (check_range(x, posmousex[i][b], posmousexcheck[i][b]))
				{
					if (check_range(y, posmousey[i][b], posmouseycheck[i][b]))
					{
						if ((GetKeyState(VK_LBUTTON) & 0x8000))
						{
							if (game_vars.who_is_first_assist == 1)
							{
								if (matrixtable[i][b] != 2)
								{
									create_cross(posxcross[i][b], posycross[i][b], 12.0f, red);
									matrixtable[i][b] = 1; //replace create_cross() here
									turn_player = false;
									turn_computer = true;
								}
							}
							if (game_vars.who_is_first_assist == 0)
							{
								if (matrixtable[i][b] != 1)
								{
									circle::draw_circle(posxcircle[i][b], posycircle[i][b], 4.8f, 4.8f, red, false);
									matrixtable[i][b] = 2; //replace create_cross() here
									turn_player = false;
									turn_computer = true;
								}
							}
							i = 2;
							b = 2;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int a = 0; a < 3; a++)
		{
			for (int g = 0; g < 2; g++)
			{

				if (matrixtable[i][a] == g + 1 && matrixtable[i][a + 1] == g + 1 && matrixtable[i][a + 2] == g + 1)
				{
					if (a == 0)
					{
						if (game_vars.who_is_first_assist == 0)
						{
							if (i == 0)
							{
								vector2d::draw_vector(posxcross[i][0], posycross[i][0] * 1.5f, posxcross[i][2] * 2.0f, posycross[i][2] * 1.5f, PIXEL_SIZE, green);
							}
							if (i == 1)
							{
								vector2d::draw_vector(posxcross[i][0], posycross[i][0] * 0.3f, posxcross[i][2] * 2.0f, posycross[i][2] * 0.3f, PIXEL_SIZE, green);
							}
							if (i == 2)
							{
								vector2d::draw_vector(posxcross[i][0], posycross[i][0] * 0.75f, posxcross[i][2] * 2.0f, posycross[i][2] * 0.75f, PIXEL_SIZE, green);
							}
							if (g == 0)
							{
								game_vars.computer_won = true;
								game_vars.player_won = false;
							}
							if (g == 1)
							{
								game_vars.computer_won = false;
								game_vars.player_won = true;
							}
						}
						if (game_vars.who_is_first_assist == 1)
						{
							if (i == 0)
							{
								vector2d::draw_vector(posxcross[i][0], posycross[i][0] * 1.5f, posxcross[i][2] * 2.0f, posycross[i][2] * 1.5f, PIXEL_SIZE, green);
							}
							if (i == 1)
							{
								vector2d::draw_vector(posxcross[i][0], posycross[i][0] * 0.3f, posxcross[i][2] * 2.0f, posycross[i][2] * 0.3f, PIXEL_SIZE, green);
							}
							if (i == 2)
							{
								vector2d::draw_vector(posxcross[i][0], posycross[i][0] * 0.75f, posxcross[i][2] * 2.0f, posycross[i][2] * 0.75f, PIXEL_SIZE, green);
							}
							if (g == 0)
							{
								game_vars.computer_won = false;
								game_vars.player_won = true;
							}
							if (g == 1)
							{
								game_vars.computer_won = true;
								game_vars.player_won = false;
							}
						}
						game_vars.end_game_ = true;
					}
				}
				if (matrixtable[i][a] == g + 1 && matrixtable[i + 1][a] == g + 1 && matrixtable[i + 2][a] == g + 1)
				{
					if (i == 0)
					{
						if (game_vars.who_is_first_assist == 0)
						{
							if (a == 0)
							{
								vector2d::draw_vector(posxcross[0][a] * 0.65f, posycross[0][a] * 2.0f, posxcross[2][a] * 0.65f, posycross[2][a], PIXEL_SIZE, green);
							}
							if (a == 1)
							{
								vector2d::draw_vector(posxcross[0][a] * 0.25f, posycross[0][a] * 2.0f, posxcross[2][a] * 0.25f, posycross[2][a], PIXEL_SIZE, green);
							}
							if (a == 2)
							{
								vector2d::draw_vector(posxcross[0][a] * 1.65f, posycross[0][a] * 2.0f, posxcross[2][a] * 1.65f, posycross[2][a], PIXEL_SIZE, green);
							}
							if (g == 0)
							{
								game_vars.computer_won = true;
								game_vars.player_won = false;
							}
							if (g == 1)
							{
								game_vars.computer_won = false;
								game_vars.player_won = true;
							}
						}
						if (game_vars.who_is_first_assist == 1)
						{
							if (a == 0)
							{
								vector2d::draw_vector(posxcross[0][a] * 0.65f, posycross[0][a] * 2.0f, posxcross[2][a] * 0.65f, posycross[2][a], PIXEL_SIZE, green);
							}
							if (a == 1)
							{
								vector2d::draw_vector(posxcross[0][a] * 0.25f, posycross[0][a] * 2.0f, posxcross[2][a] * 0.25f, posycross[2][a], PIXEL_SIZE, green);
							}
							if (a == 2)
							{
								vector2d::draw_vector(posxcross[0][a] * 1.65f, posycross[0][a] * 2.0f, posxcross[2][a] * 1.65f, posycross[2][a], PIXEL_SIZE, green);
							}
							if (g == 0)
							{
								game_vars.computer_won = false;
								game_vars.player_won = true;
							}
							if (g == 1)
							{
								game_vars.computer_won = true;
								game_vars.player_won = false;
							}
						}
						game_vars.end_game_ = true;
					}
				}
				if (matrixtable[i][a] == g + 1 && matrixtable[i + 1][a + 1] == g + 1 && matrixtable[i + 2][a + 2] == g + 1)
				{
					if (i == 0 && a == 0)
					{
						if (game_vars.who_is_first_assist == 0)
						{
							vector2d::draw_vector(posxcross[i][a], posycross[i][a] * 2.3f, posxcross[i + 2][a + 2] * 2.5f, posycross[i + 2][a + 2], PIXEL_SIZE, green);
							if (g == 0)
							{
								game_vars.computer_won = true;
								game_vars.player_won = false;
							}
							if (g == 1)
							{
								game_vars.computer_won = false;
								game_vars.player_won = true;
							}
						}
						if (game_vars.who_is_first_assist == 1)
						{
							vector2d::draw_vector(posxcross[i][a], posycross[i][a] * 2.3f, posxcross[i + 2][a + 2] * 2.5f, posycross[i + 2][a + 2], PIXEL_SIZE, green);
							if (g == 0)
							{
								game_vars.computer_won = false;
								game_vars.player_won = true;
							}
							if (g == 1)
							{
								game_vars.computer_won = true;
								game_vars.player_won = false;
							}
						}
						game_vars.end_game_ = true;
					}
				}
				if (matrixtable[i][a] == g + 1 && matrixtable[i + 1][a - 1] == g + 1 && matrixtable[i + 2][a - 2] == g + 1)
				{
					if (i == 0 && a == 2)
					{
						if (game_vars.who_is_first_assist == 0)
						{
							vector2d::draw_vector(posxcross[0][2] * 2.0f, posycross[0][2] * 1.5f, posxcross[2][0], posycross[2][0], PIXEL_SIZE, green);
							if (g == 0)
							{
								game_vars.computer_won = true;
								game_vars.player_won = false;
							}
							if (g == 1)
							{
								game_vars.computer_won = false;
								game_vars.player_won = true;
							}
						}
						if (game_vars.who_is_first_assist == 1)
						{
							vector2d::draw_vector(posxcross[0][2] * 2.0f, posycross[0][2] * 1.5f, posxcross[2][0], posycross[2][0], PIXEL_SIZE, green);
							if (g == 0)
							{
								game_vars.computer_won = false;
								game_vars.player_won = true;
							}
							if (g == 1)
							{
								game_vars.computer_won = true;
								game_vars.player_won = false;
							}
						}
						game_vars.end_game_ = true;
					}
				}
			}
		}
	}
}