/*
 * This is the file in which you'll write the functions required to 
implement
 * a stack using two queues.  Make sure to add your name and 
@oregonstate.edu
 * email address below:
 *
 * Name: Brittany Dunn
 * Email: dunnbrit@oregonstate.edu
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


#ifndef TYPE
#define TYPE int
#endif

/**************************************************
 All of the initial Queue functions
 ***************************************************/
struct link {
	TYPE value;
	struct link * next;
};

struct listQueue {
	struct link *firstLink;
	struct link *lastLink;
	int size;
};

/*
* This function takes a queue and allocates the memory. It then
* creates a sentinel and assigns the first link and last link
* to the sentinel.
*/
void listQueueInit(struct listQueue *q) {

 //Create sentinel
 struct link *sentinel = (struct link *) malloc(sizeof(struct link));
 //Make sure sentinel is not null
 assert(sentinel != 0);
//Set next to null
 sentinel->next = 0;
 //Set first and last link to sentinel 
 q->firstLink = q->lastLink = sentinel;

}

/*
 * This function creates a new queue. Parts of the create include 
allocating
 * the memory, initializing all of the values and returning a pointer to 
the newly
 * created queue.
 */
struct listQueue * listQueueCreate()
{
    //Dynamically allocate listQueue
    struct listQueue *queue = (struct listQueue *) malloc(sizeof(struct listQueue));
    //Make sure queue is not null
    assert(queue != 0);
    //Use listQueueInit function to initialize all values
    listQueueInit(queue);
    //return pointer to listQueue
    return queue;

	
}


/*
* This function returns a 1 or 0 based on the statement looking at
* the first link. If the next value is null it is empty, and will return 1
*/
int listQueueIsEmpty(struct listQueue *q) {
    //Return 1 (true) if list is empty
    if(q->firstLink->next == 0){
	return 1;
    }
    //Return 0 (false) if not empty
    else{
	return 0;
    }

}

/*
 * This function adds a new link and value to the back of the queue. It 
takes
 * a list and a type variable, allocates the memory and adjusts the proper 
links
 * to make the connection. No return value.
 */
void listQueueAddBack(struct listQueue *q, TYPE e) {
    //Create new link
    struct link * newLink = (struct link *) malloc(sizeof(struct link));
    //Make sure new link is not null
    assert (newLink != 0);
    //Set lastLink's next to new link
    q->lastLink->next = newLink;
    //Set lastLink to new link
    q->lastLink = newLink;
    //Set value of new link
    newLink->value = e;
    //Set next of new link to null
    newLink->next = 0;
}

/*
 * This function takes a list argument and removes the link at the front.
 */
void listQueueRemoveFront(struct listQueue *q) {
    //Make sure list is not empty
    assert(!listQueueIsEmpty(q));
    //Create a temp link to hold first link after sentinel
    struct link* temp = q->firstLink->next;
    //if there is only one link in queue
    if (q->firstLink->next == q->lastLink){
	//Set last link and first link to sentinel
	q->lastLink = q->firstLink;
	//Set firstLink next to null
	q->firstLink->next = 0;
    //If more than one link
    }else{
	//Set first link next to the second link
	q->firstLink->next = q->firstLink->next->next;
    }
    //Delete first link
    free(temp);
    //and set to null
    temp = 0;
}

/*
 * Function returns the value at the front of the list.
 */
TYPE listQueueFront(struct listQueue *q) {
    //Make sure list is not empty
    assert(!listQueueIsEmpty(q));
    //Return value of first link
    return q->firstLink->next->value;

}


/*
* This function is a tester function that iterates through the list
* and prints out the values at each link.
*/
void printList(struct listQueue* l)
{
	assert(l != 0);
	
	struct link * printMe = l->firstLink->next;

	while (printMe!= NULL)
	{
		printf("Value: %d\n", printMe->value);
		printMe = printMe->next;
	}
}

/**************************************************
Stack Implementation
***************************************************/

struct linkedListStack {
	struct listQueue *Q1;
	struct listQueue *Q2;
	int structSize;
};

/*
 * This function initializes the values of the created Stack. Initializes 
both 
 * queues and the structSize.
 */
void linkedListStackInit(struct linkedListStack * s)
{
    //Make sure stack is not null
    assert(s != 0);
    //Set size to 0
    s->structSize = 0;
    //Create and set Q1 and Q2
    s->Q1 = listQueueCreate();
    s->Q2 = listQueueCreate();
 }

