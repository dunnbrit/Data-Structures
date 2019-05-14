/* CS261- Assignment 1 - Q.3*/
/* Name: Brittany Dunn
 * Date: July 10 2018
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>

void deleteChar(int position, int length, char* str)
{
     //Delete character by shifting all elements left one
     int i = 0;
     for(i = position; i < length; ++i)
     {
          str[i] = str[i+1];
     }
}


char toUpperCase(char ch){
  /*Convert ch to upper case, assuming it is in lower case currently*/
    ch -= 32;
    return ch; 
}

char toLowerCase(char ch){
  /*Convert ch to lower case, assuming it is in upper case currently*/                          
     ch += 32;
     return ch;
}

int stringLength(char s[]) {
   /*Return the length of the string*/
     int length = 0;
     do
     {
	  if(s[length] == ' ')
	  {
	       s[length] = '1';
	  }
	  ++length;
     }
     while(s[length] != '\0');
     return length;
}


void camelCase(char* word){
	/*Convert to camelCase*/
	  //Get length
	  int length = 0;
	  length = stringLength(word);
	  //convert word
	  int i = 0;
	  for(i = 0; i < length; ++i)
	  {
	       if(word[i] == '_')
	       {
		    //Change letter following _ to uppercase
		    word[i+1] = toUpperCase(word[i+1]);
		    //Delete underscore
		    deleteChar(i,length,word);
		    --length;
	       }
	  }
	
}

void toUnderScore(int size, char* str)
{
     int i = 0;
     int letter = 0;
     //Convert any non-letters to _
     for(i = 0; i < size; ++i)
     {
	  letter = 0;
	  //If uppercase letter
	  if(str[i] >= 'A' && str[i] <= 'Z')
	  {
	       //Then letter is true
	       letter = 1;
	  }
	  //If lowercase letter
	  if(str[i] >= 'a' && str[i] <= 'z')
	  {
	       //Then letter is true
	       letter = 1;
	  }
	  //If not a letter
	  if(letter == 0)
	  {
	       //convert to _
	       str[i] = '_';
	  }
     }
}
    

int main(){

	/*Read the string from the keyboard*/
	  char input[100];
	  printf("Please input a string: \n");
	  scanf("%[^\n]s",input);
	  //Get length of string
	  int length = 0;
	  length = stringLength(input);
	  //Change any non-letters to _
	  toUnderScore(length, input);
	  //Validate Input
	  int underScores = 0;
	  int chars = 0;
	  int i = 0;
	  //Check for number of letters and underscores 
	  for(i = 0; i < length; i++)
	  {
	       if(input[i]== '_')
	       {
		    ++underScores; 
	       }
	       if(input[i] >= 'A' && input[i] <= 'Z')
	       {
		    ++chars;
	       }
	       if(input[i] >= 'a' && input[i] <= 'z')
	       {
		    ++chars;
	       }
	  }
	  //If there is not a underscore or a letter then invalid
	  if(underScores < 1 || chars < 1)
	  {
	       printf("Invalid input string\n");
	       //Exit program
	       return 0;
	  }
	  //If there is only one word then invalid
	  if(underScores == 2 && input[0] && '_' && input[length-1] == '_')
	  {
	       printf("Invalid input string\n");
	       //Exit program
	       return 0;
	  }     
	/*Call camelCase*/
	  //Convert to proper form before calling
	  for(i = 0; i < length; i++)
	  {
	       //Delete repeating underscores
	       if(input[i] == '_' && input[i+1] == '_')
	       {
		    deleteChar(i,length,input);
		    --length;
	       }
	       //Convert all uppercase letters to lowercase
	       if(input[i] >= 'A' && input[i] <= 'Z')
	       {
		    input[i] = toLowerCase(input[i]);
	       }
	  }
	  //If string begins with underscore then delete it
	  if(input[0] == '_')
	  {
	    deleteChar(0,length,input);
	    --length;
	  }
	  //If string ends with underscore then delete it
	  if(input[length-1] == '_')
	  {
	    deleteChar(length-1,length,input);
	    --length;
	  }
	  //Convert to camelCase
	  camelCase(input);
	/*Print the new string*/
	  printf("%s \n",input);
	
	return 0;
}

