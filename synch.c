/*
Here are functions to check whether an automaton is synchronizing or not,
compute shortest synchronizing word
*/

#include <stdlib.h>
#include <stdio.h>
#include "automata.h"
#include "extern.h"


int is_synch(int **aut, unsigned char states, unsigned char letters){
	unsigned char i,j,k,l;
	unsigned int cur_pos = 0;
	unsigned char st1, st2, tmp;
	unsigned char flag;
	unsigned int length = (states*(states - 1)*letters)/2;

	int *pairs;

	pairs = (int *) malloc(length*sizeof(unsigned int));

	for(i = 0; i < states - 1; i++){
		for(j = i + 1; j < states; j++){
			for(k = 0; k < letters; k++){

				st1 = aut[i][k];
				st2 = aut[j][k];

				if(st1 == st2){
					
					for(l = 1; l <= k; l++){
						pairs[cur_pos - l] = -1;
					}

					for(l = k; l < letters; l++){
						pairs[cur_pos] = -1;
						cur_pos++;
					}

					k = letters;

				}
				else{

					if(st1 > st2){
						tmp = st1;
						st1 = st2;
						st2 = tmp;
					}
					
					pairs[cur_pos] = (st1*(states - 1) + st2 - 1 - (st1*(st1 + 1))/2)*letters;
					cur_pos++;
				}

			}
		}
	}

	
	//new arrray filled
	flag = 1;

	while(flag){
		
		flag = 0;
		for(i = 0; i < length; i+= letters){

			if( pairs[i] >= 0 ){

				for(j = 0; j < letters; j++){
					if(pairs[ pairs[i + j] ] < 0) break;
				}

				if(j < letters){

					for(k = 0; k < letters; k++){
						pairs[i + k] = -1;
					}
					flag = 1;

				}
			}
		}
	}


	for(i = 0; i < length; i+=letters){
		if(pairs[i] >= 0) {
			return 0;
		}
	}

	free(pairs);

	return 1;

}

int min_synch_word(){

	int que_beg, que_end;
	int i;
	int *st;
	int bin, sum, let;


	for(i = 0; i < POW; i++){
	    path[i] = -1;
	}
	path[POW - 1] = 0;

	que_beg = 0; que_end = STATES + 1;
	for(i = 0; i < STATES; i++) queue[i] = 1; 
	queue[STATES] = 0;



	while(1){//i'm risky, pal
	    
	    //dequeue
	    st = &queue[que_beg];

	    
	    for(let = 0; let < LETTERS; let++){
	        
		for(i = 0; i < STATES; i++) tmp[i] = 0;

		for(i = 0; i < STATES; i++){
		    if( st[i] == 1) tmp[ aut[i][let] ] = 1;
		}

		bin = 0;
		sum = 0;

		for(i = 0; i < STATES; i++){
		    bin = bin*2 + tmp[i];
		    sum += tmp[i];
		}
		
		if( path[bin] == -1){//enqueue
		    path[bin] = st[STATES] + 1;

		    if(sum == 1){
			return path[bin];
		    }

		    for(i = 0; i < STATES; i++) queue[que_end + i] = tmp[i];
		    queue[que_end + STATES] = path[bin];
		    que_end = que_end + STATES + 1;
		}


	    }

	    que_beg += STATES + 1;

	}

	return 0;
}


int is_euler(){
	int i;
	int degree[STATES];

	for(i = 0; i < STATES; i++){
		degree[i] = 0;
	}

	for(i = 0; i < RECT; i++){
		degree[str_aut[i]]++;
	}

	for(i = 0; i < STATES; i++){
		if( degree[i] != LETTERS ) return 0;
	}

	return 1;
}