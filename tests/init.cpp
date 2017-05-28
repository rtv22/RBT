#include <RBT.hpp>
#include <catch.hpp>

SCENARIO ("init", "[init]")
{
  RBT<int> test;
  REQUIRE(test._root() == test._NIL());
}

SCENARIO("insert", "[init]")
{
  RBT<int> test;
  test.insert(1);
  REQUIRE(test.search(1) != 0);
}

SCENARIO("insert_1", "[init]")
{
  RBT<int> tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  REQUIRE(tree._root() == tree.search(2));
  REQUIRE(tree._color(2) == 1);
  REQUIRE(tree._color(1) == 0);
  REQUIRE(tree._color(3) == 0);
  REQUIRE(tree.search(1) != 0);
  REQUIRE(tree.search(2) != 0);
  REQUIRE(tree.search(3) != 0);
}
