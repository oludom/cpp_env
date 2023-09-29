#include "getbaud.h"

Speed getBaud(int speed)
{
	struct
	{
		int value;
		Speed speed;
	}
	speeds[] =
		{
			{      0,      Speed::B0 },
			{     50,     Speed::B50 },
			{     75,     Speed::B75 },
			{    110,    Speed::B110 },
			{    134,    Speed::B134 },
			{    150,    Speed::B150 },
			{    200,    Speed::B200 },
			{    300,    Speed::B300 },
			{    600,    Speed::B600 },
			{   1200,   Speed::B1200 },
			{   1800,   Speed::B1800 },
			{   2400,   Speed::B2400 },
			{   4800,   Speed::B4800 },
			{   9600,   Speed::B9600 },
			{  19200,  Speed::B19200 },
			{  38400,  Speed::B38400 },
			{  57600,  Speed::B57600 },
			{ 115200, Speed::B115200 },
			{ 230400, Speed::B230400 },
		};

	if(speed < 0)
	{
		throw bad_speed();
	}

	for(const auto& s : speeds)
	{
		if(speed == s.value)
		{
			return s.speed;
		}

		if(speed < s.value)
		{
			return (*((&s)-1)).speed;
		}
	}

	return speeds[sizeof(speeds) / sizeof(*speeds) - 1].speed;
}
