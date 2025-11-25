#include <cmath>
#include <time.h>


static int clamp(int min, int val, int max)
{
	if (val < min)
	{
		return min;
	}
	if (val > max)
	{
		return max;
	}
	return val;
}

static int random(int low, int high)
{
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	int seconds = ltm.tm_sec;
	int diff = high - low;
	int proportion_sec = 60 / diff;
	int num = 1;
	int numsec = -1;
	for (int i = 0; i < diff; i++)
	{
		int proportionsec_num = proportion_sec * num;
		int proportionsec_nummin = proportion_sec * (num - 1);
		if (seconds <= proportionsec_num && seconds >= proportionsec_nummin)
		{
			numsec = num - 1;
			break;
		}
		else
		{
			num++;
		}
	}
	int randomvalue = low + numsec;
	return randomvalue;
}

bool check_range(float k, float b /*  minimal value */, float c /*  maximum value */)
{
	if (fabs(k) > fabs(b) && fabs(k) < fabs(c))
	{
		return true;
	}
	else
	{
		return false;
	}
}

static unsigned int rgb(unsigned int r, unsigned int g, unsigned int b)
{
	unsigned int rgbnumber = (r << 16) + (g << 8) + b;
	return rgbnumber;
}
static bool neg_or_pos_num(float num)
{
	//neg - false, pos - true
	if (num / 1.0f == fabs(num))
	{
		return true;
	}
	else
	{
		return false;
	}
}
static bool check_number_type(float num)
{
	// if decimal - true, fractional - false
	if (num == round(num))
	{
		return true; // true
	}
	else
	{
		return false; // false
	}
}
static void swap(float& a, float& b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}
static void Break()
{
	int number = 0;
	int number2 = 5 / number;
}