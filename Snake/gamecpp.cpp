#define white 0xffffff
#define green 0x00ff00
#define red 0xff0000
#define blue 0x0000ff
#define yellow 0xffff00
#define black 0
//1 - true
//0 - false
using namespace std;
float speeddivider = 45.0f;
struct Game
{
	int number = 0;
	float distancefactor = 1.5f;
	int score = 0;
	int digit1 = 0;
	int digit2 = -1;
	int numberleftsetx = 0;
	float posxapple = 0.0f;
	float posyapple = 0.0f;
	int numberrightsetx = 0;
	int twodigitalscorecount = 0;
	int screenx = 85;
	int screeny = 49;
	int numberupsety = 0;
	int numberdownsety = 0;
	int isnotdefault = 0;
	int defaultnum = 0;
	int gameOver = 0;
	int current_number_of_snake_tails = 1;
	float posses_of_tailsy[50] =
	{
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	};
	float posses_of_tailsx[50] =
	{
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	};
	int direction_of_snake_tails_up[50] =
	{
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
	};
	int direction_of_snake_tails_down[50] =
	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};
	int direction_of_snake_tails_right[50] =
	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};
	int direction_of_snake_tails_left[50] =
	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};
	int direction_of_snake_tails_default[50] =
	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
	};
	float movefactorx = 0.0f;
	float movefactory = 0.0f;
	int directions[5] =
	{
		0,
		0,
		0,
		0,
		1 // default up
	};
	float factor = 1.0f;
};
Game game;

