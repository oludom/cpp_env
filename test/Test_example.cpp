#include "uunit.h"
#include <iostream>

class ExampleTest : public uUnit {
public:
  ExampleTest() {
    uTEST(ExampleTest::myTest);
    uTEST(ExampleTest::mySecondTest);
  }

  void myTest() { uASSERT_EQUAL(false, true); }
  void mySecondTest() { uASSERT_EQUAL(true, true); }
};

static ExampleTest exampleTest;