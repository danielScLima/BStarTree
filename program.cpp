// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "bStarTree.h"

bool checkVectorOfEntriesInNode(NodeOfBStarTree* node, std::vector<int> vec)
{
	if (node->getVectorOfEntries().size() != vec.size())
		return false;
	
	for (int index = 0; index < vec.size(); ++index)
	{
		if (node->getVectorOfEntries().at(index) != vec.at(index))
			return false;
	}
	
	return true;
}

bool checkCountOfChilds(NodeOfBStarTree* node, int count)
{
	return node->getVectorOfPointers().size() == count;
}

TEST_CASE( "Testing the insert call in the bstartree", "[single-file]" )
{
	BTreeStar b (5);
	b.insert(50);
	
	NodeOfBStarTree* root = b.getRoot();
	
	REQUIRE( root != nullptr);
	REQUIRE( checkVectorOfEntriesInNode(root, {50}));
	
	b.insert(40);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {40,50}));
	
	b.insert(60);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {40,50,60}));
	
	b.insert(70);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {40,50,60,70}));
	
	b.insert(80);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {60}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {70,80}));
	
	b.insert(90);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {60}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {70,80,90}));
	
	//100
	b.insert(100);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {60}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {70,80,90,100}));
	
	//110
	b.insert(110);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {80,90,100,110}));
	
	
	//120
	b.insert(120);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {80}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,110,120}));
	
	//130
	b.insert(130);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {70,110}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {80,90,100}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {120,130}));
	
	//101
	b.insert(101);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {70,110}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {80,90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {120,130}));
	
	//105
	b.insert(105);//to the right of the middle
	
	REQUIRE( checkVectorOfEntriesInNode(root, {70,105}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {80,90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {110,120,130}));
	
	//104
	b.insert(104);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {70,104}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {80,90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {105,110,120,130}));
	
	//103
	b.insert(103);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {80,104}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101,103}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {105,110,120,130}));
	
	//102
	b.insert(102);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {80,102,110}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104,105}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {120,130}));
	
	//90,100,101, 102,  103,104,105, 110, 120,130: 3
	
	
	
	//140
	b.insert(140);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {80,102,110}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104,105}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {120,130,140}));
	
	//150
	b.insert(150);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {80,102,110}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104,105}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {120,130,140,150}));
	
	//160
	b.insert(160);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {80,102,120}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104,105,110}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {130,140,150,160}));
	
	//170
	b.insert(170);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {80,102,110,150}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104,105}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {120,130,140}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(4), {160,170}));
	
	//103,104,105,110,120,130,140,150,160,170
	
	//180
	b.insert(180);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {80,102,110,150}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104,105}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {120,130,140}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(4), {160,170,180}));
	
	//190
	b.insert(190);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {80,102,110,150}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104,105}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {120,130,140}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(4), {160,170,180,190}));
	
	//200
	b.insert(200);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {80,102,110,160}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104,105}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {120,130,140,150}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(4), {170,180,190,200}));
	
	//210
	b.insert(210);
	root = b.getRoot();
	
	NodeOfBStarTree *left = root->pointerByIndex(0);
	NodeOfBStarTree *right = root->pointerByIndex(1);
	
	REQUIRE( checkVectorOfEntriesInNode(root, {110}));
	
	REQUIRE( checkVectorOfEntriesInNode(left, {80,102}));
	REQUIRE( checkVectorOfEntriesInNode(right, {150,190}));
	
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(2), {103,104,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(0), {120,130,140}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(1), {160,170,180}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(2), {200,210}));
	
	
	//120,130,140,150,160,170,180,190,200,210
}

