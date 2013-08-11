#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automata.h"
#include "synch.h"
#include "generator.h"
#include "converter.h"

//current automata
int **aut;
int flag[STATES];
int str_aut[STATES*LETTERS];
//used by synch.c
int pairs[ (STATES*(STATES - 1)*LETTERS)/2 ];
int queue[POW*(STATES + 1)];
int tmp[STATES];
int path[POW];
int sw_length[MAX + 1];

int is_sc();
int has_rank(int);

int main(){

	int i;
	unsigned long long count_synch = 0, count = 0;

    aut = (int **) malloc(STATES*sizeof(int *));

    for(i = 0; i < STATES; i++){
        aut[i] = (int *) malloc(LETTERS*sizeof(int));
    }

	for(i = 0; i <= MAX; i++){
        sw_length[i] = 0;
    }


	/*
	aut[0][0] = 1;
	aut[1][0] = 2;
	aut[2][0] = 3;
	aut[3][0] = 4;
	aut[4][0] = 5;
	aut[5][0] = 0;

	aut[0][1] = 1;
	aut[1][1] = 1;
	aut[2][1] = 2;
	aut[3][1] = 3;
	aut[4][1] = 4;
	aut[5][1] = 5;

*/

	//initialization for automata generation
    init_flag();
    init_aut();


	do {
		convert();
	
			if( is_synch(aut, STATES, LETTERS) ){
				count_synch++;
				sw_length[min_synch_word()]++;


				/*if( min_synch_word() == 35){

						/*for(i = 0; i < STATES; i++){
							printf("%d %d \n", aut[i][0], aut[i][1]);
						}
				}*/
			}
		
		count++;

    } while( next_aut() );

	printf("Synch: %d\n", count_synch);
	printf("Total: %llu\n", count);

	for( i = MAX; i >= 1; i--){ 
		if(sw_length[i] != 0 ){
			printf("Upper bound: %d\n", i);
			break;
		}
	}

	for(i = 1; i <= MAX; i++){
        printf("%d  ", sw_length[i]);
    }
	printf("\n");

  
    for(i = 0; i < STATES; i++){
        free(aut[i]);
    }
    
    free(aut);

	
	//system("pause");
    return 0;

}

int has_rank(int rank){
	int i,j;

	int mask[STATES];
	
	
	j = 0; 
    for(j = 0; j < LETTERS; j++){
		
		for(i = 0; i < STATES; i++){
			mask[i] = 0;
		}

		for(i = 0; i < STATES; i++){
			mask[aut[i][j]] = 1;
		}

		for(i = 1; i < STATES; i++){
			mask[0] += mask[i];
		}

		if(mask[0] != rank) return 0;
	}

	return 1;
}