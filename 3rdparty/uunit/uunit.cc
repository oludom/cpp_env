// -*- c++ -*-
// This is the uUnit main file.
// Copyright 2020 Bent Bisballe Nyeng (deva@aasimon.org)
// This file released under the CC0-1.0 license. See CC0-1.0 file for details.

#define uUNIT_MAIN
#include "uunit.h"

#include <fstream>

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;
	std::ofstream xmlfile;
	xmlfile.open("result_" OUTPUT ".xml");
	return uUnit::runTests(xmlfile);
}
