/* Here we have functions to generate all initially connected automata
*/

#include <stdio.h>
#include "automata.h"
#include "extern.h"

int print_flag();

int next_flag(){

    int last = -1;
    int i,j;

    for(i = 1; i < STATES; i++){
        if( (flag[i] - last) > 1 ) break;
	last++;
    }

    if( i == STATES ){
        return 0;
    } else {
        last = --flag[i];
	last--;
	//reset first flags
	for(j = i - 1; j > 0; j--){
	    flag[j] = ( (j*LETTERS - 1) > last)?last:(j*LETTERS - 1);
	    last--;
	}
    }
//print_flag();
    return 1;

}



int init_flag(){
    
    int i;
    for(i = 1; i < STATES; i++){
        flag[i] = i*LETTERS - 1;
    }

    return 0;

}

int init_aut(){
    int i,j;

    for(j = 0; j < RECT; j++) str_aut[j] = 0;

    for(i = 1; i < STATES; i++){
        str_aut[ flag[i] ] = i;
    }
    
    return 0;

}


int follow_aut(){

    int i, j;

    for(i = 1; i < STATES - 1; i++){
        
	for(j = flag[i] + 1; j < flag[i + 1]; j++){

	    if(str_aut[j] < i){

	        str_aut[j]++;
		
		j--;

		while(j > flag[i]){
		    str_aut[j] = 0;
		    j--;
		}

		i--;

		while( i > 0){

		   for(j = flag[i] + 1; j < flag[i + 1]; j++){
		       str_aut[j] = 0;
		   }

		   i--;

		}

		return 1;
	    }

	}
    }

    for(i = flag[STATES - 1] + 1; i < RECT; i++){

        if( str_aut[i] < STATES - 1){

	    str_aut[i]++;

	    i--;

	    while(i > flag[STATES - 1]){
	        str_aut[i] = 0;
		i--;
	    }

	    for(i = 0; i < flag[STATES - 1]; i++){
	        str_aut[i] = 0;
	    }

	    for(i = 1; i < STATES; i++){
	        str_aut[ flag[i] ] = i;
	    }

	    return 1;
	}
    }

    return 0;
}



int next_aut(){

    if( follow_aut() ){
        return 1;
    } else {

        if( next_flag() ){
	    init_aut();
	    return 1;
	}
    }
    
    return 0;
}



int print_flag(){
    int i,j;

    for(i = 0; i < RECT; i++){

        for(j = 1; j < STATES; j++){
	    if( flag[j] == i) break;
	}

	if(j < STATES) printf("1 ");
	else printf("0 ");
    }

    printf("\n");

    return 0;
}

int print_str_aut(){
    int i,j;

    for( i = 0; i < STATES; i++){
        
	for(j = 0; j < LETTERS; j++){
	    printf("%d ", str_aut[i*LETTERS + j]);
	}

	printf(" ");
    }

    printf("\n");
    
    return 0;
}
