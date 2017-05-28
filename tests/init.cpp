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
    REQUIRE(obj.search(2) != 0);
    REQUIRE(obj.search(5) == 0);
  }
  
  SCENARIO("Color_check", "[color]")
  {
  	RBT<int> obj; 							//const bool BLACK = 1
 	 obj.search(1);           						//const bool RED = 0;
 	 obj.search(2);
 	 obj.search(3);
  	REQUIRE(obj._color(2) != 0);
  	REQUIRE(obj._color(1) == 0);
  	REQUIRE(obj._color(3) == 0);
  }