static void KeysPress()
{
	//player
	if (GetKeyState('A') & 0x8000 || GetKeyState(VK_LEFT) & 0x8000)
	{
		for (int k = 0; k < 4; k++)
		{
			if (k == 0)
			{
				game.directions[k] = 1;
			}
			else
			{
				game.directions[k] = 0;
			}
		}
	}
	if (GetKeyState('D') & 0x8000 || GetKeyState(VK_RIGHT) & 0x8000)
	{
		for (int k = 0; k < 4; k++)
		{
			if (k == 1)
			{
				game.directions[k] = 1;
			}
			else
			{
				game.directions[k] = 0;
			}
		}
	}
	if (GetKeyState('W') & 0x8000 || GetKeyState(VK_UP) & 0x8000)
	{
		for (int k = 0; k < 4; k++)
		{
			if (k == 2)
			{
				game.directions[k] = 1;
			}
			else
			{
				game.directions[k] = 0;
			}
		}
	}
	if (GetKeyState('S') & 0x8000 || GetKeyState(VK_DOWN) & 0x8000)
	{
		for (int k = 0; k < 4; k++)
		{
			if (k == 3)
			{
				game.directions[k] = 1;
			}
			else
			{
				game.directions[k] = 0;
			}
		}
	}
}
static void process_dir(int index, int left, int right, int up, int down)
{
	game.direction_of_snake_tails_left[index] = left;
	game.direction_of_snake_tails_right[index] = right;
	game.direction_of_snake_tails_up[index] = up;
	game.direction_of_snake_tails_down[index] = down;
}
static void MoveLeft(int index)
{
	process_dir(index, 1, 0, 0, 0);
	game.posses_of_tailsx[index] = game.posses_of_tailsx[index] - game.factor / speeddivider;
}
static void MoveRight(int index)
{
	process_dir(index, 0, 1, 0, 0);
	game.posses_of_tailsx[index] = game.posses_of_tailsx[index] + game.factor / speeddivider;
}
static void MoveUp(int index)
{
	process_dir(index, 0, 0, 1, 0);
	game.posses_of_tailsy[index] = game.posses_of_tailsy[index] + game.factor / speeddivider;
}
static void MoveDown(int index)
{
	process_dir(index, 0, 0, 0, 1);
	game.posses_of_tailsy[index] = game.posses_of_tailsy[index] - game.factor / speeddivider;
}
static void Apple()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> x(-game.screenx, game.screenx);
	uniform_int_distribution<int> y(-game.screeny, game.screeny);
	game.posxapple = (float)x(mt);
	game.posyapple = (float)y(mt);
}
static void Start()
{
	if (game.number == 0)
	{
		Apple();
		game.current_number_of_snake_tails = 3;
		for (int g = 1; g < game.current_number_of_snake_tails; g++)
		{
			game.posses_of_tailsy[g] = game.posses_of_tailsy[g - 1] - game.distancefactor;
			if (g == game.current_number_of_snake_tails - 1)
			{
				game.number = 1;
			}
		}
	}
}
static void Move(int index, int obj)
{
	if (index == 0)
	{
		MoveLeft(obj);
	}
	if (index == 1)
	{
		MoveRight(obj);
	}
	if (index == 2)
	{
		MoveUp(obj);
	}
	if (index == 3)
	{
		MoveDown(obj);
	}
}
static void MoveDefaultUp(int index)
{
	game.posses_of_tailsy[index] = game.posses_of_tailsy[index] + game.factor / speeddivider;
}
static void CheckForGameOver()
{
	for (int j = 0; j < game.current_number_of_snake_tails; j++)
	{
		for (int h = 0; h < game.current_number_of_snake_tails; h++)
		{
			if (h != j)
			{
				if (round(game.posses_of_tailsx[j]) == round(game.posses_of_tailsx[h]) && round(game.posses_of_tailsy[j]) == round(game.posses_of_tailsy[h]))
				{
					game.gameOver = 1;
				}
			}
		}
	}
}
static void CheckForScore(int score)
{
	if (game.score > (game.twodigitalscorecount + 1) * 10)
	{
		game.twodigitalscorecount += 1;
	}
	if (score > 10 * (game.twodigitalscorecount+1) && score != 10 * (game.twodigitalscorecount + 1))
	{
		game.digit1 += 1;
		game.digit2 = game.twodigitalscorecount + 1;
	}
	if (score == 10 * (game.twodigitalscorecount + 1))
	{
		game.digit1 = 0;
		game.digit2 = game.twodigitalscorecount + 1;
	}
	if (score < ((game.twodigitalscorecount + 1) * 10) - 1 || score == 9 + (game.twodigitalscorecount * 10))
	{
		game.digit1 = game.digit1 + 1;
	}
}
static void ScoreSystem()
{
	if (game.score == 0)
	{
		if (game.score != (game.twodigitalscorecount + 1) * 11)
		{
			draw_score(game.digit1, game.digit2, 30.0f, 30.0f, 0xffffff);
		}
	}
	else
	{
		if (game.score != game.twodigitalscorecount * 11)
		{
			draw_score(game.digit1, game.digit2, 30.0f, 30.0f, 0xffffff);
		}
	}
	if (game.score != 0)
	{
		if (game.score == game.twodigitalscorecount * 11)
		{
			draw_numbers(game.twodigitalscorecount, 30.0f, 30.0f, 0xffffff);
			draw_numbers(game.twodigitalscorecount, 22.0f, 30.0f, 0xffffff);
		}
	}
}
static void simulategame()
{
	clear_screen(black);
	ScoreSystem();
	if (game.gameOver == 0)
	{
		KeysPress();
		Start();
		CheckForGameOver();
		if (round(game.posses_of_tailsx[0]) == round(game.posxapple) && round(game.posses_of_tailsy[0]) == round(game.posyapple))
		{
			Apple();
			game.current_number_of_snake_tails += 1;
			speeddivider += 6.0f;
			game.score += 1;
			CheckForScore(game.score);
			if (game.direction_of_snake_tails_left[game.current_number_of_snake_tails - 2] == 1)
			{
				game.posses_of_tailsy[game.current_number_of_snake_tails - 1] = game.posses_of_tailsy[game.current_number_of_snake_tails - 2];
				game.posses_of_tailsx[game.current_number_of_snake_tails - 1] = game.posses_of_tailsx[game.current_number_of_snake_tails - 2] + game.distancefactor;
				game.direction_of_snake_tails_left[game.current_number_of_snake_tails - 1] = 1;
			}
			if (game.direction_of_snake_tails_right[game.current_number_of_snake_tails - 2] == 1)
			{
				game.posses_of_tailsy[game.current_number_of_snake_tails - 1] = game.posses_of_tailsy[game.current_number_of_snake_tails - 2];
				game.posses_of_tailsx[game.current_number_of_snake_tails - 1] = game.posses_of_tailsx[game.current_number_of_snake_tails - 2] - game.distancefactor;
				game.direction_of_snake_tails_right[game.current_number_of_snake_tails - 1] = 1;
			}
			if (game.direction_of_snake_tails_up[game.current_number_of_snake_tails - 2] == 1)
			{
				game.posses_of_tailsx[game.current_number_of_snake_tails - 1] = game.posses_of_tailsx[game.current_number_of_snake_tails - 2];
				game.posses_of_tailsy[game.current_number_of_snake_tails - 1] = game.posses_of_tailsy[game.current_number_of_snake_tails - 2] - game.distancefactor;
				game.direction_of_snake_tails_up[game.current_number_of_snake_tails - 1] = 1;
			}
			if (game.direction_of_snake_tails_down[game.current_number_of_snake_tails - 2] == 1)
			{
				game.posses_of_tailsx[game.current_number_of_snake_tails - 1] = game.posses_of_tailsx[game.current_number_of_snake_tails - 2];
				game.posses_of_tailsy[game.current_number_of_snake_tails - 1] = game.posses_of_tailsy[game.current_number_of_snake_tails - 2] + game.distancefactor;
				game.direction_of_snake_tails_down[game.current_number_of_snake_tails - 1] = 1;
			}
		}
		//Simulate
		for (int h = 0; h < game.current_number_of_snake_tails; h++)
		{
			if (game.direction_of_snake_tails_left[h] == 0 && game.direction_of_snake_tails_right[h] == 0 && game.direction_of_snake_tails_up == 0 && game.direction_of_snake_tails_down[h] == 0)
			{
				game.direction_of_snake_tails_default[h] = 0; //default
			}
			if (game.direction_of_snake_tails_left[h] == 1 || game.direction_of_snake_tails_right[h] == 1 || game.direction_of_snake_tails_up[h] == 1 || game.direction_of_snake_tails_down[h] == 1)
			{
				game.direction_of_snake_tails_default[h] = 1; //not default
			}
			for (int k = 0; k < game.current_number_of_snake_tails; k++)
			{
				if (game.direction_of_snake_tails_default[k] == 0)
				{
					MoveDefaultUp(k);
				}
			}
		}
		for (int b = 1; b < game.current_number_of_snake_tails; b++)
		{
			for (int f = 0; f < 4; f++)
			{
				if (game.directions[f] == 1)
				{
					Move(f, 0);
				}
			}
			for (int jleft = 0; jleft < game.current_number_of_snake_tails; jleft++)
			{
				if (game.direction_of_snake_tails_left[jleft + 1] == 1)
				{
					Move(0,jleft + 1);
				}
			}
			for (int jright = 0; jright < game.current_number_of_snake_tails; jright++)
			{
				if (game.direction_of_snake_tails_right[jright + 1] == 1)
				{
					Move(1,jright + 1);
				}
			}
			for (int jup = 0; jup < game.current_number_of_snake_tails; jup++)
			{
				if (game.direction_of_snake_tails_up[jup + 1] == 1)
				{
					Move(2,jup + 1);
				}
			}
			for (int jdo = 0; jdo < game.current_number_of_snake_tails; jdo++)
			{
				if (game.direction_of_snake_tails_down[jdo + 1] == 1)
				{
					Move(3,jdo + 1);
				}
			}
			if (game.direction_of_snake_tails_default[b - 1] == 1)
			{
				//left
				for (int i = 1; i < game.current_number_of_snake_tails; i++)
				{
					if (game.direction_of_snake_tails_left[i] == 0 && game.direction_of_snake_tails_left[i - 1] == 1)
					{
						game.numberleftsetx = 0;
						if (round(game.posses_of_tailsy[i]) == round(game.posses_of_tailsy[i - 1]))
						{
							Move(0, i);
							if (game.numberleftsetx == 0)
							{
								game.posses_of_tailsy[i] = game.posses_of_tailsy[i - 1];
								game.posses_of_tailsx[i] = game.posses_of_tailsx[i - 1] + game.distancefactor;
								game.numberleftsetx = 1;
							}
						}
					}
				}
				//right
				for (int i = 1; i < game.current_number_of_snake_tails; i++)
				{
					if (game.direction_of_snake_tails_right[i] == 0 && game.direction_of_snake_tails_right[i - 1] == 1)
					{
						game.numberrightsetx = 0;
						if (round(game.posses_of_tailsy[i]) == round(game.posses_of_tailsy[i - 1]))
						{
							Move(1, i);
							if (game.numberrightsetx == 0)
							{
								game.posses_of_tailsy[i] = game.posses_of_tailsy[i - 1];
								game.posses_of_tailsx[i] = game.posses_of_tailsx[i - 1] - game.distancefactor;
								game.numberrightsetx = 1;
							}
						}
					}
				}
				//up
				for (int i = 1; i < game.current_number_of_snake_tails; i++)
				{
					if (game.direction_of_snake_tails_up[i] == 0 && game.direction_of_snake_tails_up[i - 1] == 1)
					{
						game.numberupsety = 0;
						if (round(game.posses_of_tailsx[i]) == round(game.posses_of_tailsx[i - 1]))
						{
							Move(2, i);
							if (game.numberupsety == 0)
							{
								game.posses_of_tailsx[i] = game.posses_of_tailsx[i - 1];
								game.posses_of_tailsy[i] = game.posses_of_tailsy[i - 1] - game.distancefactor;
								game.numberupsety = 1;
							}
						}
					}
				}
			}
			//down
			for (int i = 1; i < game.current_number_of_snake_tails; i++)
			{
				if (game.direction_of_snake_tails_down[i] == 0 && game.direction_of_snake_tails_down[i - 1] == 1)
				{
					game.numberdownsety = 0;
					if (round(game.posses_of_tailsx[i]) == round(game.posses_of_tailsx[i - 1]))
					{
						Move(3,i);
						if (game.numberdownsety == 0)
						{
							game.posses_of_tailsx[i] = game.posses_of_tailsx[i - 1];
							game.posses_of_tailsy[i] = game.posses_of_tailsy[i - 1] + game.distancefactor;
							game.numberdownsety = 1;
						}
					}
				}
			}
		}
		for (int y = 0; y < game.current_number_of_snake_tails; y++)
		{
			draw_rect(game.posses_of_tailsx[y], game.posses_of_tailsy[y], 1, 1, green);
		}
		draw_rect(game.posxapple, game.posyapple, 1, 1, blue);
		////left
	//if (dir == 0)
	//{
	//	for (int x = 0; x < game.current_number_of_snake_tails; x++)
	//	{
	//		if (round(game.true_posses_y_up[x]) == round(game.true_posses_y_up[x - 1]))
	//		{
	//			process_dir(1, 0, 0, 0);
	//			game.posses_of_tailsy[x] = game.posses_of_tailsy[x - 1];
	//		}
	//	}
	//}
	////right
	//if (dir == 1)
	//{
	//	for (int x = 0; x < game.current_number_of_snake_tails; x++)
	//	{
	//		if (round(game.true_posses_y_up[x]) == round(game.true_posses_y_up[x - 1]))
	//		{
	//			for (int s = 0; s < 5; s++)
	//			{
	//				process_dir(0, 1, 0, 0);
	//				game.posses_of_tailsy[x] = game.posses_of_tailsy[x - 1];
	//			}
	//		}
	//	}
	//}
	////up
	//if (dir == 2)
	//{
	//	for (int x = 0; x < game.current_number_of_snake_tails; x++)
	//	{
	//		if (round(game.true_posses_x_left[x]) == round(game.true_posses_x_left[x - 1]))
	//		{
	//			for (int s = 0; s < 5; s++)
	//			{
	//				process_dir(0, 0, 1, 0);
	//				game.posses_of_tailsx[x] = game.posses_of_tailsx[x - 1];
	//			}
	//		}
	//	}
	//}
	////down
	//if (dir == 3)
	//{
	//	for (int x = 0; x < game.current_number_of_snake_tails; x++)
	//	{
	//		if (round(game.true_posses_x_left[x]) == round(game.true_posses_x_left[x - 1]))
	//		{
	//			process_dir(0, 0, 0, 1);
	//			game.posses_of_tailsx[x] = game.posses_of_tailsx[x - 1];
	//		}
	//	}
	//}
	}
}