#include<stdio.h>

/* Count digits, white spaces characters (blank, tab, newline),
   and of all other characters. */

int main()
{
	int c, nd, nb, nt, nn;
	nd = nb = nt = nn = 0;
	
	while((c = getchar()) != EOF) {
		if(c == '0' || c == '1' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
			++nd;
		else if(c == ' ')
			++nb;
		else if(c == '\t')
			++nt;
		else if(c == '\n')
			++nn;
	}

	printf("no. of digits:\t%d\n", nd);
	printf("no. of blanks:\t%d\n", nb);
	printf("no. of tabs:\t%d\n", nt);
	printf("no. of newline:\t%d\n", nn);

}
