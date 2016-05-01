#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
void btreeBuilder(string *btree, string expr,int productions[50]);
void printBtree(string *btree, int size);
char* produceName(int production);
void produce(string* btree, int production, int node);

int main (int argc, char **argv){
	
	int stack[1024] = {-1};		// Vector with only integers, used as a datastore
    int productions[50] = {-1};	// Result of Pushdown Automata
    string *btree = NULL;		// Dynamic allocated Binary Tree (Array of char*)
    
    FILE *input;
    
    if (argc == 2){
    	// Expr
    	string expr = argv[1];
    	int size = strlen(expr), i;
    	
    	btree = (string*) malloc(size*sizeof(string));

		if(strlen(expr)<50){
			FILE *output = fopen("output.txt", "w");
		    if(output!=NULL){
		    	fprintf(output,"Run: %s %s \n", argv[0], argv[1]);
				fprintf(output,"Input: %s \n", expr);
				
				// Execution of Pushdown Automata results in set of productions
				pushDownAutomata(expr,productions,output);
				
				// Btree initial state
				for(i = 0; i<size;i++){
					string token= "000";
					btree[i] = malloc(sizeof(token));
					strcpy(btree[i],"_");
				}
				strcpy(btree[0], "E");
				
				printf("List of productions to build the expr %s without '(' ')': \n", expr);
				for (i = 0; productions[i]!=-1;i++){
					if(productions[i] < 9){
						printf("%d ", productions[i]);
					}
				}
				printf("\nPlease apply productions to nodes. (Leftmost First)\n");
				
				int node = 0;
				printBtree(btree,size);
				for (i = 0; productions[i]!=-1;i++){
					if(productions[i] < 9){
						printf("Apply production %s in node: ", produceName(productions[i]));
						scanf("%d", &node);
						produce(btree,productions[i],node);
						printBtree(btree,size);
					}
				}
				
				printf("Done! Output file generated\n");
				
				string rpn = (string) malloc(100*sizeof(string));
			    // B-tree -> Reverse Polish Notation
			    postOrder(btree,size, 0, rpn);
			    	
			    fprintf(output,"\nReverse polish notation: %s\n", rpn);
		
			    // Array of instructions
				Tinstruction * instructions = toInstruction(rpn, size);
				fprintf(output,"\nOutput:\n");
				fprintf(output,"%-10s %-7s %-7s %-7s %-7s %-15s %s\n","Inst","Level","Arg","Top","Counter","Base","Stack");
				pcode(instructions, stack, output);
	
		    	// Free memory
				for(i = 0; i<size; i++){
			    	free(btree[i]);
			    }
			    free(btree);
			    free(rpn);
			    	
			    // Closing File
		    	fclose(output);
		    		
		    }else{
		    	printf("\nError when opening the output file.");
		    }
	    }else{
	    	printf("\nToo long expression");
	    }
    }else{
    	printf("\nInsuficient params");
    }
    
    return 0;
}

void printBtree(string *btree, int size){
	int j;
	for (j=0;j<size;j++){
		printf("%s ", btree[j]);
	}
	printf("\n");
}

char* produceName(int production){
	char *p = NULL;
	switch(production){
		case 0:
			p = "E -> 1";
		break;
		case 1:
			p = "E -> 2";
		break;
		case 2:
			p = "E -> x";
		break;
		case 3:
			p = "E -> y";
		break;
		case 4:
			p = "E -> EAE";
		break;
		case 5:
			p = "A -> +";
		break;
		case 6:
			p = "A -> -";
		break;
		case 7:
			p = "A -> *";
		break;
		case 8:
			p = "A -> /";
		break;
	}
	
	return p;
}

void produce(string* btree, int production, int node){
	switch(production){
		case 0:
			strcpy(btree[node], "1");
		break;
		case 1:
			strcpy(btree[node], "2");
		break;
		case 2:
			strcpy(btree[node], "x");
		break;
		case 3:
			strcpy(btree[node], "y");
		break;
		case 4:
			strcpy(btree[node], "A");
			strcpy(btree[2*node + 1], "E");
			strcpy(btree[2*node + 2], "E");
		break;
		case 5:
			strcpy(btree[node], "+");
		break;
		case 6:
			strcpy(btree[node], "-");
		break;
		case 7:
			strcpy(btree[node], "*");
		break;
		case 8:
			strcpy(btree[node], "/");
		break;
	}
}


