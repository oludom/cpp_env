// -*- c++ -*-
// This is the header-only implementation of the uUnit unit-test framework.
// Copyright 2020 Bent Bisballe Nyeng (deva@aasimon.org)
// This file released under the CC0-1.0 license. See CC0-1.0 file for details.
#pragma once

#include <cstddef>
#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <exception>
#include <typeinfo>

class uUnit
{
public:
	uUnit()
	{
		if(uUnit::suite_list == nullptr)
		{
			uUnit::suite_list = this;
			return;
		}

		auto unit = uUnit::suite_list;
		while(unit->next_unit)
		{
			unit = unit->next_unit;
		}
		unit->next_unit = this;
	}

	virtual ~uUnit() = default;

	//! Overload to prepare stuff for each of the tests.
	virtual void setup() {}

	//! Overload to tear down stuff for each of the tests.
	virtual void teardown() {}

	struct test_result
	{
		std::string func;
		std::string file;
		std::size_t line;
		std::string msg;
		std::string failure_type;
		std::size_t id;
	};

	//! Run test
	//! \param test_suite the name of a test suite or null for all.
	//! \param test_name the name of a test name inside a test suite. Only valid
	//!  if test_suite is non-null. nullptr for all tests.
	static int runTests(std::ofstream& out)
	{
		std::size_t test_num{0};

		std::list<test_result> failed_tests;
		std::list<test_result> successful_tests;

		for(auto suite = uUnit::suite_list; suite; suite = suite->next_unit)
		{
			for(const auto& test : suite->tests)
			{
				++test_num;
				try
				{
					try
					{
						suite->setup();
						test.func();
					}
					catch(...)
					{
						// call teardown and ignore exceptions
						try { suite->teardown(); } catch(...) {}
						throw; // rethrow setup/test.func exception
					}
					suite->teardown();
				}
				catch(test_result& result)
				{
					status_cb(test.name, test.file, false);
					result.id = test_num;
					result.func = test.name;
					result.failure_type = "Assertion";
					failed_tests.push_back(result);
					continue;
				}
				catch(...)
				{
					status_cb(test.name, test.file, false);
					test_result result;
					result.id = test_num;
					result.func = test.name;
					result.file = test.file;
					result.line = 0;
					try
					{
						throw;
					}
					catch(std::exception& e)
					{
						result.msg = std::string("Uncaught exception: ") + e.what();
					}
					catch(...)
					{
						result.msg = "Uncaught exception without std::exception type";
					}
					result.failure_type = "Exception";
					failed_tests.push_back(result);
					continue;
				}
				status_cb(test.name, test.file, true);
				test_result result{test.name, {}, {}, {}, {}, {}};
				result.id = test_num;
				successful_tests.push_back(result);
			}
		}

		out << "<?xml version=\"1.0\" encoding='ISO-8859-1' standalone='yes' ?>" <<
			std::endl;
		out << "<TestRun>" << std::endl;
		out << "	<FailedTests>" << std::endl;
		for(const auto& test : failed_tests)
		{
			out << "		<FailedTest id=\"" << test.id << "\">" << std::endl; // constexpr newline cross-platform specifik
			out << "			<Name>" << sanitize(test.func) << "</Name>" << std::endl;
			out << "			<FailureType>" << sanitize(test.failure_type) <<
				"</FailureType>" << std::endl;
			out << "			<Location>" << std::endl;
			out << "				<File>" << sanitize(test.file) << "</File>" << std::endl;
			out << "				<Line>" << test.line << "</Line>" << std::endl;
			out << "			</Location>" << std::endl;
			out << "			<Message>" << sanitize(test.msg) << "</Message>" <<
				std::endl;
			out << "		</FailedTest>" << std::endl;
		}
		out << "	</FailedTests>" << std::endl;
		out << "	<SuccessfulTests>" << std::endl;
		for(const auto& test : successful_tests)
		{
			out << "		<Test id=\"" << test.id << "\">" << std::endl;
			out << "			<Name>" << sanitize(test.func) << "</Name>" << std::endl;
			out << "		</Test>" << std::endl;

		}
		out << "	</SuccessfulTests>" << std::endl;
		out << "	<Statistics>" << std::endl;
		out << "		<Tests>" << (successful_tests.size() + failed_tests.size()) <<
			"</Tests>" << std::endl;
		out << "		<FailuresTotal>" << failed_tests.size() << "</FailuresTotal>" <<
			std::endl;
		out << "		<Errors>0</Errors>" << std::endl;
		out << "		<Failures>" << failed_tests.size() << "</Failures>" <<
			std::endl;
		out << "	</Statistics>" << std::endl;
		out << "</TestRun>" << std::endl;

		return failed_tests.size() == 0 ? 0 : 1;
	}

