#include <RBT.hpp>
#include <catch.hpp>

SCENARIO ("init", "[init]")
{
  RBT<int> obj;
  REQUIRE(obj._root()==obj._NIL());
}

SCENARIO("findNode&insert", "[find_node]")
  {
    RBT<int> obj;
    obj.insert(4);
    obj.insert(2);
    REQUIRE(obj.findNode(2) == 1);
	REQUIRE(obj.findNode(5) ==0)
  }
  
  SCENARIO("Color_check", "[color]")
{
  RedBlackTree<int> obj; 						//const bool BLACK = 1
  obj.insert(1);           						//const bool RED = 0;
  obj.insert(2);
  obj.insert(3);
  REQUIRE(obj._color(2) == 1);
  REQUIRE(obj._color(1) == 0);
  REQUIRE(obj._color(3) == 0);
}