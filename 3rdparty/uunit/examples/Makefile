# Add more tests here
TESTS=\
	test_ExampleTest

CXX ?= g++
CXXFLAGS ?= -g -std=c++17 -Wall -Werror -Wextra -Wconversion -I..

all: ${TESTS}

check: all
	@F="0"; \
		for T in ${TESTS}; do echo; echo -n "$$T: "; ./$$T 2> $$T.log; F=$$(($$F+$$?)); done; \
		echo; echo '-----'; echo "Failed tests: $$F"; echo '-----'; \
		[ $$F -eq 0 ]

EXAMPLE_TEST_SRC = \
	getbaud.cc \
	ExampleTest.cc
test_ExampleTest: $(EXAMPLE_TEST_SRC)
	$(CXX) $(CXXFLAGS) -DOUTPUT=\"$@\" -o $@ ../uunit.cc $(EXAMPLE_TEST_SRC)

clean:
	rm -f ${TESTS}
	rm -f *.xml
	rm -f *.log
