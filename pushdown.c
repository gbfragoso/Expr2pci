#include <stdio.h>
#include <string.h>

char stack[50] = {""};

char pop(){
    char rtn = stack[0];
    memmove(stack,stack+1,strlen(stack));
    return rtn;
}

void push(char* source, char *value){
    char *p = source;
    int len = strlen(value);
    memmove(p,p-len,strlen(source)+len);
    memcpy(p,value,len);
}

char* replace(char* str, char* a, char *b){
    int len  = strlen(str);
    int lena = strlen(a), lenb = strlen(b);
    char *p = str; 
    p = strstr(p, a);
    
    if(p){
        memmove(p+lenb, p+lena,len - (p - str) + lenb);
        memcpy(p, b, lenb);
    }
    
    return str;
}

int * pushDownAutomata(char word[50], int productions[50], FILE *output){
	int i = 0, j = 0, step=2 , size = strlen(word);
    
    fprintf(output,"\nPushdown Automata\n");
    fprintf(output,"%-5s %-30s %-15s %-2s\n","Step",".w","Stack","P");
    fprintf(output,"%-5d %-30s %-15s %-2s\n",0,word,stack,"-");
    
	// Initial symbol
	push(stack, "E");
	fprintf(output,"%-5d %-30s %-15s %-2s\n",1,word,stack,"-");
	
	while(i<size){
		
		switch(stack[0]){
			case 'E':
				if(word[i] == '1'){
					replace(stack,"E","1");
					productions[j++] = 0;
					fprintf(output,"%-5d %-30c %-15s %-2s\n",step,word[i],stack,"P0");
				}
				if(word[i] == '2'){
					replace(stack,"E","2");
					productions[j++] = 1;
					fprintf(output,"%-5d %-30c %-15s %-2s\n",step,word[i],stack,"P1");
				}
				if(word[i] == 'x'){
					replace(stack,"E","x");
					productions[j++] = 2;
					fprintf(output,"%-5d %-30c %-15s %-2s\n",step,word[i],stack,"P2");
				}
				if(word[i] == 'y'){
					replace(stack,"E","y");
					productions[j++] = 3;
					fprintf(output,"%-5d %-30c %-15s %-2s\n",step,word[i],stack,"P3");
				}
				if(word[i] == '('){
					replace(stack,"E","(EAEB");
					productions[j++] = 4;
					fprintf(output,"%-5d %-30c %-15s %-2s\n",step,word[i],stack,"P4");
				}
			case 'A':
				if(word[i] == '+'){
					replace(stack,"A","+");
					productions[j++] = 5;
					fprintf(output,"%-5d %-30c %-15s %-2s\n",step,word[i],stack,"P5");
				}
				if(word[i] == '-'){
					replace(stack,"A","-");
					productions[j++] = 6;
					fprintf(output,"%-5d %-30c %-15s %-2s\n",step,word[i],stack,"P6");
				}
				if(word[i] == '*'){
					replace(stack,"A","*");
					productions[j++] = 7;
					fprintf(output,"%-5d %-30c %-15s %-2s\n",step,word[i],stack,"P7");
				}
				if(word[i] == '/'){
					replace(stack,"A","/");
					productions[j++] = 8;
					fprintf(output,"%-5d %-30c %-15s %-2s\n",step,word[i],stack,"P8");
				}
				break;
			case 'B':
				replace(stack,"B",")");
				productions[j++] = 9;
				fprintf(output,"%-5d %-30c %-15s %-2s\n",step,word[i],stack,"P9");
				break;
			default:
				pop();
				i++;
				if(word[i] == word[size] && strlen(stack) == 0){
	                fprintf(output,"%-5d %-30s %-15s %-2s\n",step,"accept",stack,"-");
	            }else if(word[i] == word[size] && strlen(stack) > 0){
			        fprintf(output,"%-5d %-30s %-15s %-2s\n",step,"rejected",stack,"-");
	            }else{
	            	fprintf(output,"%-5d %-30c %-15s %-2s\n",step,word[i],stack,"-");
	            }
				break;
		}
		
		step++;
	}
	productions[j++] = -1;
	return productions;
}