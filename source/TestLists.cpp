#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Lists.hpp"


TEST_CASE("empty(), size, default constructor", "[aufg_1]"){
    List<int> test{};
    REQUIRE(test.empty());
    REQUIRE(test.size() == 0);
}

TEST_CASE("add an element with push_front" , "[modifiers]")
{
    List<int> list;
    list.push_front(42);
    REQUIRE(42 == list.front());
    list.push_front(100);
    REQUIRE(100 == list.front());
    REQUIRE(42 == list.back());
}

TEST_CASE("add an element with push_back" , "[modifiers]")
{
    List<int> list;
    list.push_back(42);
    REQUIRE(42 == list.front());
    REQUIRE(42 == list.back());
    list.push_back(100);
    REQUIRE(42 == list.front());
    REQUIRE(100 == list.back());
}

TEST_CASE("pop_back", "[modifiers]"){
    List<int> list;
    list.push_back(42);
    list.push_back(100);
    list.pop_back();
    REQUIRE(42 == list.front());
    list.pop_back();
    REQUIRE(list.empty());
}

TEST_CASE("pop_front", "[modifiers]"){
    List<int> list;
    list.push_front(42);
    list.push_front(100);
    list.pop_front();
    REQUIRE(42 == list.front());
    list.pop_front();
    REQUIRE(list.empty());
}

TEST_CASE("should be empty after clearing" , "[modifiers]")
{
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    list.clear();
    REQUIRE(list.empty());
    ListNode<std::string>* node = new ListNode<std::string>{"lol"};
    ListIterator<std::string> b{node};
    std::string c = *b;
}