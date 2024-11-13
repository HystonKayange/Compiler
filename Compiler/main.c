# include <stdio.h>
# include <stdlib.h>
# include "type.h"

extern int syntax_err;
extern A_NODE *root;

int main(void) {
    initialize();
    yyparse();
    
    if (syntax_err) {
        exit(EXIT_FAILURE);
    }

    print_ast(root);
    printf("\nGenerated code\n");
    code_generation(root);

    return EXIT_SUCCESS;
}


