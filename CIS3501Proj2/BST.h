#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"
using namespace std;



class BST
{
private:
	//root of tree
	Node* root;
	//integer to keep track of twin nodes, constructor will have default value of 1(NOT 0)


public:
	BST() { root = NULL; }; //constructor with inline method def

	~BST() {

		destroyTree(root);

	}; //destructor


	void destroyTree(Node* root) { //use this for destructor!! 

		if (root == NULL) {
			return;
		}
		destroyTree(root->left);
		destroyTree(root->right);
		delete root;

	};

	int getRepeat(Node* root) { //DELETE this I think? can just use root->repeat to get repeat value

		return root->repeat;
	}

	void insert(int data, int& comparison) {//wrapper method for insertNode //ADDED & comparison to determine amntof comparison/operations

		insertItem(root, data, comparison);

	};
	void insertItem(Node*& root, int data, int& comparison) {
		comparison += 1;  //minimum 1 comparison if tree is empty
		if (root == NULL) {

			root = new Node(data);

		}

		if (data < root->value) {//traverse left subtree

			insertItem(root->left, data, comparison);

		}
		else if (data > root->value) { //traverse right subtree
			insertItem(root->right, data, comparison);

		}
		else { //if data == root->value TWIN NODE CASE

			root->repeat += 1; //increment repeat value by 1 
			return;
		}

	};

	void print(ofstream& outputFile) {

		printItem(root);
		printOutPut(root, outputFile);

	}; //wrapper for printing tree


	//prints tree with root to the far left of screen and its children to the right of screen
	void printItem(Node* root, int level = 0) {

		if (root == NULL) {
			return;
		}

		printItem(root->left, level + 1);

		for (int i = 0; i < level; i++) {

			cout << "    ";
		}
		cout << root->value;
		if (root->repeat > 1) {
			cout << '(' << root->repeat << ')' << endl;
		}
		else { cout << endl; }

		printItem(root->right, level + 1);




	}; //prints out tree, have level with default value 0 to help with spacing of tree

	void printOutPut(Node* root, ofstream& outputFile, int level = 0) {

		if (root == NULL) {
			return;
		}
		printOutPut(root->left, outputFile, level + 1);
		for (int i = 0; i < level; i++) {

			outputFile << "    ";
		}
		outputFile << root->value;
		if (root->repeat > 1) {
			outputFile << '(' << root->repeat << ')' << endl;
		}
		else { outputFile << endl; }
		printOutPut(root->right, outputFile, level + 1);

	}

	Node* findMin(Node* root) { //use this method to find left most node, IMPORTANT FOR DELETION METHOD

		while (root->left != NULL) {

			root = root->left;

		}
		return root;
	}

	void deleteItem(int value, int& comparison) {

		deleteNode(root, value, comparison);

	}; //wrapper for deleteNode



	void deleteNode(Node*& root, int data, int& comparison) {

		comparison++; //Even if empty tree, there is still 1 comparison to check empty root (so minimum 1 comparison)
		if (root == NULL) {
			return;
		}
		if (data < root->value) { //if data is less than root, traverse left subtree

			deleteNode(root->left, data, comparison);
		}
		else if (data > root->value) {

			deleteNode(root->right, data, comparison);
		}
		else {

			if (root->repeat > 1) {//if there is a twin, just decrement it 

				root->repeat -= 1; //decrement by 1
				return;
			}
			else if (root->left == NULL) { //0 or 1 child
				Node* temp = root;
				root = root->right;
				delete temp;
			}
			else if (root->right == NULL) {//0 or 1 child

				Node* temp = root;
				root = root->left;
				delete temp;
			}
			else {//find min in right subtree, this is 2 child case

				Node* temp = findMin(root->right);
				root->value = temp->value;
				deleteNode(root->right, temp->value, comparison);
			}
		}



	};  //pass root by refrence in order to delete it properly


	bool search(int value, int& comparison) {//wrapper for SearchItem

		return SearchItem(root, value, comparison);

	}

	bool SearchItem(Node* root, int data, int& comparison) {

		comparison++; //Increment comparison, it will be 1 if its empty tree since there still is a comparison to empty root
		if (root == NULL) { //base (not found)
			return false;
		}
		else if (data < root->value) { //leftsubtree

			SearchItem(root->left, data, comparison);
		}
		else if (data > root->value) {//rightsubtree

			SearchItem(root->right, data, comparison);
		}
		else { //is found!!

			return true;
		}
	};

	int height() { //wrapper method for height

		return getHeight(root);
	}

	int getHeight(Node* root) { //Root is considered 1 

		if (!root) {

			return 0; //if empty tree, return 0 as height
		}

		return max(getHeight(root->left), getHeight(root->right)) + 1;

	}



};

