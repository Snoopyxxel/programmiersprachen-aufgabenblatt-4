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

}

TEST_CASE("iterator * and ->", "[iterator]"){
    ListNode<std::string>* node = new ListNode<std::string>{"lol"};
    ListIterator<std::string> b{node};
    std::string c = *b;
    REQUIRE(c.compare("lol") == 0);
    REQUIRE(b->compare("lol") == 0);
}

TEST_CASE("iterator operator++(), ==, !=, next()", "[iterators]"){
    ListNode<std::string>* node = new ListNode<std::string>{"0"};
    ListNode<std::string>* node1 = new ListNode<std::string>{"1"};
    ListNode<std::string>* node2 = new ListNode<std::string>{"2"};
    ListNode<std::string>* node3 = new ListNode<std::string>{"3"};
    ListNode<std::string>* node4 = new ListNode<std::string>{"4"};


    node->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    ListIterator<std::string> b{node};
    REQUIRE(b++->compare("0") == 0);
    REQUIRE((++b)->compare("2") == 0);
    REQUIRE(b->compare("2") == 0);
    ListIterator<std::string> c{node2};
    REQUIRE(c == b);
    REQUIRE(!(c != b));
    REQUIRE(b.next()->compare("3") == 0);
}

TEST_CASE("should be an empty range after default construction", "[iterators]"){
    List<int> list;
    auto b = list.begin();
    auto e = list.end();
    REQUIRE(b == e);
    REQUIRE(b.node == nullptr);
    REQUIRE(e.node == nullptr);
}
TEST_CASE("provide access to the first element with begin", "[iterators]"){
    List<int> list;
    list.push_front(42);
    REQUIRE (42 == *list.begin());
}
TEST_CASE("provide access to the last element with end", "[iterators]"){
    List<int> list;
    list.push_front(42);
    list.push_back(100);
    REQUIRE (100 == *list.end());
}

TEST_CASE("compare lists", "[compare]"){
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    List<int> list1;
    list1.push_front(1);
    list1.push_front(2);
    list1.push_front(3);
    list1.push_front(4);
    REQUIRE(list1 == list);
    REQUIRE(!(list1 != list));
    List<int> list_empty;
    List<int> list_empty1;
    REQUIRE(list_empty == list_empty1);
    REQUIRE(!(list_empty != list_empty1));

    REQUIRE(list_empty != list);
    REQUIRE(!(list_empty == list));


}