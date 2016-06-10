/*Program Description: Read in a list of car students records from a given file.
*						Delete cars made in a given name and output to file.
*Programer Name: Tara Eicher
*WSU ID: z847x563
*Professor: Karen Milberger
*Date Completed: 9/24/2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "bin_search_tree.h"

//main function

int main(void)
{
	/******************************VARS**********************************************/
	char input1[]={"enrollment_list\0"};	//input1 file 1
	char input2[]={"drop_list\0"};		//input1 file 2
	char output[]={"classlist.txt\0"};		//output file
	Tree students;								//class list
	
	//message to user that output file is done
	
	char done[]={"The class list was saved in the file\0"};
	
	/*************************VARS**************************************************/ 

	FILE *enroll;		//enrollment file stream
	FILE *drop;		//drop file stream
	FILE *classlist;	//output file stream

	//Open the input files. Exit if file(s) could not be opened.

	if(!(enroll=fopen(input1,"r")))
	{
		printf("The enrollment file did not open properly. The program will now terminate.\n");
		return -1;
	}

	if(!(drop=fopen(input2,"r")))
	{
		printf("The drop file did not open properly. The program will now terminate.\n");
		return -1;
	}

	//Initialize the list and read in the data from the enrollment file.
	
	tree_init(&students);
	int goodData=populate(enroll,&students);

	//Exit if file was improperly formatted (returns 0).
	//Exit if the file did not close (returns 2).

	if(goodData==0)
	{
		printf("The enrollment file was improperly formatted. The program will now terminate.\n");
		return -1;
	}
	else if(goodData==2)
	{
		printf("The enrollment file did not close properly. The program will now terminate.\n");
		return -1;
	}
	
	//Read in the data from the drop file and delete records from tree.
	
	goodData=deleteFromFile(drop,students);

	//Exit if file was improperly formatted (returns 0).
	//Exit if the file did not close (returns 2).

	if(goodData==0)
	{
		printf("The drop file was improperly formatted. The program will now terminate.\n");
		return -1;
	}
	else if(goodData==2)
	{
		printf("The drop file did not close properly. The program will now terminate.\n");
		return -1;
	}
		

	//Open the output file. Exit if the file could not be opened.

	if(!(classlist=fopen(output,"w")))
	{
		printf("The output file did not open properly. The program will now terminate.\n");
		return -1;
	}
	
	//Print the list to the output file.
	
	fprintf(classlist,"Class List for CS 300:\n\n");
	tree_inorder(students,classlist);
	int closed=(fclose(classlist));
	
	//Exit if the file did not close (returns 0).
	
	if(closed!=0)
	{
		printf("The output file did not close properly. The program will now terminate.\n");
		return -1;
	}
	
	//Tell user that output file is done.
	
	printf("%s %s.\n",done,output);
	
	//Close and exit the program.
	
	return 0;
}
