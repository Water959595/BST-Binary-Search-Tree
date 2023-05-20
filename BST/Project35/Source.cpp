#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//test\test.txt


typedef struct Node //tree node structure
{
	int value;
	Node* left;
	Node* right;
}Node_t;


//func(1) add new key into tree
Node* addNode(Node* newNode, int value, bool* successFlag);  

//func(2) delete key in tree
Node* deleteNode(Node* binTreeNode, int value, bool* successFlag); 
Node* FindRightMin(Node* binTreeNode);	//replace delete key with min key in right subtree 

//func(3) find a key
Node* findNode(Node* binTreeNode, int value);	

//func(4) find a kthSmallest key in tree
int kthSmallest(Node* binTreeNode, int k, int countNum);	
int getSize(Node* binTreeNode);		//get the leftsize of a node

//func(5) show inorder traversal
void inTraversal(Node* binTree);


int main()
{
	FILE* inpF;					//input file 
	char inpFString[50];		//file input - to strore file name (String)
	Node* binTree = nullptr;	//binary shearch tree
	int num;					//file input - the numbers from input file
	int countNum = 0;			//counter for the numbers from input file
	int selecNum;				//input - select function number
	int userInp;				//input - user input number to test function
	bool successFlag;			//Determine the add/delete func successful or not
	int kthSmall;				//output - the kth smallest number


	//request user input the file
	printf("Enter the txt file path >> ");
	fgets(inpFString, 50, stdin);

	inpFString[strlen(inpFString) - 1] = '\0'; //replace '\n' with '\0'

	//check read the file successfully or not
	if ((inpF = fopen(inpFString, "r")) == NULL)
	{
		printf("open file error!!\n");
		system("PAUSE");
		exit(1);
	}

	//scan the data from input file
	//store data into Binary Shearch Tree
	while (!feof(inpF))
	{
		fscanf(inpF, "%d", &num);
		//printf("%d ", num);

		binTree = addNode(binTree, num, &successFlag);
		countNum++;
	}
	fclose(inpF);

	
	//tree traversal
	printf("Inorder traversal: \n");
	inTraversal(binTree);
	printf("\n\n");
	

	while (1)
	{
		successFlag = true;

		do
		{
			printf("-------------------------------------------------------\n");
			printf("Present Inorder Traversal: \n");
			inTraversal(binTree);
			printf("\n\n");

			printf("* Function Table *\n");
			printf("1. Add a new Key value\n");
			printf("2. Delete a Key value\n");
			printf("3. Find a Key value\n");
			printf("4. Find the nth smallest key value\n");
			printf("5. Output sorting results of Key values (from min to max)\n");
			printf("6. end the program\n");

			printf("Select a function you want to test (1~6)>> ");
			scanf("%d", &selecNum);
			printf("\n");
		} while (selecNum < 1 || selecNum > 6);


		//6. end the program
		if (selecNum == 6) { printf("Program end.\n"); break; }
		

		switch (selecNum)
		{
		case 1:
			printf("\n1. Add a new Key value\n");
			printf("Please Add a new Key value >> ");
			scanf("%d", &userInp);

			binTree = addNode(binTree, userInp, &successFlag);
			if (successFlag) { printf("Add node `%d` successfully!\n", userInp);	}
			printf("Inorder traversal: \n");
			inTraversal(binTree);
			printf("\n");
			break;

		case 2:
			printf("\n2. Delete a Key value\n");
			printf("Enter a Key value you want to delete >> ");
			scanf("%d", &userInp);
			binTree = deleteNode(binTree, userInp, &successFlag);

			if (successFlag){ printf("Delete Key `%d` successfully!\n", userInp);}
			printf("Inorder traversal: \n");
			inTraversal(binTree);
			printf("\n");
			break;

		case 3:
			printf("3. Find a Key value\n");
			printf("Enter a Key value you want to find >> ");
			scanf("%d", &userInp);
			findNode(binTree, userInp);
			printf("Inorder traversal: \n");
			inTraversal(binTree);
			break;

		case 4:
			printf("4. Find the nth smallest key value\n");
			printf("Enter the kth smallest Key you want to find >> ");
			scanf("%d", &userInp);
			kthSmall = kthSmallest(binTree, userInp, countNum);

			if (kthSmall == -1)	{ printf("Sorry! `%dth` smallest number is NOT in the tree!\n", userInp); }
			else{ printf("kth smallest: %d, Key: %d\n", userInp, kthSmall);	}
			
			printf("Inorder traversal: \n");
			inTraversal(binTree);
			break;

		case 5:
			printf("5. Output sorting results of Key values (from min to max)\n");
			printf("Results: \n");
			inTraversal(binTree);
			break;

		default:
			break;
		}

		printf("\n\n\n");
	}
	

	printf("\n");
	system("pause");
	return 0;
}


