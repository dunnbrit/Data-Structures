#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
	    //Convert char to lowercase
	    c = tolower(c);
	    
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
     //Set word to first word from file using nextWord
    char* word = nextWord(file);
    
    //While word is not null
    while(word != 0){
	//Add to map using hashMapPut
	hashMapPut(map,word,1);
	//Free word
	free(word);
	//Get next word
	word = nextWord(file);
    }
}

//Function from https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

int levenshtein(char *s1, char *s2) {
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int column[s1len+1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x-1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return(column[s1len]);
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(11000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    printf("\n");
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        
        //Convert input to lowercase
	for(int i = 0; i <sizeof(inputBuffer); i++){
	    inputBuffer[i] = tolower(inputBuffer[i]);
	}
	
	//If quit then exit
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
	
	//If not quit check if input matches a key
	else if(hashMapContainsKey(map,inputBuffer)==1){
	    printf("The inputted word %s is spelled correctly \n",inputBuffer);
	}
	
	//If no match then get suggestions
	else{
	   //Create an array to store 5 HashLinks
	   HashLink* words[5];
	   
	   HashLink* current;
	   int distance;
	   int count = 0;
	   
	   //Go through all words in dictionary, add levenshtein dist as val
	   for(int i = 0; i < map->capacity; i++){
	       //Set current to first link in table bucket
	       current = map->table[i];
	   
	       //While current is not null (not at end of bucket)
	       while(current != 0){
		   //Calculate levenshtein distance for link
		   distance = levenshtein(inputBuffer,current->key);
		   //Update value to distance
		   current->value = distance;
		   //Add first 5 key words to array
		   if(count < 5){
		       //Add word to array
		       words[count] = current;
		       
		       //Increment count
		       count++;
		   }
		   //Else compare to words to see if distance is less
		   else{
		       //For each word (HashLink)
		       for(int i = 0; i < 5; i++){
			   //Check if distance is less than word distance 
			    if(distance < words[i]->value){
				//If less then replace word
				words[i] = current;
				//Set i to 5 to exit
				i = 5;
			    }
		        }
		    }
		   //Set current to next
		   current = current->next;
	       }
	   }
	   printf("The inputted word %s is spelled incorrectly \n",inputBuffer);
	   printf("Did you mean ");
	   for (int i = 0; i < 5; i++){
	       printf("%s ",words[i]->key);
	   }
	   printf("? \n");
	}
	printf("\n");
    }
    hashMapDelete(map);
    return 0;
}