/*
* This function creates the linked list stack. It allocates the memory and 
calls the
* initialization function to initialize all of the values. It then returns 
the stack.
*/
struct linkedListStack * linkedListStackCreate(){
    //Dynamically allocate listQueue
    struct linkedListStack *myStack = (struct linkedListStack *) malloc(sizeof(struct linkedListStack));
    //Make sure queue is not null
    assert(myStack != 0);
    //Use linkedListStackInit function to initialize all values
    linkedListStackInit(myStack);
    //return pointer to listQueue
    return myStack;
}

/*
* This function returns 1 if the linked list stack is empty and otherwise 
returns a 0.
*/
int linkedListStackIsEmpty(struct linkedListStack *s) {
    //If empty return 1 (true)
    if(s->structSize == 0){
        return 1;
    }
    //Else return 0 (false)
    else{
        return 0;
    }
}

/*
 * This is the linked list acting as a stack push function. It takes 
 * a linked list stack argument and a value and pushes it onto the stack. 
The
 * funciton then also increases the size of the stack by 1. 
 */
void linkedListStackPush(struct linkedListStack *s, TYPE d) {
    //Make sure stack is not null
    assert(s != 0);
    //Add link to back of Q1
    listQueueAddBack(s->Q1,d);
    //Increase size
    s->structSize++;
}
/*
 * This funciton pops a value off of the stack. It does this by moving all 
values
 * that are currently on the stack to the other queue. The stack top is 
maintained
 * at the back of the queue list. 
 */
void linkedListStackPop(struct linkedListStack *s) {
    //If stack is empty then print error message
    if(linkedListStackIsEmpty(s)){
        printf("Cannot pop empty stack \n");
    }
    else{
        for(int i = 0; i < s->structSize-1; i++){
            //Move all of stack except top from Q1 to Q2
            listQueueAddBack(s->Q2,listQueueFront(s->Q1));
            //Remove links from Q1
            listQueueRemoveFront(s->Q1);
        }
        //Pop (remove) value from stack (Q1)
        listQueueRemoveFront(s->Q1);
	//Decrease structsize
	s->structSize--;
        for(int j = 0; j < s->structSize; j++){
	    //Move all of stack except from Q2 back to Q1
	    listQueueAddBack(s->Q1,listQueueFront(s->Q2));
	    //Remove links from Q2
	    listQueueRemoveFront(s->Q2);  
        }
    }
}
/*
 * This function returns the value that is at the back of the queue that 
is 
 * maintaing the values of the stack. 
 */
TYPE linkedListStackTop(struct linkedListStack *s) {
    //Make sure stack is not empty
    assert(!linkedListStackIsEmpty(s));
    //Return value of top of stack(Q1)
    return s->Q1->lastLink->value;
}

/*
 * This function gores through the stack and removes each link in the 
queue.
 * It then frees the struct itself. 
 */
void linkedListStackFree(struct linkedListStack *s){
    assert(s != 0);
	
    while (s->structSize != 0) 
    {
	linkedListStackPop(s);
    }

    free(s->Q1->firstLink);
    free(s->Q2->firstLink);
    free(s->Q1);
    free(s->Q2);
    free(s);
}

/*
 * Main is used to test the stack ADT.
 */
int main(int argc, char* argv[])
{
     
    struct linkedListStack *stack = linkedListStackCreate();

	//Test Stack
	//Push 4 values onto the stack
	printf("Pushing the value: 1\n");
	linkedListStackPush(stack, 1);
	printf("Pushed.\n\n");

	printf("Pushing the value: 2\n");
	linkedListStackPush(stack, 2);
	printf("Pushed.\n\n");

	printf("Pushing the value: 3\n");
	linkedListStackPush(stack, 3);
	printf("Pushed.\n\n");

	printf("Pushing the value: 4\n");
	linkedListStackPush(stack, 4);
	printf("Pushed.\n\n");



	//Print value at the top and then remove it
	printf("Value at the top of stack %d now being popped. \n",linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));  
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	//Try to pop when the stack is empty prints error:
	printf("Trying to pop empty stack:\n");

	linkedListStackPop(stack);

	
	//Push and Pop alternating
	printf("Pushing the value: 10\n");
	linkedListStackPush(stack, 10);
	printf("Pushed.\n\n");

	printf("Pushing the value: 11\n");
	linkedListStackPush(stack, 11);
	printf("Pushed.\n\n");

	printf("One more pop:\n");
	linkedListStackPop(stack);
	printf("Value at the top of stack: %d\n", 
	linkedListStackTop(stack));

	linkedListStackFree(stack);

	return 0;

}





