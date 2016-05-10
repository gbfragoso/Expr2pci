#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ada2asa.h"
#include "pcode.h"
#include "rpn2pci.h"
#include "btree2rpn.h"
#include "pushdown.h"

typedef char * string;

/*
	This program aim to convert a expression into pcode instructions. The convert process is compound of 5 steps
	Expr -> Pushdown Automata -> Productions -> Btree -> RPN -> PCI. 
	
	Author: Gustavo B. Fragoso
*/
int main (int argc, char **argv){
	
	// Vector with only integers, used as a datastore
	int stack[50] = {-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10};
    int productions[50], i;	    							// Result of Pushdown Automata
    char btree[50] = {""};									// Binary Tree
    string rpn;               								// Reverse Polish Notation
    
    FILE *input;
    
    for (i = 0;i<50;i++){
        btree[i] = '_';
        productions[i] = -1;
    }
    
    // Initial symbol
    btree[0] = 'E';
    
    if (argc == 2){
    	// Expr
    	string expr = argv[1];
    	int size = strlen(expr);

		if(strlen(expr)<50){
			FILE *output = fopen("output.txt", "w");
		    if(output!=NULL){
		    	fprintf(output,"Run: %s %s \n", argv[0], argv[1]);

				printf("Step 1. Catch arithmetic expression ... done!\n");
				
				// Execution of Pushdown Automata results in set of productions
				printf("Step 2. Running pushdown automata ... ");
				pushDownAutomata(expr,productions,output);
				printf("done!\n");
				
				// Apply productions to build ASA
				printf("Step 3. Apply productions to build an btree ... ");
				ada_to_asa(btree,productions);
				fprintf(output,"\nBtree: %s", btree);
				printf("done!\n");
                
			    // B-tree -> Reverse Polish Notation
                printf("Step 4. Running postorder trasversal on btree ... ");
                rpn = (string) malloc(50*sizeof(string));
			    postOrder(btree,size, 0, rpn);
			    fprintf(output,"\nReverse polish notation: %s\n", rpn);
			    printf("done!\n");	
				
			    // RPN -> PCI
			    printf("Step 5. Convert RPN into pcode instructions ... ");
				Tinstruction * instructions = toInstruction(rpn);
				printf("done!\n");
				
				// Array of instructions
				printf("Step 6. Running pcode machine ... ");
				fprintf(output,"\nOutput:\n");
				fprintf(output,"%-10s %-7s %-7s %-7s %-7s %-15s %s\n","Inst","Level","Arg","Top","Counter","Base","Stack");
				pcode(instructions, stack, output);
				printf("done!\n");
				
				free(rpn);
			    // Closing File
		    	fclose(output);
		    	
		    	printf("Output file generated.\n");	
		    }else{
		    	printf("\nError when opening the output file.");
		    }
	    }else{
	    	printf("\nToo long expression");
	    }
    }else{
    	printf("Insufficient params, running like this %s \"expr\"\n", argv[0]);
    }
    
    return 0;
}
