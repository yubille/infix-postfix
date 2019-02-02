/*
* Laboratory 01 (CMSC 28)
* Conversion from infix to postfix expression
* Pair: MALABANAN, Kaila Jeanne and ALFECHE, Jubille Tricia F.
*/

#include <stdio.h>
#include <stdlib.h>

struct node {
	char data;
	struct node *nextPtr;
};
typedef struct node Node;
typedef Node *NodePtr;

//function prototypes
void enqueue(NodePtr *, NodePtr *, char);
int push(NodePtr *, char);
void pop(NodePtr *);
void print(NodePtr);

int main() {
	//declaration of variables
	NodePtr stackStartPtr = NULL; //first in list in stack
	NodePtr queueStartPtr = NULL; //first in list in queue
	NodePtr queueCurrentPtr = NULL; //last in list in queue
	
	char exp[20] = {'\0'}; //expression array
	int i = 0; //loop counter
	int stack; //takes on a return value for determining precedence
	
	//introduction
	printf("Welcome. You are now using infix-postfix converter.\nSimply input your expression.\n\n");
	
	//take in expression
	printf("Infix: \t ");
	scanf("%s", &exp);
	
	//loop to go over each character
	while(exp[i] != '\0'){
		stack = 0;
		//checks whether the character is a number
		if(exp[i] >= '0' && exp[i] <= '9' && i % 2 == 0){
			enqueue(&queueStartPtr, &queueCurrentPtr, exp[i]);
		} else if((exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') && i % 2 == 1){ //check whether it's an operation
			stack = push(&stackStartPtr, exp[i]); //stores and returns value for operation precedence
			//current operation has lower/same precedence than previous
			if(stack == 1){ 
				enqueue(&queueStartPtr, &queueCurrentPtr, stackStartPtr->data); //transfer character from stack to queue
				pop(&stackStartPtr); //delete character from stack
				i--; //go back one place value (since current operation is not added nor deleted)
			}
		} else { //for errors in input
			if((exp[i] >= '0' && exp[i] <= '9') || (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')){
				if(i % 2 == 0){
					printf("\nError in place %d. Two operations are written consecutively.", i);
				} else if(i % 2 == 1){
					printf("\nError in place %d. Two digits are written consecutively.", i);
				}
			} else {
				printf("\nError in place %d. Invalid character is inputted.", i);	
			}
			printf("\nTerminating program.");
			return 0; //immediately ends program
		}
		i++; //increment to move on to the next character
	}//end of loop, all characters have been checked
	//for operations that still remain in stack
	while(stackStartPtr != NULL){ //loop runs until stack is empty
		enqueue(&queueStartPtr, &queueCurrentPtr, stackStartPtr->data); //transfer character from stack to queue
		pop(&stackStartPtr); //delete character from stack
	} //stack is now empty
	
	printf("Postfix: ");
	print(queueStartPtr); //prints all characters in queue
	
	printf("\n\nConversion successful. Thank you for using the program.\nBy: Malabanan and Alfeche of BSCS-1");
	
	return 0;
}

//Usual algorithm for queue --> FIFO (First in, first out)
void enqueue(NodePtr *startPtr, NodePtr *currentPtr, char character) {
	NodePtr newPtr;
	newPtr = (Node *) malloc(sizeof(Node));
	
	newPtr->data = character;
	newPtr->nextPtr = NULL;
	
	if(newPtr == NULL) //no memory available
		printf("%c not inserted. No memory available.", newPtr->data);

	if(*startPtr == NULL){
		*startPtr = newPtr;
	} else {
		(*currentPtr)->nextPtr = newPtr;
	}
	*currentPtr = newPtr;
}

//Usual algorithm for stack, FILO (First in, last out)
int push(NodePtr *startPtr, char character) {
	NodePtr newPtr;
	newPtr = (Node *) malloc(sizeof(Node));
	
	newPtr->data = character;
	newPtr->nextPtr = *startPtr;
	
	if(newPtr == NULL) //no memory available
		printf("%c not inserted. No memory available.", newPtr->data);
	
	//conditions to determine precedence
	if(*startPtr != NULL){
		switch(newPtr->data){
			case'+': case'-': //if new operation has less/same precedence than the first operation in the stack list (+ or -)
				if(((*startPtr)->data == '*' || (*startPtr)->data == '/') || ((*startPtr)->data == '+' || (*startPtr)->data == '-')){
					return 1; //sets condition in main function
				}
			case '*': case '/': //if new operation has same precedence than the first operation in the stack list (* or /)
				if((*startPtr)->data == '*' || (*startPtr)->data == '/'){
					return 1; //sets condition in main function
				}
			default:
				break;
		}
	}
	*startPtr = newPtr;
}

//deletes an operation in stack
void pop(NodePtr *currentPtr) {
	NodePtr tempPtr;

	tempPtr = *currentPtr;
	*currentPtr	= (*currentPtr)->nextPtr;
	
	free(tempPtr);
}

//prints final queue list
void print(NodePtr currentPtr) {
	while(currentPtr != NULL){
		printf("%c", currentPtr->data);
		currentPtr = currentPtr->nextPtr;
	}
}