	static std::function<void(const char*, const char*, bool)> status_cb;

	static void u_assert(bool value, const char* expr,
	                     const char* file, std::size_t line)
	{
		if(!value)
		{
			std::ostringstream ss;
			ss << "assertion failed" << std::endl <<
				"- Expression: " << expr << "" << std::endl;
			throw test_result{"", file, line, ss.str(), {}, {}};
		}
	}
	//! Convenience macro to pass along filename and linenumber
	#define uUNIT_ASSERT(value)	  \
		uUnit::u_assert(value, #value, __FILE__, __LINE__)
	#define uASSERT(...) uUNIT_ASSERT(__VA_ARGS__)

	static void assert_equal(double expected, double value,
	                         const char* file, std::size_t line)
	{
		if(std::fabs(expected - value) > 0.0000001)
		{
			std::ostringstream ss;
			ss << "equality assertion failed" << std::endl <<
				"- Expected: " << expected << "" << std::endl <<
				"- Actual  : " << value << "" << std::endl;
			throw test_result{"", file, line, ss.str(), {}, {}};
		}
	}

	template<typename T, typename U>
	static void assert_equal(const T& expected, const U& value,
	                         const char* file, std::size_t line)
	{
		if(expected != value)
		{
			std::ostringstream ss;
			ss << "equality assertion failed" << std::endl <<
				"- Expected: " << expected << "" << std::endl <<
				"- Actual  : " << value << "" << std::endl;
			throw test_result{"", file, line, ss.str(), {}, {}};
		}
	}
	//! Convenience macro to pass along filename and linenumber
	#define uUNIT_ASSERT_EQUAL(expected, value) \
		uUnit::assert_equal(expected, value, __FILE__, __LINE__)
	#define uASSERT_EQUAL(...) uUNIT_ASSERT_EQUAL(__VA_ARGS__)

	template<typename T>
	static void assert_throws(const char* expected, std::function<void()> expr,
	                          const char* file, std::size_t line)
	{
		try
		{
			expr();
			std::ostringstream ss;
			ss << "throws assertion failed" << std::endl <<
				"- Expected: " << expected << " to be thrown" << std::endl <<
				"- Actual  : no exception was thrown" << std::endl;
			throw test_result{"", file, line, ss.str(), {}, {}};
		}
		catch(const T& t)
		{
			// T was thrown as expected
		}
		catch(...)
		{
			std::ostringstream ss;
			ss << "throws assertion failed" << std::endl <<
				"- Expected: " << expected << " to be thrown" << std::endl <<
				"- Actual  : unexpected exception was thrown" << std::endl;
			throw test_result{"", file, line, ss.str(), {}, {}};
		}
	}
	#define uUNIT_ASSERT_THROWS(expected, expr) \
		uUnit::assert_throws<expected>(#expected, [&](){expr;}, __FILE__, __LINE__)
	#define uASSERT_THROWS(...) uUNIT_ASSERT_THROWS(__VA_ARGS__)

protected:
	template<typename O, typename F>
	void registerTest(O* obj, const F& fn, const char* name, const char* file)
	{
		tests.push_back({std::bind(fn, obj), name, file});
	}
	#define uUNIT_TEST(func)	  \
		registerTest(this, &func, #func, __FILE__)
	#define uTEST(...) uUNIT_TEST(__VA_ARGS__)

private:
	static std::string sanitize(const std::string& input)
	{
		std::string output;
		for(auto c : input)
		{
			switch(c)
			{
			case '"':
				output += "&quot;";
				break;
			case '&':
				output += "&amp;";
				break;
			case '<':
				output += "&lt;";
				break;
			case '>':
				output += "&gt;";
				break;
			default:
				output += c;
				break;
			}
		}
		return output;
	}

	static uUnit* suite_list;
	uUnit* next_unit{nullptr};

	struct test_t
	{
		std::function<void()> func;
		const char* name;
		const char* file;
	};

	std::vector<test_t> tests;
};

#ifdef uUNIT_MAIN

uUnit* uUnit::suite_list{nullptr};

namespace
{
//! Default implementation of test result reporter function.
//! Overload this with your own implementation by assigning the uUnit::status_cb
//! function pointer to a function with the same signature.
void report_result(const char* name, const char* file, bool success)
{
	(void)name;
	(void)file;
	if(success)
	{
		std::cout << ".";
	}
	else
	{
		std::cout << "F";
	}
	std::cout << std::flush;
}
}

std::function<void(const char*, const char*, bool)> uUnit::status_cb{report_result};

#endif
