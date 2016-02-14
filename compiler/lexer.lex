%option noyywrap
%{
#include <stdio.h>
#include "symboltable.h"

int linenumber=0;
int tokens=0;
int comments=0;

%}


letter [A-Za-z]
digit [0-9]
elphanum ({letter}|{digit})
ID {letter}({letter}|{digit}|"_")*
COMMENTS [/][*]([^*]|(\*+([^*/]|[\r\n\t])))*[*]+[/]
%%

{COMMENTS}    {comments++; tokens++; insert_comment(yytext); }
{ID}    { tokens++; insert_id(yytext); }

%%

int main(int argc, char **argv)
{
    argc--; ++argv;
    init_symtab();	/* Initialize Symbol/Comment tables */
    init_comtab();
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;
    yylex();
    printf("number of tokens %d\n",tokens);
    printf("number of lines %d\n",linenumber);
    printf("There are %d comments:\n",comments);
    print_symtab();
    print_comtab();	/* Print Comments and Symbols */
    cleanup_comtab();	/* Clean up tables */
    cleanup_symtab();
    return 0;
}
