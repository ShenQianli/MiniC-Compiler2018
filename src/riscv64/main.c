#include <stdio.h>
#include "globals.h"
#include "mytree.h"
#include "riscv64.h"
#include "y.tab.h"
#include "optimize.h"


int lineno = 1;
TreeNode * root = NULL;

extern FILE * yyin;
extern FILE * yyout;
extern int yyparse();

int main(int argc, char** argv){
    if(argc >= 2){
        yyin = fopen(argv[1], "r");
        if(yyin == NULL){
			fprintf(stderr, "error : input file '%s' not found\n", argv[1]);
            exit(1);
        }
    }
	if(argc == 3){
		yyout = fopen(argv[2], "w");
		if(yyout == NULL){
			fprintf(stderr, "error : fail to open output file '%s'\n", argv[1]);
			exit(1);
		}
	}
    else if(argc > 3){
		fprintf(stderr, "usage: $ %s <input filename>? <output filename>?\n", argv[0]);
        exit(1);
    }
    yyparse();
	fprintf(stderr, "\n");
	TiggerTreeOptimize(root);
    GenRISCV64(root, yyout);
	
	if(yyin)
    	fclose(yyin);
	if(yyout)
		fclose(yyout);

    return 0;
}
