#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
    //Dynamically allocate front sentinel
    list->sentinel = malloc(sizeof(struct Link));
    //Make sure sentinel is not null
    assert(list->sentinel != 0);
    //Set sentinel next to point to itself
    list->sentinel->next = list->sentinel;
    //Set sentinel prev to point to itself   
    list->sentinel->prev = list->sentinel;
    //Set list size to 0
    list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	//Dynamically allocate link
        struct Link* newLink = malloc(sizeof(struct Link));
	//Make sure newLink is not null
        assert(newLink != 0);
        //Set next and prev to null
        newLink->next = NULL;
        newLink->prev = NULL;
        //Set value to value passed in
        newLink->value = value;
        //Return newLink pointer
        return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
    //Make sure link is not null
    assert(link != 0);
    //Create new link using createLink function
    struct Link* newLink = createLink(value);
    //Set newLink prev to link
    newLink->prev = link;
    //Set newLink next to link's next
    newLink->next = link->next;
    //Set link next to new link
    link->next = newLink;
    //Set newLink next link's prev to newLink
    newLink->next->prev = newLink;
    //Increase list size
    list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
    //Make sure list is not empty
    assert(!circularListIsEmpty(list));
    //Make sure link is not null
    assert(link != 0);
    //Set the previous link's next to passed in link's next
    link->prev->next = link->next;
    //Set the next link's prev to passed in link's prev
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
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
        //Delete links while list is not empty
	while (!circularListIsEmpty(list))
	{
            circularListRemoveFront(list);
	}
        //Once all links are removed, delete the sentinel
	free(list->sentinel);
        //Delete the list
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
    //Use addLinkAfter function to add link after sentinel
    addLinkAfter(list,list->sentinel,value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
    //Use addLinkAfter function to add link after link before sentinel
    addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
    //Make sure list is not empty
    assert(!circularListIsEmpty(list));
    //Return value of front
    return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
    //Make sure list is not empty
    assert(!circularListIsEmpty(list));
    //Return value of front
    return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
    //Make sure list is not empty
    assert(!circularListIsEmpty(list));
    //Use removeLink function to remove front link
    removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
    //Make sure list is not empty
    assert(!circularListIsEmpty(list));
    //Use removeLink function to remove back link
    removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
    //If size is 0 then return 1 (true)
    if(list->size == 0){
        return 1;
    }
    //Else return 0 (false)
    else{
        return 0;
    }
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
    //If empty print list empty
    if(circularListIsEmpty(list)){
        printf("List is empty. \n");
    }
    //Else print list
    else{
        printf("Current List: ");
        //Set mylink to first link
        struct Link* myLink = list->sentinel->next;
        while(myLink != list->sentinel){
            //Using double because it is defined in circularList.h
            printf(" %g ", myLink->value);
            myLink = myLink->next;
        }
        printf("\n");
    }
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
    //Make sure list is not empty
    assert(!circularListIsEmpty(list));
 
    //Set current link to sentinel
    struct Link* current = list->sentinel;

   // do while current is not sentinel
   do{
       //Set temp to next link
       struct Link* temp = current->next;
       //Set current next to prev
       current->next = current->prev;
       //Set current prev to next
       current->prev = temp;
       //Set current to original next link
       current = temp;
   }while(current != list->sentinel);
}