//create new node & return the reference to that node
Node* addNode(Node* newNode, int value, bool* successFlag)
{
	if (!newNode) //doesn't have any node
	{
		//(1) create new node
		newNode = (Node*)malloc(sizeof(Node_t));

		//(2) set the data for that node
		newNode->value = value;

		//(3) Lchild, Rchild initially to null (new node doesn't have L,R child)
		newNode->left = nullptr;
		newNode->right = nullptr;
	}
	else
	{
		if (value == newNode->value)
		{
			*successFlag = false;
			printf("Sorry! The value can Not be same!\n");
		}
		else if (value < newNode->value) //value is smaller >> left
		{
			newNode->left = addNode(newNode->left, value, successFlag);
		}
		else if (value > newNode->value) //value is bigger >> right
		{
			newNode->right = addNode(newNode->right, value, successFlag);
		}
	}

	//return a reference to the node that we add
	return newNode;
}


void inTraversal(Node* binTree)
{
	if (binTree)
	{
		inTraversal(binTree->left);
		printf("%d ", binTree->value);
		inTraversal(binTree->right);
	}
}


Node* deleteNode(Node* binTreeNode, int value, bool* successFlag)
{
	if (binTreeNode == NULL)
	{
		*successFlag = false;
		printf("The tree doesn't NOT exist!\n");
	}
	else if (value < binTreeNode->value) //continue to find >> left
	{
		if (binTreeNode->left == nullptr)
		{
			*successFlag = false;
			printf("Sorry! value: `%d` does NOT in the tree!\n", value);
		}
		else
		{
			//renew the L node, After delete
			binTreeNode->left = deleteNode(binTreeNode->left, value, successFlag);
		}
	}
	else if (value > binTreeNode->value) //continue to find >> right
	{
		if (binTreeNode->right == nullptr)
		{
			*successFlag = false;
			printf("Sorry! value: `%d` does NOT in the tree!\n", value);
		}
		else
		{
			//renew the R node, After delete
			binTreeNode->right = deleteNode(binTreeNode->right, value, successFlag);
		}
	}
	else //found the delete value
	{
		//Case 1: no child
		if ((binTreeNode->left == nullptr) && (binTreeNode->right == nullptr))
		{
			free(binTreeNode);
			return nullptr;
		}
		//Case 2: One child
		else if (binTreeNode->left == nullptr)	//has R child
		{
			Node* temp = binTreeNode;			//store the addr of current node we want to delete
			binTreeNode = binTreeNode->right;	//R child become the root of this subtree
			free(temp);							//delete current node
		}
		else if (binTreeNode->right == nullptr) //has L child
		{
			Node* temp = binTreeNode;
			binTreeNode = binTreeNode->left;	//L child become the root of this subtree
			free(temp);
		}
		//Case 3: 2 children
		else
		{
			Node* succeNode = FindRightMin(binTreeNode->right);
			binTreeNode->value = succeNode->value;

			//Delete the smallest node from the right subtree
			binTreeNode->right = deleteNode(binTreeNode->right, succeNode->value, successFlag);
		}
	}


	return binTreeNode;
}



Node* FindRightMin(Node* binTreeNode)
{
	Node* minNode = binTreeNode;

	while (minNode->left != nullptr)
	{
		minNode = minNode->left;
	}

	return minNode;
}


Node* findNode(Node* binTreeNode, int value)
{
	if (binTreeNode == NULL){ printf("The tree doesn't NOT exist!\n"); }
	else if (value == binTreeNode->value)
	{
		printf("Found! value: `%d` is in the tree!\n", value);
	}
	else if (value < binTreeNode->value) //continue to find >> left
	{
		if (binTreeNode->left == nullptr)
		{
			printf("Sorry! value: `%d` does NOT in the tree!\n", value);
		}
		else
		{
			//renew the L node, After delete
			binTreeNode->left = findNode(binTreeNode->left, value);
		}
	}
	else if (value > binTreeNode->value) //continue to find >> right
	{
		if (binTreeNode->right == nullptr)
		{
			printf("Sorry! value: `%d` does NOT in the tree!\n", value);
		}
		else
		{
			//renew the R node, After delete
			binTreeNode->right = findNode(binTreeNode->right, value);
		}
	}

	return binTreeNode;
}


int getSize(Node* binTreeNode) //how many numbers in the tree
{
	if (binTreeNode == NULL){ return 0;	}
	else
	{
		//Left + root + Right
		return getSize(binTreeNode->left) + 1 + getSize(binTreeNode->right);
	}
}


int kthSmallest(Node* binTreeNode, int k, int countNum)
{
	int leftSize;


	if (binTreeNode == nullptr) { return NULL; }
	if (k < 1 || k > countNum){ return -1; }

	leftSize = getSize(binTreeNode->left);


	if (k <= leftSize) // kth smallest is in L
	{
		return kthSmallest(binTreeNode->left, k, countNum);
	}
	else if (k == leftSize + 1)  // kth smallest is root
	{
		return binTreeNode->value;
	}
	else if(k > leftSize + 1) // kth smallest is in R
	{
		// kth smallest in tree = k-(leftSize+1)th smallest is in R
		return kthSmallest(binTreeNode->right, k-(leftSize+1), countNum);
	}
}