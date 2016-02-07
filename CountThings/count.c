#include<stdio.h>
#include<stdbool.h>


int digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

bool is_digit(int character) {
	for(int i=0; i<10; ++i)
		if(character == digits[i])
			return true;

	return false;
}

/* Count digits, white spaces characters (blank, tab, newline),
   and of all other characters. */

int main()
{
	int c, ndigit, nwhite, nother;	
	ndigit = nwhite = nother = 0;
	
	while((c = getchar()) != EOF) {
		if(is_digit(c))
			++ndigit;
		else if(c == ' ' || c == '\t' || c == '\n')
			++nwhite;
		else
			++nother;
	}

	printf("\nno. of digits:\t%d\n", ndigit);
	printf("no. of whitespaces:\t%d\n", nwhite);
	printf("no. of other:\t%d\n", nother);
}
