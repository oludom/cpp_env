#pragma once

enum class Speed
{
	B0,
	B50,
	B75,
	B110,
	B134,
	B150,
	B200,
	B300,
	B600,
	B1200,
	B1800,
	B2400,
	B4800,
	B9600,
	B19200,
	B38400,
	B57600,
	B115200,
	B230400,
};

//! Exception
struct bad_speed {};

//! Convert requested int based speed to corresponding Speed enum class value.
//! The returned enum class value is the closest value not bigger than the
//! requested int value.
//! If no matching enum class value is found a bad_speed exception is thrown.
Speed getBaud(int speed);
