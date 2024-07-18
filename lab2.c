// DO NOT REMOVE THIS COMMENT!! CSE 3430 lab2.c SP 24 CODE 082108

// STUDENT NAME: Jonathan Rhymond

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	struct Data {
		char title[60];
		char author[60];
		int stockNumber;
		float wholesalePrice;
		float retailPrice;
		int wholesaleQuantity;
		int retailQuantity;
	};

	typedef struct Node {
		struct Data book;
		struct Node *next;
	} Node;

void getDataAndBuildList(Node **listHeadPtr);
Node *createNodeAndGetData(void);
void insertNode(Node **listHeadPtr, Node *newNodePtr);
void deleteNode(Node **listHeadPtr, int stockNumToDelete);
void getUserOption(Node **listHead);
double calculateTotalRevenue(const Node *listHead);
double calculateInvestmentInInventory(const Node *listHead);
double calculateTotalWholesaleCost(const Node *listHead);
double calculateTotalProfit(const Node *listHead);
int calculateTotalBooksSold(const Node *listHead);
double calculateAverageProfit(const Node *listHead);
void printList(const Node *listHead);
void freeAllNodes(Node **listHeadPtr);

int main() {
	Node *listHead = NULL;
	getDataAndBuildList(&listHead);
	getUserOption(&listHead);
	return 0;
}

void getDataAndBuildList(Node **listHeadPtr) {
	Node *newNodePtr;
	printf("Please enter data about the books.\n\n");
	while (newNodePtr = createNodeAndGetData()) {
		insertNode(listHeadPtr, newNodePtr);
	}
}

Node *createNodeAndGetData(void) {
	Node *newNodePtr;
	newNodePtr = malloc (sizeof(Node));
	if (newNodePtr == NULL) {
		printf("Error: memory could not be allocated for enough nodes. ");
		printf("Terminating program!\n");
		exit (0);
	}
	else {
		scanf("%[^\n]", newNodePtr->book.title);
		if (strcmp(newNodePtr->book.title, "END_DATA") == 0) {
			/* free Node if end of book data detected */
			free(newNodePtr);			
			return NULL;
		}
		else {
			/* consume newline before author string */
			getchar();				
			scanf("%[^\n]s", newNodePtr->book.author);
			scanf("%i", &newNodePtr->book.stockNumber);
			scanf("%f", &newNodePtr->book.wholesalePrice);
			scanf("%f", &newNodePtr->book.retailPrice);
			scanf("%i", &newNodePtr->book.wholesaleQuantity);
			scanf("%i", &newNodePtr->book.retailQuantity);
			/* consume newline before next title string */
			getchar();				
		}
		return newNodePtr;
	}
}


void insertNode(Node **listHeadPtr, Node *newNodePtr) {
	Node *traversePtr = *listHeadPtr;
	//first case: empty list, insert first node
	if (traversePtr == NULL) {
		*listHeadPtr = newNodePtr;
		newNodePtr->next = NULL;
	}
	//second case: non-empty list, insert new before current first node
	else if (newNodePtr->book.stockNumber < traversePtr->book.stockNumber){
		*listHeadPtr = newNodePtr;
		newNodePtr->next=traversePtr;
	}
	//third case: non-empty list, insert new after current first node
	else {
		Node *priorNodePtr = traversePtr;
		traversePtr = traversePtr->next;
		while(traversePtr != NULL && traversePtr->book.stockNumber < newNodePtr->book.stockNumber) {
			priorNodePtr = traversePtr;
			traversePtr = traversePtr->next;
		}
		priorNodePtr->next = newNodePtr;
		newNodePtr->next = traversePtr;
	}
}

void getUserOption(Node **listHeadPtr) {
	int option;
	Node *newNodePtr;
	int stockNumToDelete;
	do {
		printf("\nPlease enter an integer between 1 and 10 to select an operation on the data:\n");
		scanf("%i", &option);
		getchar();
		switch (option){
			case 1:
				printList (*listHeadPtr);
				break;
			case 2:
				printf("\nTotal revenue: %.2f\n", calculateTotalRevenue(*listHeadPtr));
				break;
			case 3:
				printf("\nTotal wholesale cost: %.2f\n", calculateTotalWholesaleCost(*listHeadPtr));
				break;
			case 4:
				printf("\nTotal investment in inventory: %.2f\n", calculateInvestmentInInventory(*listHeadPtr));
				break;
			case 5:
				printf("\nTotal profit: %.2f\n", calculateTotalProfit(*listHeadPtr)); 
				break;
			case 6:
				printf("\nTotal number of books sold = %i\n", calculateTotalBooksSold(*listHeadPtr));
				break;
			case 7:
				printf("\nAverage profit: %.2f\n", calculateAverageProfit(*listHeadPtr));
				break;
			case 8:		
				printf("\nPlease enter the data for the book you wish to add:\n\n");
				newNodePtr = createNodeAndGetData();
				insertNode(listHeadPtr, newNodePtr);			
				break;
			case 9:
				printf("\nEnter the stock number of the book you wish to delete: ");
				scanf("%i", &stockNumToDelete);
				deleteNode(listHeadPtr, stockNumToDelete);
				break;
			case 10:
				freeAllNodes(listHeadPtr);
				break;
			default:
				printf("Valid option choices are 1 to 10. Please choose again!\n");
				break;
		} 
	} while (option != 10);
}

