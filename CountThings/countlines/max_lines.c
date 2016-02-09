#include<stdio.h>
#include<stdlib.h>

#define MAXLINELEN 1500

int get_line(FILE *fp, char curr_array[]);
void save(char src[], char dest[], int length);

int main()
{
	FILE *fp = fopen("max_lines.c", "r");
	char curr_line[MAXLINELEN]; /* Stores the current line */
	char max_line[MAXLINELEN];  /* Stores the longest line */
	int maxline_length, currline_length;

	maxline_length = currline_length = 0;

	while((currline_length = get_line(fp, curr_line)) >= 0 )
		if(currline_length > maxline_length) {
			maxline_length = currline_length;
			save(curr_line, max_line, maxline_length);
		}
	
	for(int i=0; i<maxline_length; ++i)
		printf("%c", max_line[i]);
	printf("\n");
	
	free(fp);
}


void save(char src[], char dest[], int length) {
	for(int i = 0; i < length; ++i)
		dest[i]=src[i];
}


int get_line(FILE *fp, char curr_array[]) {
	char c;
	int line_length = 0;
	
	if((c = getc(fp)) == EOF)
		return -1;
	else {
		do {	
			if(c != '\n' && c != EOF) {
				curr_array[line_length] = c;
				++line_length;
			}
			else {
				break;
			}
		} while((c = getc(fp)) != EOF);
	}
	
	return line_length;
}
