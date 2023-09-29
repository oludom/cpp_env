#include <concepts>
#include <iostream>
#include <string>

template <typename T>
concept HasGetStr = requires(T a) {
  {
    a.get_str()
  } -> std::same_as<std::string>;
};

class Hello
{
public:
  std::string get_str() { return "Hello, "; }
};

class World
{
public:
  std::string get_str() { return "World!"; }
};

void print_get_str(HasGetStr auto first, HasGetStr auto second)
{
  std::cout << first.get_str() << second.get_str() << std::endl;
}

int main()
{
  Hello hello;
  World world;
  print_get_str(hello, world);
}