double calculateTotalRevenue(const Node *listHead) { 
	const Node *traversePtr = listHead;
	double totalRevenue = 0.0;
	while (traversePtr != NULL) {
		totalRevenue += traversePtr->book.retailPrice*traversePtr->book.retailQuantity;
		traversePtr = traversePtr->next;
	}
	return totalRevenue;
}

double calculateInvestmentInInventory(const Node *listHead) { 
	const Node *traversePtr = listHead;
	double totalInvestment = 0.0;
	while (traversePtr != NULL) {
		totalInvestment += (traversePtr->book.wholesaleQuantity - traversePtr->book.retailQuantity)*traversePtr->book.wholesalePrice;
		traversePtr = traversePtr->next;
	}
	return totalInvestment;
}

double calculateTotalWholesaleCost(const Node *listHead) { 
	const Node *traversePtr = listHead;
	double totalWholesaleCost = 0.0;
	while (traversePtr != NULL) {
		totalWholesaleCost += traversePtr->book.wholesalePrice*traversePtr->book.wholesaleQuantity;
		traversePtr = traversePtr->next;
	}
	return totalWholesaleCost;
}

double calculateTotalProfit(const Node *listHead) { 
	double totalRevenue = calculateTotalRevenue(listHead);
	double totalWholesaleCost = calculateTotalWholesaleCost(listHead);
	double totalInvestment = calculateInvestmentInInventory(listHead);
	double profit = totalRevenue - totalWholesaleCost + totalInvestment;
	return profit;
}

int calculateTotalBooksSold(const Node *listHead) { 
	const Node *traversePtr = listHead;
	int totalBooksSold = 0;
	while (traversePtr != NULL) {
		totalBooksSold += traversePtr->book.retailQuantity;
		traversePtr = traversePtr->next;
	}
	return totalBooksSold;
}

double calculateAverageProfit(const Node *listHead) {
	double totalProfit = calculateTotalProfit(listHead);
	int totalBooksSold = calculateTotalBooksSold(listHead);
	double averageProfit = 0.0;
	if (totalBooksSold != 0) { //use if to avoid divide by 0
		averageProfit = totalProfit/totalBooksSold;
	}
	return averageProfit;
}

void deleteNode(Node **listHeadPtr, int stockNumToDelete) {
	Node *traversePtr = *listHeadPtr;
	//first case: empty list, ERROR
	if (traversePtr == NULL) {
		printf("ERROR: Empty List, cannot delete\n");
	}
	//second case: non-empty list, delete first node
	else if (traversePtr->book.stockNumber == stockNumToDelete) {
		*listHeadPtr = traversePtr->next;
		free(traversePtr);
		printf("Book stock number %i deleted\n", stockNumToDelete);
	}
	//third case: non-empty list, delete node after first node
	else {
		Node *priorNodePtr = traversePtr;
		traversePtr = traversePtr->next;
		while(traversePtr != NULL && traversePtr->book.stockNumber < stockNumToDelete) {
			priorNodePtr = traversePtr;
			traversePtr = traversePtr->next;
		}
		if (traversePtr == NULL || traversePtr-> book.stockNumber != stockNumToDelete) {
			printf("ERROR: Book stock number %i deleted\n", stockNumToDelete);
		} else {
			priorNodePtr->next = traversePtr->next;
			free(traversePtr);
			printf("Book stock number %i deleted\n", stockNumToDelete);
		}
	}
}

void printList(const Node *listHead) {
	const Node *traversePtr = listHead;
	printf("\nBook list:\n");
	while (traversePtr != NULL) {		/* determine not at end of list */
		printf("%s\n", traversePtr->book.title); 
		traversePtr = traversePtr->next;
	}
	printf("\n");
}

void freeAllNodes(Node **listHeadPtr) {
	Node *traversePtr = *listHeadPtr;
	Node *restOfListPtr = *listHeadPtr;    
	while (restOfListPtr != NULL) {         /* determine list is not empty */
		restOfListPtr = restOfListPtr->next;
		free(traversePtr);
		traversePtr = restOfListPtr;
	}
	*listHeadPtr = NULL; /* set listHeadPtr back to NULL after space freed */
}

