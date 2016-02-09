#include<stdio.h>
#include<stdlib.h>

#define MAXLINELEN 1500

char *get_line(FILE *fp, int *line_length);
//void save(char *src, char *dest);

int main()
{
	FILE *fp = fopen("max_lines.c", "r");
	char *max_line; /* Stores the longest line */
	int maxline_length;
	char *curr_line; /* Stores the current line */
	int currline_length;

	maxline_length = currline_length = 0;

	int ii = 0;
	while(curr_line = get_line(fp, &currline_length)) {
		printf("%d", currline_length);
		for(int i=0; i<MAXLINELEN; ++i)
			printf("%c", curr_line[i]);
		printf("\n");
	}
}

/*
void save(char *src, char *dest) {
	dest = malloc(MAXLINELEN);
	for(int i = 0; i < MAXLINELEN; ++i)
		dest[i]=src[i];
}
*/

char *get_line(FILE *fp, int *line_length) {
	char c;
	*line_length = 0;
	
	if((c = getc(fp)) == EOF)
		return NULL;
	else
		ungetc(c, fp);
	
	char *current_array = malloc(MAXLINELEN);

	while((c = getc(fp)) != EOF)
	    	if(c != '\n' && c != EOF) {
			current_array[*line_length] = c;
			++(*line_length);
		}
		else {
			break;
		}
	
	return current_array;
}
