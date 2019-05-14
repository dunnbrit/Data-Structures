/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Brittany Dunn	
 * Date: August 13,2018
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    //make sure map is not null
    assert(map !=0);
    
    HashLink* current;
    HashLink* temp;
    
    //For each table bucket
    for(int i=0; i <map->capacity;i++){
	//Set current to the first link of table bucket
	current = map->table[i];
	//Delete the linked list associated with table bucket
	while(current != 0){
	    //Set temp to current
	    temp = current;
	    //Set current to temp next
	    current = temp->next;
	    //Delete temp
	    hashLinkDelete(temp);
	}
    }
    //Delete the map table
    free(map->table);
    //Set map size(links) to 0
    map->size = 0;
    //Set map capacity(buckets) to 0
    map->capacity = 0;
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    //make sure map and key are not null
    assert(map != 0);
    assert(key != 0);
    
    //Get the index using the key
    int index = HASH_FUNCTION(key)% map->capacity;
    
    //Set current to first link in bucket
    HashLink* current = map->table[index];
    
    //Check each link in bucket for key
    while(current != 0){
	//If current link key is equal to key
	if(strcmp(current->key,key)==0){
	    //Return pointer to the value of current link
	    return &(current->value);
	}
	//If not equal set current to next
	current = current->next;
    }
    //If not found return null
    return 0;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given 
 * capacity (double of the old capacity). After allocating the new table, 
 * all of the links need to rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    //make sure map is not null
    assert(map !=0);
    //make sure capcity is greater than 0
    assert(capacity > 0);
    
    //Create a new map using hashMapNew
    HashMap* newMap = hashMapNew(capacity);
    
    HashLink* current;
    
    for(int i = 0; i <map->capacity;i++){
	//Set current to table bucket
	current = map->table[i];
	
	//While current is not null
	while(current != 0){
	    //use hashMapPut to put each link key and val in the newMap table
	    hashMapPut(newMap,current->key,current->value);
	    //Set current to next
	    current = current->next;
	}
    }
    
    //Delete the old table using hashMapCleanUp
    hashMapCleanUp(map);
    
    //Set map size,table,and capacity equal to newMap
    map->capacity = newMap->capacity;
    map->size = newMap->size;
    map->table = newMap->table;
    
    //Delete newMap
    hashMapDelete(newMap);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    //make sure map is not null
    assert(map !=0);
    //make sure key is not null
    assert(key != 0);
    
    
    //Check if key already exists using hashMapContainsKey
    if(hashMapContainsKey(map,key)==1){
	//Get pointer to value using hashMapGet
	int* valuePtr = hashMapGet(map,key);
	//Update value
	*valuePtr += value;
    }
    
    //If key does not exist then add it
    else{
	//Get table index
	int index = HASH_FUNCTION(key) % map->capacity;
	
	//Create link using hashLinkNew
	//Next points to the current first link in table bucket at index
	HashLink* link = hashLinkNew(key,value,map->table[index]);
	
	//Make sure new link is not null
	assert(link != 0);
	
	//Change the first link in table bucket at index to new link
	map->table[index] = link;
	
	//Increase map size
	map->size++;
	
	//Check if table needs to be resized
	//Get load factor
	float load = hashMapTableLoad(map);
	//Compare load to max load
	if(load >= MAX_TABLE_LOAD){
	    
	    //If load is more than max then resize
	    int capacity = map->capacity;
	    capacity *= 2;
	    resizeTable(map,capacity);
	}
    }
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    //make sure map is not null
    assert(map != 0);
    //make sure key is not null
    assert(key != 0);
    
    //Check if key is in table, if it does then remove
    if(hashMapContainsKey(map,key)==1){
	//Get table index
	int index = HASH_FUNCTION(key) % map->capacity;
	
	//Set current to first link in table bucket
	HashLink* current = map->table[index];
	//Set previous to null
	HashLink* previous = 0;
	
	//If key is first link in bucket
	if(strcmp(current->key,key)== 0){
	    //Set first link to current next
	    map->table[index] = current->next;
	    //Delete current
	    hashLinkDelete(current);
	    //Decrease map size
	    map->size--;
	    //Set current to null
	    current = 0;
	}
	
	//While current is not null
	while(current != 0){
	    //If key is equal to current key then remove
	    if(strcmp(current->key,key)== 0){
		//Set previous next to current next
		previous->next = current->next;
		//Delete current
		hashLinkDelete(current);
		//Decrease map size
		map->size--;
		//Set current to null
		current = 0;
	    }
	    //else set previous to current and current to next
	    else{
		previous = current;
		current = current->next;
	    }
	}
    }
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    //make sure map is not null
    assert(map !=0);
    //make sure key is not null
    assert(key !=0);
    
    //Get table index
    int index = HASH_FUNCTION(key) % map->capacity;
    
    //Set current to first link in table bucket
    HashLink* current = map->table[index];
    
    //While current is not null
    while(current != 0){
	//If key is equal to current key
	if(strcmp(current->key,key)==0){
	    //then return 1
	    return 1;
	}
	//else set current to next
	current = current->next;
    }
    
    //if not found return 0
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    //make sure map is not null
    assert(map !=0);
    
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    //make sure map is not null
    assert(map !=0);
    
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    //make sure map is not null
    assert(map !=0);
    
    int emptyBuckets = 0;
    
    //Check if each table bucket is empty
    for(int i = 0; i < map->capacity; i++){
	//If bucket's first link is null
	if(map->table[i]== 0){
	    //Then increment emptyBuckets
	    emptyBuckets++;
	}
    }
    
    return emptyBuckets;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    //make sure map is not null
    assert(map !=0);
    
    //Make size and capacity float instead of int
    float size = (float)map->size;
    float capacity = (float)map->capacity;
    
    //Return ratio of links/buckets
    return size/capacity;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    //make sure map is not null
    assert(map !=0);
    
    HashLink* current;
    
    //For each table bucket
    for(int i = 0; i < map->capacity; i++){
	printf("\n");
	
	//Set current to first link of bucket
	current = map->table[i];
	
	printf("Bucket %i->",i);
	
	//While current is not null
	while(current !=0){
	    //Print each link key and value
	    printf("(%s,%d)->", current->key,current->value);
	    //Set current to next
	    current = current->next;
	}
    }  
}
