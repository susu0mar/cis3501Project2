#pragma once
class Node {

public:
	int value;
	int repeat;
	int height;
	Node* left;
	Node* right;

	Node(int item) { //default constructor to set values

		value = item;
		repeat = 0;
		height = 1;
		left = NULL;
		right = NULL;
	}
};