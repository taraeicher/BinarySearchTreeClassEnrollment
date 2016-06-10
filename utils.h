/*Program Description: Copy a string from a stream to array using getString function.
*						Print a string from an array to a stream using printString function.
*						Use get_int, get_long, get_float, and get_double for string-to-
*						number conversions.
*Programer Name: Tara Eicher
*WSU ID: z847x563
*Professor: Karen Milberger
*Date Completed: 9/7/2013
*/

//Print prompt and convert user input to integer.

int get_int(char *prompt);

//Print prompt and convert user input to long.

long get_long(char *prompt);

//Print prompt and convert user input to float.

float get_float(char *prompt);

//Print prompt and convert user input to double.

double get_double(char *prompt);

//Get string of specified length limit and store it to specified array.
//Stop at the given sentinel.

int getString(char *string, int limit, char sentinel, FILE *stream);
