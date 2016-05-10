#include "btree2rpn.h"
#include <string.h>

char* postOrder(char* btree, int treeSize, int node, char* expr){
    if(node >= treeSize || btree[node]== "_"){
    	return NULL;
    }else{
    	postOrder(btree, treeSize, 2*node+1, expr);
    	postOrder(btree, treeSize, 2*node+2, expr);
    	char c[3] = {btree[node],' ','\0');
    	strcat(expr, c);
    }
}
