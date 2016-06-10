/*Program Description: Copy a string from a stream to array using getString function.
*						Print a string from an array to a stream using printString function.
*						Use get_int, get_long, get_float, and get_double for string-to-
*						number conversions.
*Programer Name: Tara Eicher
*WSU ID: z847x563
*Professor: Karen Milberger
*Date Completed: 9/2/2013
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

//Print prompt and convert user input to integer.

int get_int(char *prompt)
{
	int valid=0;				//validity of input
	const int cap=8;			//capacity of type
	char integer[cap+1];		//user input (extra slot for null)
	int answer=0;				//solution
	
	//Print prompt and get user input as long as previous input does not fit into array.
	
	while(!valid)
	{
		printf("%s",prompt);	//Print the prompt.

		//Get user input. If too many characters, mark invalid and repeat.

		valid=getString(integer,cap+1,'\n',stdin);	
		
		if(valid)
		{
			//Convert user input to integer using strtol function.
			//Use strlen function to create endptr.
		
			char *end;				//pointer to end of string
	
			answer=(int)strtol(integer,&end,10);

			if(end!=(integer+strlen(integer)))	
			{
				valid=0;
				printf("Please enter an integer.\n");
			}
		}
	}
	return answer;	
}

//Print prompt and convert user input to long.

long get_long(char *prompt)
{	
	const int cap=16;				//capacity of type
	char integer[cap+1];			//user input (extra slot for null)
	int valid=0;					//validity of input
	int answer=0;					//solution
	
	
	//Print prompt and get user input as long as previous input does not fit into array.
	
	while(!valid)
	{
		printf("%s",prompt);	//Print the prompt.
		
		//Get user input. If too many characters, mark invalid and repeat.
		
		valid=getString(integer,cap+1,'\n',stdin);		

		//If string is too long to convert, tell user.

		if(valid)
		{

			//Convert user input to integer using strtol function.
			//Use strlen function to create endptr.
		
			char *end;				//pointer to end of string
	
			answer=strtol(integer,&end,10);

			if(end!=integer+strlen(integer))	
			{
				valid=0;
				printf("Please enter an integer.\n");
			}
		}
	}
	
	return answer;
}

//Print prompt and convert user input to float.

float get_float(char *prompt)
{
	const int cap=32;					//capacity of type
	char strFloat[cap+1];				//user input (extra slot for null)
	int valid=0;						//validity of input
	float answer=0;						//solution

	//Print prompt and get user input as long as previous input does not fit into array.

	while(!valid)
	{
		printf("%s",prompt);	//Print the prompt.
		
		//Get user input. If too many characters, mark invalid and repeat.
		
		valid=getString(strFloat,cap+1,'\n',stdin);		

		if(valid)
		{

			//Convert user input to integer using strtol function.
			//Use strlen function to create endptr.
		
			char *end;				//pointer to end of string
	
			answer=strtof(strFloat,&end);

			if(end!=strFloat+strlen(strFloat))	
			{
				valid=0;
				printf("Please enter a number.\n");
			}
		}
	}
	return answer;
}

//Print prompt and convert user input to double.

double get_double(char *prompt)
{
	const int cap=64;			//capacity of type
	char strDouble[cap+1];		//user input (extra slot for null)
	int valid=0;				//validity of user input
	double answer;				//solution

	//Print prompt and get user input as long as previous input does not fit into array.

	while(!valid)
	{
		printf("%s",prompt);	//Print the prompt.
		
		//Get user input. If too many characters, mark invalid and repeat.
		
		valid=getString(strDouble,cap+1,'\n',stdin);		

		if(valid)
		{

			//Convert user input to integer using strtol function.
			//Use strlen function to create endptr.
		
			char *end;				//pointer to end of string
	
			answer=strtof(strDouble,&end);

			if(end!=strDouble+strlen(strDouble))	
			{
				valid=0;
				printf("Please enter a number.\n");
			}
		}
	}
	return answer;
}

//Get string of specified length limit and store it to specified array.
//Stop at the given sentinel.

int getString(char *string, int limit, char sentinel, FILE *stream)
{
	char *start=string;		//Mark the beginning of the array.
	*string=getc(stream);    	//Get first character.
	int isEnd=feof(stream);		//Determine whether file has ended.
	int retVal=-1;			//Return -1 at EOF, 0 if string too long, 1 otherwise.

	//Read character-by-character until a newline is reached.

	while((*string!=sentinel)&&(!isEnd))
	{
		++string;
		*string=getc(stream);		
		isEnd=feof(stream);	//Determine whether file has ended.
		
		//If sentinel is not reached in the limited number of characters, return 0.
	
		if(string>start+limit-1)
			retVal=0;
	} 
	
	//Get rid of sentinel character.
	
	*string='\0';
	
	//Return -1 at EOF.
	
	if(isEnd)
		retVal=-1;
		
	//If return value is not zero (string not too long), set to 1.
		
	else if(!retVal)
		printf("ERROR: Number of characters in input exceeds %d. Please try again.\n",limit-1);
	else
		retVal=1;
		
	//Return the return value.

	return retVal;
}
