void applyProduction(char *array, int production, int node){
    switch(production){
        case 0:
            array[node] = '1';
        break;
        case 1:
            array[node] = '2';
        break;
        case 2:
            array[node] = 'x';
        break;
        case 3:
            array[node] = 'y';
        break;
        case 4:
            array[node] = 'A';
            array[2*node+1] = 'E';
            array[2*node+2] = 'E';
        break;
        case 5:
            array[node] = '+';
        break;
        case 6:
            array[node] = '-';
        break;
        case 7:
            array[node] = '*';
        break;
        case 8:
            array[node] = '/';
        break;
    }
}

int getFather(int node){
    int father = 0;
    if ((node-1)%2 == 0){
        father = (node-1)/2;
    }else{
        father = (node-2)/2;
    }
    return father;
}

void ada_to_asa(char *array, int productions[]){
    int next = 0, i, j = 0, max = 0;
    
    for(i=0; productions[j] != -1 ; i++){
        switch(array[next]){
            case 'E':
                //The leftmost node will receive production
                applyProduction(array,productions[j++],next);
                if(array[2*next+1] == 'E'){
                    next = 2*next+1;
                }else if(array[2*next+2] == 'E'){
                    next = 2*next+2;
                }else{
                    next = getFather(next);
                }
            break;
            case 'A':
                applyProduction(array,productions[j++],next);
                if(array[2*next+1] == 'E'){
                    next = 2*next+1;
                }else if(array[2*next+2] == 'E'){
                    next = 2*next+2;
                }else{
                    next = getFather(next);
                }
            break;
            default:
                next = getFather(next);
        }
        if(next > max){
            max = next; // Catch last node position in array
        }
    }
    array[max + 1] = '\0';
}