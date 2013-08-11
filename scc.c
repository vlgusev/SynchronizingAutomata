/*
Functions to check whether a digraph is strongly connected or not

Code completely copy pasted from cormen leiserson rivest.

Afterwards I noticed trivial simplification, so, it is just dfs from 0 vertex in transposed graph
*/

#include <stdio.h>
#include "automata.h"
#include "extern.h"

#define WHITE 0
#define GREY 1
#define BLACK 2

unsigned char d[STATES];
unsigned char f[STATES];
unsigned char color[STATES];
unsigned char time;
unsigned char aut_sc[STATES][STATES];

int dfs_visit(unsigned char);

int dfs(){
	unsigned char i;
	time = 0;
	for(i = 0; i < STATES; i++){
		color[i] = WHITE;
	}

	for(i = 0; i < STATES; i++){
		if(color[i] == WHITE) dfs_visit(i);
	}

	return 0;
}

int dfs_visit(unsigned char vertex){
	unsigned char j;
	color[vertex] = GREY;
	d[vertex] = time;
	time++;
	for(j = 0; j < STATES; j++){
		if(aut_sc[vertex][j] == 1 && color[j] == WHITE) dfs_visit(j);
	}
	color[vertex] = BLACK;
	f[vertex] = time;
	time++;
	return 0;
}

int is_sc(){
	unsigned char i, j, forefather;


	for(i = 0; i < STATES; i++){
		for(j = 0; j < STATES; j++){
			aut_sc[i][j] = 0;
		}
	}

	for(i = 0; i < STATES; i++){
		for(j = 0; j < LETTERS; j++){
			aut_sc[i][aut[i][j]] = 1;
		}
	}
	
	dfs();

	for(i = 0; i < STATES; i++){
		if(f[i] == STATES*2 - 1) break;
	}

	if(i == STATES) printf("Internal ERROR, is_sc function!!");


	forefather = i;

	time = 0;
	for(i = 0; i < STATES; i++){
		color[i] = WHITE;
	}

	for(i = 0; i < STATES; i++){
		for(j = 0; j < STATES; j++){
			aut_sc[i][j] = 0;
		}
	}

	for(i = 0; i < STATES; i++){
		for(j = 0; j < LETTERS; j++){
			aut_sc[aut[i][j]][i] = 1;
		}
	}

	dfs_visit(forefather);

/*	for(i = 0; i < STATES; i++){
		if(color[i] == WHITE) return 0;
	}

/*	for(i = 0; i < STATES; i++) printf("%d  ", color[i]);
	printf("\n");

	printf("%d\n", time);*/

	if(time == 2*STATES) {
		return 1;
	} else {
		return 0;
	}

}