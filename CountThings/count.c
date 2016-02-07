#include<stdio.h>
#include<stdbool.h>

/* Count digits, white spaces characters (blank, tab, newline),
   and of all other characters. */

int main()
{
	int c, ndigit, nwhite, nother;	
	int digitcount[10];
	
	ndigit = nwhite = nother = 0;
	for(int i=0; i<10; ++i)
		digitcount[i] = 0;
			

	while((c = getchar()) != EOF) {
		if(c >= '0' && c <= '9')
			++digitcount[c-'0'];
		else if(c == ' ' || c == '\t' || c == '\n')
			++nwhite;
		else
			++nother;
	}

	printf("\nno. of digits:\n");
	for(int i=0; i<10; ++i)
		printf("\t%2d count:\t%2d \n", i, digitcount[i]);

	printf("no. of whitespaces:\t%2d\n", nwhite);
	printf("no. of other:\t%2d\n", nother);
}
