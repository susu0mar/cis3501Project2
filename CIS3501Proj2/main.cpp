#include <iostream>
#include "BST.h"
#include "AVL.h"
#include<string>
#include<fstream>

using namespace std;

int main() {
	
	//ignore BST.cpp and AVL.cpp (all methods defined in BST.h)

	BST tree;

	AVL tree2;

	string tstCase;

	string firstInputFile; //use this name in ifstream

	string secondActionFile; //use this name in 2nd ifstream

	string outFileName; //use this name in output file ofstream (BST)

	string outFileName2; //use this name in output file ofstream for AVL

	ifstream initialFile; //name comes from firstInputFile string

	ifstream operationFile; //name comes from secondActionFile string

	ofstream outputFileBST; //Output file

	ofstream outputFileAVL; //output file

	int number;

	//2-Dimensional Array! 
	int operAmnt[2][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };//at index(column) 0 = total Creation, at index 1= total insert, at index 2= total search, at index 3= total delete
															//at index(row) 0 = BST, at index 1 = AVL
	int comparisons; //store amount of comparisons/operations for each action

	int comparisonsAVL; //store amount of comparisons/operations for each action for AVL

	int rotations = 0; //store amount of rotations done for inserts or deletes!

	
	
	cout << "Hello! Please Enter test case name:" << endl;

	getline(cin, tstCase);

	cout << "Enter 1st input file name" << endl;

	cin >> firstInputFile;

	firstInputFile = firstInputFile + ".txt";

	cout << "Enter 2nd input (Action) file name" << endl;

	cin >> secondActionFile;

	secondActionFile = secondActionFile + ".txt";

	cout << "Enter output file name for BST" << endl;

	cin >> outFileName;

	outFileName = outFileName + ".txt";

	cout << "Enter output file name for AVL" << endl;

	cin >> outFileName2;

	outFileName2 = outFileName2 + ".txt";


	initialFile.open(firstInputFile); //open input file //IT WORKS FINALLY
	outputFileBST.open(outFileName); //open output file
	outputFileAVL.open(outFileName2); //open output file AVL

	if (!initialFile.is_open()) {

		//terminate program if file fails to open

		cout << "Unable to open File" << endl;

		return 1;
	}

	if (!outputFileBST.is_open() || !outputFileAVL.is_open()) { //Open check works!

		//terminate program if file fails to open

		cout << "Unable to open output File" << endl;

		return 1;

	}
	
	
	//check if file is empty
	if (initialFile.peek() == EOF) { // IT WORKS :) 

		cout << "Empty File. Tree is empty" << endl;
		outputFileBST << "Empty File. Tree is empty" << endl;
		outputFileAVL << "Empty File. Tree is empty" << endl;

	}
	else { //iterate each number in the initial file into the tree

		while (initialFile >> number) { 
			//reset values
			comparisons = 0;
			comparisonsAVL = 0;
			rotations = 0;

			cout << "Insert into BST and AVL " << number << endl << endl;
			outputFileBST << "Insert into BST " << number << endl << endl;
			outputFileAVL << "Insert into AVL " << number << endl << endl;

			tree.insert(number, comparisons);
			//tree2.insert(number, comparisonsAVL, rotations);
			comparisons += 1; //ADD 1 TO COMPARISON TO ACCOUNT FOR INSERT ACTION (NOT JUST COMPARISON)
			//comparisonsAVL += 1;

			cout << "BST" << endl << endl << endl;
			tree.print(outputFileBST);
			cout << endl;
			cout << "Tree Height: " << tree.height() << endl;
			cout << "Comparisons/operations to insert " << number << ": " << comparisons;
			cout << endl << endl;

			//print to outputfile
			outputFileBST << endl;
			outputFileBST << "Tree Height: " << tree.height() << endl;
			outputFileBST << "Comparisons/operations to insert " << number << ": " << comparisons;
			outputFileBST << endl << endl;
			operAmnt[0][0] += comparisons;    //+= to calculate total comparisons for Tree Creation

			//FOR AVL
			cout << "AVL" << endl;
			tree2.insert(number, comparisonsAVL, rotations, outputFileAVL);
			comparisonsAVL += 1;
			cout <<endl<<endl<<endl;
			tree2.print(outputFileAVL);
			cout << endl;
			cout << "Tree Height: " << tree2.height() << endl;
			cout << "Comparisons/operations to insert " << number << ": " << comparisonsAVL<<endl;
			cout << "Total rotations done: " << rotations;
			cout << endl << endl;
			//print to outputfile AVL
			outputFileAVL << endl;
			outputFileAVL << "Tree Height: " << tree2.height() << endl;
			outputFileAVL << "Comparisons/operations to insert " << number << ": " << comparisonsAVL<<endl;
			outputFileAVL << "Total rotations done: " << rotations;
			outputFileAVL << endl << endl;
			operAmnt[1][0] += comparisonsAVL;   //+= to calculate total comparisons for Tree Creation (ROTAIONS NOT INCLUDED IN COMPARISON/OPERATION COUNT)

		}

	}
	//Done with first input file now close it
	initialFile.close();

	cout << endl << "NOW ONTO THE OPERATION FILE :)" << endl << endl;
	outputFileBST << endl << "NOW ONTO THE OPERATION FILE :)" << endl << endl; //to outputfile
	outputFileAVL << endl << "NOW ONTO THE OPERATION FILE :)" << endl << endl; //to outputfile
	//Now Open 2nd input(action) file 

	operationFile.open(secondActionFile);

	if (!operationFile.is_open()) {

		//terminate program if file fails to open

		cout << "Unable to open File" << endl;

		return 1;
	}

	//Declare char variable that will hold actions and int that will hold numbers in operation file
	char Action;
	int ActionNum;

	//Check if operation(action) File is empty
	if (operationFile.peek() == EOF) {

		cout << "Empty Action File. No actions will be performed" << endl;
		outputFileBST << "Empty Action File. No actions will be performed" << endl;
		outputFileAVL << "Empty Action File. No actions will be performed" << endl;
	}
	else {
		while (operationFile >> Action >> ActionNum) { //CONTINUE HEREEEEEEEEE!!!!!!!

			switch (Action) {

			case 'S':
				//reset comparisons integers
				comparisons = 0;
				comparisonsAVL = 0;
				cout << "Searching for " << ActionNum << endl << endl;
				outputFileBST << "Searching for " << ActionNum << endl << endl;
				outputFileAVL << "Searching for " << ActionNum << endl << endl;

				cout << "BST" << endl << endl << endl;
				tree.print(outputFileBST);
				cout << endl << endl << endl;
				

				if (tree.search(ActionNum, comparisons)) {

					cout << ActionNum << " Found!" << endl;
					outputFileBST << ActionNum << " Found!" << endl;
					//outputFileAVL << ActionNum << " Found" << endl;
				}
				else {

					cout << ActionNum << " Not Found!" << endl;
					outputFileBST << ActionNum << " Not Found!" << endl;
					//outputFileAVL << ActionNum << " Not Found!" << endl;
				}

				cout << "Tree Height: " << tree.height() << endl;
				cout << "Comparisons/operations to search " << ActionNum << ": " << comparisons << endl << endl;
				//output
				outputFileBST << "Tree Height: " << tree.height() << endl;
				outputFileBST << "Comparisons/operations to search " << ActionNum << ": " << comparisons << endl << endl;
				operAmnt[0][2] += comparisons; //index 2 = search


				//AVL search!
				cout << "AVL" << endl << endl << endl;
				tree2.print(outputFileAVL);
				cout << endl << endl << endl;


				if (tree2.search(ActionNum, comparisonsAVL)) {

					cout << ActionNum << " Found!" << endl;
					outputFileAVL << ActionNum << " Found!" << endl;
					
				}
				else {

					cout << ActionNum << " Not Found!" << endl;
					outputFileAVL << ActionNum << " Not Found!" << endl;
					
				}

				cout << "Tree Height: " << tree2.height() << endl;
				cout << "Comparisons/operations to search " << ActionNum << ": " << comparisonsAVL << endl << endl;
				//output
				outputFileAVL << "Tree Height: " << tree2.height() << endl;
				outputFileAVL << "Comparisons/operations to search " << ActionNum << ": " << comparisonsAVL << endl << endl;
				operAmnt[1][2] += comparisonsAVL; //index 2 = search


				break;

			case 'I':
				//reset comparisons & rotation integers
				comparisons = 0;
				comparisonsAVL = 0;
				rotations = 0;

				cout << "Inserting into BST and AVL " << ActionNum << endl << endl;
				outputFileBST << "Insert into BST " << ActionNum << endl << endl;
				outputFileAVL << "Inserting into AVL " << ActionNum << endl << endl;

				cout << "BST" << endl<<endl<<endl;
				tree.insert(ActionNum, comparisons);
				comparisons += 1; //ADD 1 TO COMPARISON TO ACCOUNT FOR INSERT ACTION (NOT JUST THE COMPARISONS DONE)

				tree.print(outputFileBST);
				cout << "Tree Height: " << tree.height() << endl;
				cout << "Comparisons/operations to insert " << ActionNum << ": " << comparisons << endl << endl;
				//output
				outputFileBST << "Tree Height: " << tree.height() << endl;
				outputFileBST << "Comparisons/operations to insert " << ActionNum << ": " << comparisons << endl << endl;

				operAmnt[0][1] += comparisons; //index 1 = insert


				//AVL
				cout << "AVL" << endl << endl << endl;
				tree2.insert(ActionNum, comparisonsAVL, rotations, outputFileAVL);
				comparisonsAVL += 1;//ADD 1 TO COMPARISON TO ACCOUNT FOR INSERT ACTION (NOT JUST THE COMPARISONS DONE)
				
				tree2.print(outputFileAVL);
				cout << "Tree Height: " << tree2.height() << endl;
				cout << "Comparisons/operations to insert " << ActionNum << ": " << comparisonsAVL << endl;
				cout << "Total rotations done: " << rotations<<endl<<endl;

				operAmnt[1][1] += comparisonsAVL;//index 1 = insert
				break;

			case 'D': //TODO!!
				//reset comparison & rotation integers
				comparisons = 0;
				comparisonsAVL = 0;
				rotations = 0;

				int searchcheck; //to use in search, NOT IMPORTANT, JUST MADE IT SO I CAN CALL SEARCH

				cout << "Deleting " << ActionNum <<" from BST and AVL"<< endl << endl;
				outputFileBST << "Deleting " << ActionNum <<" from BST"<< endl << endl;
				outputFileAVL << "Deleting " << ActionNum << " from AVL" << endl << endl;

				//check if number is in tree (to account for actual delete action since my method doesnt increment if something is deleted, it just counts comparisons)
				if (tree.search(ActionNum, searchcheck)) {
					comparisons += 1; //SEARCH FOR THE NUMBER, IF ITS IN TREE, ADD 1 TO DELETE COMPARISON COUNT TO ACCOUNT FOR THE ACTUAL DELETE ACTION
				}

				if (tree2.search(ActionNum, searchcheck)) { //same thing but for avl
					comparisonsAVL += 1;
				}

				cout << "BST" << endl << endl<<endl;
				tree.deleteItem(ActionNum, comparisons);

				tree.print(outputFileBST);
				cout << "Tree Height: " << tree.height() << endl;
				cout << "Comparisons/operations to delete " << ActionNum << ": " << comparisons << endl << endl;
				//output
				outputFileBST << "Tree Height: " << tree.height() << endl;
				outputFileBST << "Comparisons/operations to delete " << ActionNum << ": " << comparisons << endl << endl;

				operAmnt[0][3] += comparisons; //index 3 = delete


				cout << "AVL" << endl << endl << endl;
				tree2.deleteItem(ActionNum, comparisonsAVL, rotations, outputFileAVL);

				tree2.print(outputFileAVL);
				cout << "Tree Height: " << tree2.height()<<endl;
				cout << "Comparisons/operations to delete " << ActionNum << ": " << comparisonsAVL << endl;
				cout << "Total rotations done: " << rotations<<endl<<endl;

				//output file
				outputFileAVL << "Tree Height: " << tree2.height() << endl;
				outputFileAVL << "Comparisons/operations to delete " << ActionNum << ": " << comparisonsAVL << endl;
				outputFileAVL << "Total rotations done: " << rotations << endl << endl;

				operAmnt[1][3] += comparisonsAVL;  //index 3 = delete

				break;

			default:

				cout << "Invalid Action Code" << endl << endl;
				outputFileBST << "Invalid Action Code" << endl << endl;
				outputFileAVL<< "Invalid Action Code" << endl << endl;


			}



		}



	}

	//then close the operationFile
	operationFile.close();

	//PRINT OUT RESULTS IN A SMALL TABLE

	cout << tstCase << endl;
	cout << "Operation/Comparison Count!" << endl << endl;
	cout << "\t\t" << "BST\t" << "AVL" << endl;
	cout << "Creation\t" << operAmnt[0][0]<<"\t" << operAmnt[1][0] << endl;
	cout << "Search\t\t" << operAmnt[0][2]<<"\t"<<operAmnt[1][2] << endl;
	cout << "Insert\t\t" << operAmnt[0][1]<<"\t"<<operAmnt[1][1] << endl;
	cout << "Delete\t\t" << operAmnt[0][3] << "\t"<<operAmnt[1][3]<< endl << endl;
	cout << "Total\t\t" << operAmnt[0][0] + operAmnt[0][1] + operAmnt[0][2] + operAmnt[0][3] <<"\t"
		<< operAmnt[1][0] + operAmnt[1][1] + operAmnt[1][2] + operAmnt[1][3]<< endl;


	//PRINT AGAIN TO BST OUTPUT FILE!!!!
	outputFileBST << tstCase << endl;
	outputFileBST << "Operation/Comparison Count!" << endl << endl;
	outputFileBST << "\t\t" << "BST\t" << "AVL" << endl;
	outputFileBST << "Creation\t" << operAmnt[0][0] << "\t" << operAmnt[1][0] << endl;
	outputFileBST << "Search\t\t" << operAmnt[0][2] << "\t" << operAmnt[1][2] << endl;
	outputFileBST << "Insert\t\t" << operAmnt[0][1] << "\t" << operAmnt[1][1] << endl;
	outputFileBST << "Delete\t\t" << operAmnt[0][3] << "\t" << operAmnt[1][3] << endl << endl;
	outputFileBST << "Total\t\t" << operAmnt[0][0] + operAmnt[0][1] + operAmnt[0][2] + operAmnt[0][3] << "\t"
		<< operAmnt[1][0] + operAmnt[1][1] + operAmnt[1][2] + operAmnt[1][3] << endl;



	//PRINT AGAIN TO AVL OUTPUT FILE!!!!
	outputFileAVL << tstCase << endl;
	outputFileAVL << "Operation/Comparison Count!" << endl << endl;
	outputFileAVL << "\t\t" << "BST\t" << "AVL" << endl;
	outputFileAVL << "Creation\t" << operAmnt[0][0] << "\t" << operAmnt[1][0] << endl;
	outputFileAVL << "Search\t\t" << operAmnt[0][2] << "\t" << operAmnt[1][2] << endl;
	outputFileAVL << "Insert\t\t" << operAmnt[0][1] << "\t" << operAmnt[1][1] << endl;
	outputFileAVL << "Delete\t\t" << operAmnt[0][3] << "\t" << operAmnt[1][3] << endl << endl;
	outputFileAVL << "Total\t\t" << operAmnt[0][0] + operAmnt[0][1] + operAmnt[0][2] + operAmnt[0][3] << "\t"
		<< operAmnt[1][0] + operAmnt[1][1] + operAmnt[1][2] + operAmnt[1][3] << endl;

	
	
	return 0;
}