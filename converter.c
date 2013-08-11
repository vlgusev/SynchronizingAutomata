#include "automata.h"
#include "extern.h"

int convert(){
    int i,j;

    for(i = 0; i < STATES; i++){

        for(j = 0; j < LETTERS; j++){
	    aut[i][j] = str_aut[i*LETTERS + j];
	}

    }

    return 0;
}
