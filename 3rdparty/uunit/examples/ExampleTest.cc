#include <uunit.h>
#include <iostream>

#include "getbaud.h"

std::ostream& operator<<(std::ostream& stream, const Speed& speed)
{
	switch(speed)
	{
	case Speed::B0: stream << "Speed::B0"; break;
	case Speed::B50: stream << "Speed::B50"; break;
	case Speed::B75: stream << "Speed::B75"; break;
	case Speed::B110: stream << "Speed::B110"; break;
	case Speed::B134: stream << "Speed::B134"; break;
	case Speed::B150: stream << "Speed::B150"; break;
	case Speed::B200: stream << "Speed::B200"; break;
	case Speed::B300: stream << "Speed::B300"; break;
	case Speed::B600: stream << "Speed::B600"; break;
	case Speed::B1200: stream << "Speed::B1200"; break;
	case Speed::B1800: stream << "Speed::B1800"; break;
	case Speed::B2400: stream << "Speed::B2400"; break;
	case Speed::B4800: stream << "Speed::B4800"; break;
	case Speed::B9600: stream << "Speed::B9600"; break;
	case Speed::B19200: stream << "Speed::B19200"; break;
	case Speed::B38400: stream << "Speed::B38400"; break;
	case Speed::B57600: stream << "Speed::B57600"; break;
	case Speed::B115200: stream << "Speed::B115200"; break;
	case Speed::B230400: stream << "Speed::B230400"; break;
	}
	return stream;
}

class ExampleTest
	: public uUnit
{
public:
	ExampleTest()
	{
		uTEST(ExampleTest::boundaryTests);
		uTEST(ExampleTest::exceptionTests);
	}

	void boundaryTests()
	{
		uASSERT_EQUAL(Speed::B0, getBaud(0));
		uASSERT_EQUAL(Speed::B0, getBaud(1));
		uASSERT_EQUAL(Speed::B0, getBaud(49));

		uASSERT_EQUAL(Speed::B50, getBaud(50));
		uASSERT_EQUAL(Speed::B50, getBaud(51));
		uASSERT_EQUAL(Speed::B50, getBaud(74));

		uASSERT_EQUAL(Speed::B75, getBaud(75));
		uASSERT_EQUAL(Speed::B75, getBaud(76));
		uASSERT_EQUAL(Speed::B75, getBaud(109));

		uASSERT_EQUAL(Speed::B110, getBaud(110));
		uASSERT_EQUAL(Speed::B110, getBaud(111));
		uASSERT_EQUAL(Speed::B110, getBaud(133));

		uASSERT_EQUAL(Speed::B134, getBaud(134));
		uASSERT_EQUAL(Speed::B134, getBaud(135));
		uASSERT_EQUAL(Speed::B134, getBaud(149));

		uASSERT_EQUAL(Speed::B150, getBaud(150));
		uASSERT_EQUAL(Speed::B150, getBaud(151));
		uASSERT_EQUAL(Speed::B150, getBaud(199));

		uASSERT_EQUAL(Speed::B200, getBaud(200));
		uASSERT_EQUAL(Speed::B200, getBaud(201));
		uASSERT_EQUAL(Speed::B200, getBaud(299));

		uASSERT_EQUAL(Speed::B300, getBaud(300));
		uASSERT_EQUAL(Speed::B300, getBaud(301));
		uASSERT_EQUAL(Speed::B300, getBaud(599));

		uASSERT_EQUAL(Speed::B600, getBaud(600));
		uASSERT_EQUAL(Speed::B600, getBaud(601));
		uASSERT_EQUAL(Speed::B600, getBaud(1199));

		uASSERT_EQUAL(Speed::B1200, getBaud(1200));
		uASSERT_EQUAL(Speed::B1200, getBaud(1201));
		uASSERT_EQUAL(Speed::B1200, getBaud(1799));

		uASSERT_EQUAL(Speed::B1800, getBaud(1800));
		uASSERT_EQUAL(Speed::B1800, getBaud(1801));
		uASSERT_EQUAL(Speed::B1800, getBaud(2399));

		uASSERT_EQUAL(Speed::B2400, getBaud(2400));
		uASSERT_EQUAL(Speed::B2400, getBaud(2401));
		uASSERT_EQUAL(Speed::B2400, getBaud(4799));

		uASSERT_EQUAL(Speed::B4800, getBaud(4800));
		uASSERT_EQUAL(Speed::B4800, getBaud(4801));
		uASSERT_EQUAL(Speed::B4800, getBaud(9599));

		uASSERT_EQUAL(Speed::B9600, getBaud(9600));
		uASSERT_EQUAL(Speed::B9600, getBaud(9601));
		uASSERT_EQUAL(Speed::B9600, getBaud(19199));

		uASSERT_EQUAL(Speed::B19200, getBaud(19200));
		uASSERT_EQUAL(Speed::B19200, getBaud(19201));
		uASSERT_EQUAL(Speed::B19200, getBaud(38399));

		uASSERT_EQUAL(Speed::B38400, getBaud(38400));
		uASSERT_EQUAL(Speed::B38400, getBaud(38401));
		uASSERT_EQUAL(Speed::B38400, getBaud(57599));

		uASSERT_EQUAL(Speed::B57600, getBaud(57600));
		uASSERT_EQUAL(Speed::B57600, getBaud(57601));
		uASSERT_EQUAL(Speed::B57600, getBaud(115199));

		uASSERT_EQUAL(Speed::B115200, getBaud(115200));
		uASSERT_EQUAL(Speed::B115200, getBaud(115201));
		uASSERT_EQUAL(Speed::B115200, getBaud(230399));

		uASSERT_EQUAL(Speed::B230400, getBaud(230400));
		uASSERT_EQUAL(Speed::B230400, getBaud(230401));
	}

	void exceptionTests()
	{
		uASSERT_THROWS(bad_speed, getBaud(-1));
	}
};

// Registers the fixture into the 'registry'
static ExampleTest test;
