%{
#include <stdio.h>    
	%}

%token SUM SUB MUL DIV PAB PCI NUMBER EOL

%%

inicio :
/* epsilon */
| inicio exp EOL { printf("= %i\n", $2); }

exp :
term SUM exp { $$ = $1 + $3; }
| term SUB exp { $$ = $1 - $3; }
| term         { $$ = $1; }
;

term :
term MUL fact { $$ = $1 * $3; }
| term DIV fact { $$ = $1 / $3; }
| fact          { $$ = $1; }
;

fact :
NUMBER       { $$ = $1; }
| SUB fact     { $$ = - $2; }
| PAB exp PCI  { $$ = $2; }
;    

%%

int main() {
    yyparse();
    return 0;    
}

int yyerror(char * mensaje) {
    fprintf(stderr, "%s\n", mensaje);
    return 0;
}