TEST_CASE( "Testing the remove call in the bstartree", "[single-file]" )
{
	BTreeStar b (5);
	b.insert(50);
	b.insert(40);
	b.insert(60);
	b.insert(70);
	b.insert(80);
	b.insert(90);
	b.insert(100);
	b.insert(110);
	b.insert(120);
	b.insert(130);
	b.insert(101);
	b.insert(105);
	b.insert(104);
	b.insert(103);
	b.insert(102);
	b.insert(140);
	b.insert(150);
	b.insert(160);
	b.insert(170);
	b.insert(180);
	b.insert(190);
	b.insert(200);
	b.insert(210);
	
	//50,40,60,70,80,90,100,110,120,130,101,105,104,103,102,140,150,160,170,180,190,200,210
	
	NodeOfBStarTree *root = b.getRoot();
	NodeOfBStarTree *left = root->pointerByIndex(0);
	NodeOfBStarTree *right = root->pointerByIndex(1);
	REQUIRE( checkVectorOfEntriesInNode(root, {110}));
	REQUIRE( checkVectorOfEntriesInNode(left, {80,102}));
	REQUIRE( checkVectorOfEntriesInNode(right, {150,190}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(2), {103,104,105}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(0), {120,130,140}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(1), {160,170,180}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(2), {200,210}));
	
	
	b.remove(180);
	root = b.getRoot();
	left = root->pointerByIndex(0);
	right = root->pointerByIndex(1);
	REQUIRE( checkVectorOfEntriesInNode(root, {110}));
	
	REQUIRE( checkVectorOfEntriesInNode(left, {80,102}));
	REQUIRE( checkVectorOfEntriesInNode(right, {150,190}));
	
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(2), {103,104,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(0), {120,130,140}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(1), {160,170}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(2), {200,210}));
	
	b.remove(170);
	root = b.getRoot();
	left = root->pointerByIndex(0);
	right = root->pointerByIndex(1);
	REQUIRE( checkVectorOfEntriesInNode(root, {110}));
	
	REQUIRE( checkVectorOfEntriesInNode(left, {80,102}));
	REQUIRE( checkVectorOfEntriesInNode(right, {150,190}));
	
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(2), {103,104,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(0), {120,130,140}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(1), {160}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(2), {200,210}));
	
	b.remove(160);
	root = b.getRoot();
	left = root->pointerByIndex(0);
	right = root->pointerByIndex(1);
	REQUIRE( checkVectorOfEntriesInNode(root, {110}));
	
	REQUIRE( checkVectorOfEntriesInNode(left, {80,102}));
	REQUIRE( checkVectorOfEntriesInNode(right, {140,190}));
	
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(2), {103,104,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(0), {120,130}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(1), {150}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(2), {200,210}));
	
	b.remove(150);
	root = b.getRoot();
	left = root->pointerByIndex(0);
	right = root->pointerByIndex(1);
	REQUIRE( checkVectorOfEntriesInNode(root, {110}));
	
	REQUIRE( checkVectorOfEntriesInNode(left, {80,102}));
	REQUIRE( checkVectorOfEntriesInNode(right, {130,190}));
	
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(2), {103,104,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(0), {120}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(1), {140}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(2), {200,210}));
	
	b.remove(140);
	root = b.getRoot();
	left = root->pointerByIndex(0);
	right = root->pointerByIndex(1);
	REQUIRE( checkVectorOfEntriesInNode(root, {110}));
	
	REQUIRE( checkVectorOfEntriesInNode(left, {80,102}));
	REQUIRE( checkVectorOfEntriesInNode(right, {130,200}));
	
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(2), {103,104,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(0), {120}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(1), {190}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(2), {210}));
	
	b.remove(190);
	root = b.getRoot();
	left = root->pointerByIndex(0);
	right = root->pointerByIndex(1);
	REQUIRE( checkVectorOfEntriesInNode(root, {110}));
	
	REQUIRE( checkVectorOfEntriesInNode(left, {80,102}));
	REQUIRE( checkVectorOfEntriesInNode(right, {200}));
	
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(2), {103,104,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(0), {120,130}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(1), {210}));
	
	b.remove(130);
	root = b.getRoot();
	left = root->pointerByIndex(0);
	right = root->pointerByIndex(1);
	REQUIRE( checkVectorOfEntriesInNode(root, {110}));
	
	REQUIRE( checkVectorOfEntriesInNode(left, {80,102}));
	REQUIRE( checkVectorOfEntriesInNode(right, {200}));
	
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(left->pointerByIndex(2), {103,104,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(0), {120}));
	REQUIRE( checkVectorOfEntriesInNode(right->pointerByIndex(1), {210}));
	
	b.remove(210);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {80,102,110}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104,105}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {120,200}));
	
	b.remove(200);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {80,102,110}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104,105}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {120}));
	
	b.remove(120);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {80,102,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60,70}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {110}));
	
	b.remove(70);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {80,102,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50,60}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {110}));
	
	b.remove(60);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {80,102,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40,50}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {110}));
	
	b.remove(50);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {80,102,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {40}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {90,100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {110}));
	
	b.remove(40);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {90,102,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {80}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {100,101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {110}));
	
	b.remove(80);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {100,102,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {90}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {103,104}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(3), {110}));
	
	b.remove(90);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {102,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {100, 101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {103,104}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {110}));
	
	b.remove(100);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {102,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {101}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {103,104}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {110}));
	
	b.remove(101);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {103,105}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {102}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {104}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(2), {110}));
	
	b.remove(102);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {105}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {103,104}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {110}));
	
	b.remove(110);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {104}));
	
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(0), {103}));
	REQUIRE( checkVectorOfEntriesInNode(root->pointerByIndex(1), {105}));
	
	b.remove(105);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {103,104}));
	
	b.remove(104);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {103}));
	
	b.remove(103);
	root = b.getRoot();
	REQUIRE( checkVectorOfEntriesInNode(root, {}));
}

TEST_CASE( "Testing the search call in the bstartree", "[single-file]" )
{
	BTreeStar b (5);
	std::vector<int> toInsert = {50,40,60,70,80,90,100,110,120,130,101,105,104,103,102,140,150,160,170,180,190,200,210};
	
	for (auto number: toInsert)
		b.insert(number);
	
	for (auto number: toInsert)
		REQUIRE( b.search(number) != nullptr );
}

TEST_CASE( "Testing the search call in the bstartree, case 2", "[single-file]" )
{
	BTreeStar b (5);
	std::vector<int> toInsert = {50,40,60,70,80,90,100,110,120,130,101,105,104,103,102,140,150,160,170,180,190,200,210};
	std::vector<int> toRemove = {180,170,160};
	
	
	for (auto number: toInsert)
		b.insert(number);
	
	for (auto number: toInsert)
		REQUIRE( b.search(number) != nullptr );
	
	for (auto number: toRemove)
		b.remove(number);
	
	for (auto number: toRemove)
		REQUIRE( b.search(number) == nullptr );
}

TEST_CASE( "Testing the insert call with duplicated entries in the bstartree", "[single-file]" )
{
	BTreeStar b (5);
	REQUIRE(b.insert(50));
	REQUIRE(b.insert(40));
	REQUIRE(b.insert(60));
	REQUIRE(b.insert(70));
	
	REQUIRE(!b.insert(50));
	REQUIRE(!b.insert(40));
	REQUIRE(!b.insert(60));
	REQUIRE(!b.insert(70));
	
}

