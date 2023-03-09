#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"
using namespace std;

class AVL
{

private:
	Node* root; //root of tree

public:

	AVL() { root = NULL; } //default constructor sets root to null

	~AVL() { destroyTree(root); }//destructor for AVL class, calls same destroy tree method from BST

	void destroyTree(Node* root) { //use this for destructor!! (copied from BST)

		if (root == NULL) {
			return;
		}
		destroyTree(root->left);
		destroyTree(root->right);
		delete root;

	};

	void insert(int data, int& comparison, int& rotation, ofstream& outputFile) { //wrapper method for insertNode, comparison to count amount of comparisons done, rotation to count amount of rotations done
	
		insertItem(root, data, comparison, rotation, outputFile);
	
	}

	//TODO:might have cout for each balance part to ouput to user which rotations are being done!!! (AND ADD OUTPUT FILE TOO)
	void insertItem(Node*& root, int data, int& comparison, int& rotation, ofstream& outputFile) { //first part of insert the same from BST, just added balancing feature
		comparison += 1;  //minimum 1 comparison if tree is empty
		if (root == NULL) {

			root = new Node(data);

		}

		if (data < root->value) {//traverse left subtree

			insertItem(root->left, data, comparison, rotation, outputFile);

		}
		else if (data > root->value) { //traverse right subtree
			insertItem(root->right, data, comparison, rotation, outputFile);

		}
		else { //if data == root->value TWIN NODE CASE

			root->repeat += 1; //increment repeat value by 1 
			return;
		}


		root->height = getHeight(root); //update height of the node using getHeight method

		int balance = balanceFactor(root); //local variable balance to hold balance factor


		//NOW CHECK BALANCE FACTOR AND ROTATE APPROPRIATELY

		if (balance > 1 && data < root->left->value) { //Left Left case, rotate right once
			cout << "Rotate Right" << endl;

			//output File :)
			outputFile << "Rotate Right" << endl;

			root = rotateRight(root);
			rotation += 1; //increment rotation count by 1
		}

		if (balance > 1 && data > root->left->value) {//Left right case, rotate left then right
			cout << "Rotate Left" << endl;
			cout << "Rotate Right" << endl;

			//output File :)
			outputFile << "Rotate Left" << endl;
			outputFile << "Rotate Right" << endl;

			root->left = rotateLeft(root->left);
			root = rotateRight(root);
			rotation += 2; //increment rotation count by 2 
		}

		if (balance < -1 && data > root->right->value) {//Right right case, rotate left once
			cout << "Rotate Left" << endl;

			//output File :)
			outputFile << "Rotate Left" << endl;

			root = rotateLeft(root);
			rotation += 1; //increment rotation count by 1
		}

		if (balance < -1 && data < root->right->value) {//Right left case, rotate right then left
			cout << "Rotate Right" << endl;
			cout << "Rotate Left" << endl;

			//output File :)
			outputFile << "Rotate Right" << endl;
			outputFile << "Rotate Left" << endl;

			root->right = rotateRight(root->right);
			root = rotateLeft(root);
			rotation += 2; //increment rotation count by 2
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

	//BALANCE FACTOR METHOD!!! 
	int balanceFactor(Node* root) {
	
		if (root == NULL) { //if leaf balance is 0, if empty balance is 0

			return 0;

		}
		else {
		
			return getHeight(root->left) - getHeight(root->right); // greater than 0 means left tree is larger, if less than 0 right tree is larger, if 0 then equal!
		
		}

	}


	

	Node* rotateRight(Node* root) {
		//rotate the node once to right
		Node* newroot = root->left;
		root->left = newroot->right;
		newroot->right = root;

		//update the height for the previous root and the newroot
		root->height = getHeight(root);
		newroot->height = getHeight(newroot);

		return newroot;
	
	}

	Node* rotateLeft(Node* root) {
		//rotate the node once to the left
		Node* newroot = root->right;
		root->right = newroot->left;
		newroot->left = root;

		//update the height for the previous root and the newroot
		root->height = getHeight(root);
		newroot->height = getHeight(newroot);

		return newroot;
	
	
	}

	//PRINT TREE!
	
	//MIGHT CHANGE THE PRINT METHOD A BIT!
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



	Node* findMin(Node* root) { //use this method to find left most node, IMPORTANT FOR DELETION METHOD (reuse from bst class)

		while (root->left != NULL) {

			root = root->left;

		}
		return root;
	}

	//Delete Node Method! (modified from BST)

	void deleteItem(int value, int& comparison, int& rotation, ofstream& outputFile) {

		deleteNode(root, value, comparison, rotation, outputFile);

	}; //wrapper for deleteNode



	void deleteNode(Node*& root, int data, int& comparison, int& rotation, ofstream& outputFile) {

		comparison++; //Even if empty tree, there is still 1 comparison to check empty root (so minimum 1 comparison)
		if (root == NULL) {
			return;
		}
		if (data < root->value) { //if data is less than root, traverse left subtree

			deleteNode(root->left, data, comparison, rotation, outputFile);
		}
		else if (data > root->value) {

			deleteNode(root->right, data, comparison, rotation, outputFile);
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
				deleteNode(root->right, temp->value, comparison, rotation, outputFile);
			}
		}

		//access violation I think i need to check if root is null before continuing
		if (root == NULL) {
			return;
		}

		root->height = getHeight(root); //update height of the node using getHeight method

		int balance = balanceFactor(root); //local variable balance to hold balance factor

		//NOW CHECK BALANCE FACTOR AND ROTATE APPROPRIATELY
		
		//TODO: test that it balances correctly for delete
		if (balance > 1 && balanceFactor(root->left) >= 0) { //Left left case
			
			cout << "Rotate right" << endl;

			//output file :)
			outputFile << "Rotate right" << endl;

			root = rotateRight(root);
			rotation += 1; //increment rotation count by 1
		}
		if (balance > 1 && balanceFactor(root->left) < 0) {//Left Right case
			
			cout << "Rotate Left" << endl;
			cout << "Rotate Right" << endl;

			//output File :)
			outputFile << "Rotate Left" << endl;
			outputFile << "Rotate Right" << endl;

			root->left = rotateLeft(root->left);
			root = rotateRight(root);
			rotation += 2; //increment rotation count by 2
		}
		if (balance < -1 && balanceFactor(root->right) <= 0) {//Right right case
			
			cout << "Rotate Left" << endl;

			//output File :)
			outputFile << "Rotate Left" << endl;

			root = rotateLeft(root);
			rotation += 1; //increment rotation count by 1
		}
		if (balance < -1 && balanceFactor(root->right) > 0) {//Right left case

			cout << "Rotate Right" << endl;
			cout << "Rotate Left" << endl;

			//output File :)
			outputFile << "Rotate Right" << endl;
			outputFile << "Rotate Left" << endl;

			root->right = rotateRight(root->right);
			root = rotateLeft(root);
			rotation += 2; //increment rotation count by 2
		}

	};  //pass root by refrence in order to delete it properly


	//SEARCH METHOD! (REUSED FROM BST)
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





};

