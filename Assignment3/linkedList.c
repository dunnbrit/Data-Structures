#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to each other or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
    //Dynamically allocate front sentinel
    list->frontSentinel = malloc(sizeof(struct Link));
    //Make sure front sentinel is not null
    assert(list->frontSentinel != 0);
    //Dynamically allocate back sentinel
    list->backSentinel = malloc(sizeof(struct Link));
    //Make sure back sentinel is not null
    assert(list->backSentinel != 0);
    //Front sentinel next will point to back sentinel
    //prev is null
    list->frontSentinel->next = list->backSentinel;
    //Back sentinel prev will point to front sentinel
    //next is null
    list->backSentinel->prev = list->frontSentinel;
    //Set list size to 0
    list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
    //Make sure link is not null
    assert(link != 0);
    //Dynamically allocate new link
    struct Link *newLink = (struct Link *)malloc(sizeof(struct Link));
    //Make sure new link is not null
    assert(newLink != 0);
    //Set value of link to value
    newLink->value = value;
    //Set next of new link to link passed in
    newLink->next = link;
    //Set prev of new link to the prev of link passed in
    newLink->prev = link->prev;
    //Change the next of the link before the link passed in to the new link
    link->prev->next = newLink;
    //Change prev of link passed in to new link
    link->prev = newLink;
    //Increase size of list
    list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
    //Make sure link is not null
    assert(link != 0);
    //Set the link before passed in link next to the next of passed in link
    link->prev->next = link->next;
    //Set the link after passed in link prev to the prev of passed in link
    link->next->prev = link->prev;
    //Delete link
    free(link);
    link = 0;
    //Decrease size of list
    list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
    //Use addLinkBefore function to add a link before the current front
    addLinkBefore(list, list->frontSentinel->next, value); 
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
    //USe addLinkBefore function to add a link before the back sentinel
    addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
    //Make sure list in not empty
    assert(!linkedListIsEmpty(list));
    //Return front of list value
    return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
    //Make sure list is not empty
    assert(!linkedListIsEmpty(list));
    //Return value of list back
    return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
    //Make sure list is not empty
    assert(! linkedListIsEmpty(list));
    //Remove front link
    removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
    //Make sure list is not empty
    assert(! linkedListIsEmpty(list));
    //Remove back link
    removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
    //Return 1 (true) if size is zero
    if(list->size == 0){
        return 1;
    }
    //Else return 0 (false) if size is greater than 0
    else{
        return 0;
    }
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
    //If empty print list empty
    if(linkedListIsEmpty(list)){
        printf("List is empty. \n");
    }
    //Else print list
    else{
        printf("Current List: ");
        //Set mylink to first link
        struct Link* myLink = list->frontSentinel->next;
        while(myLink != list->backSentinel){
            //Using integer because it is defined in linkedList.h
            printf(" %i ", myLink->value);
            myLink = myLink->next;
        }
        printf("\n");
    }
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
    //Use addLinkBefore function to add link to front of list
    addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
    //Make sure list is not null
    assert(list != 0);
    //If list is empty return 0 (false)
    if(linkedListIsEmpty(list)){
        return 0;
    }
    //Else search for value
    else{
        //Set current to first link
        struct Link *current = list->frontSentinel->next; 
    
        // Loop through list and check each for the parameter value
        for(int i = 0; i < list->size; i++){
            //If found return 1 (true)
            if(current->value == value){
                return 1;
            } 
            else {
                //Set current to next link
                current = current->next;
            }
        }
    }
    //If not found and searched whole list return 0 (false)
    return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
    //Make sure list is not null
    assert(list != 0);
    //Set current to first link
    struct Link *current = list->frontSentinel->next;
    //Set valueFound to 0 (false)
    int valueFound = 0;
    //Loop through the list and compare each value to the parameter
    for(int i = 0; i < list->size && valueFound == 0; i++){
        //If value found then remove
        if(current->value == value){
            removeLink(list, current);
            valueFound = 1; // Break Loop
        }
        else {
            //Change current to next
            current = current->next;
        }
    } 
}
