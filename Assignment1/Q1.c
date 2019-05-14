/* CS261- Assignment 1 - Q.1*/
/* Name: Brittany Dunn
 * Date: July 10, 2018
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     int numberOfStudents = 10;
     struct student *studentPtr = malloc(numberOfStudents * sizeof(struct student));
     /*Return the pointer*/
     return studentPtr;
}

void generate(struct student* students){
     /*Generate random and unique IDs and random scores for ten students, 
IDs being between 1 and 10, scores between 0 and 100*/
     int id;
     int i;
     int j;
     int unique;
     int score;
     //Generate unique student ID
      for(i = 0; i < 10; ++i)
     {
	do
	{
	     //Set unique to true
	     unique = 1;
	     //Get random ID
	     id = rand() % 10 + 1;
	     //Check ID is unique
	     for(j = 0; j < i + 1; ++j)
	     {
	       //If not unique, set unique to false
	       if(id == students[j].id)
	       {
		    unique = 0;
	       }
	     }
	//Repeat until unique ID is generated
	}while(unique == 0);
	//Set student ID
	students[i].id = id;
     }
     //Generate unique student score
       for(i = 0; i < 10; ++i)
     {
	do
	{
	     //Set unique to true
	     unique = 1;
	     //Get random score
	     score = rand() % 100 + 1;
	     //Check score is unique
	     for(j = 0; j < i + 1; ++j)
	     {
	       //If not unique, set unique to false
	       if(score == students[j].score)
	       {
		    unique = 0;
	       }
	     }
	//Repeat until unique score is generated
	}while(unique == 0);
	//Set student score
	students[i].score = score;
     }          
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
     int i;
     
     for(i = 0; i < 10; ++i)
     {
	printf("%d ",students[i].id);
	printf("%d \n",students[i].score);
     }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the 
ten students*/
     int min = 100;
     int max = 0;
     double avg = 0;
     int i = 0;
     
     for(i = 0; i < 10; i++)
     {
	  if(students[i].score <= min)
	  {
	       min = students[i].score;
	  }
	  if(students[i].score >= max)
	  {
	       max = students[i].score;
	  } 
	  avg += students[i].score;
     }
     
     avg /= 10;
     
     printf("The minimum score was %d. \n", min);
     printf("The maximum score was %d. \n", max);
     printf("The average score was %g. \n", avg);

}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
     if(stud != NULL)
     {
	  free(stud);
     }
}
int main(){
    struct student* stud = NULL;
    srand(time(0));
    /*Call allocate*/
    stud = allocate();
    /*Call generate*/
    generate(stud);
    /*Call output*/
    output(stud);
    /*Call summary*/
    summary(stud);
    /*Call deallocate*/
    deallocate(stud);
    
    return 0;
}

