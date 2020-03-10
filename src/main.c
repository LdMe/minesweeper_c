#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "clear.h"
void my_putstr(char*);
void my_putchar(char);
void initialize(char **board, unsigned int size);
unsigned int count_neighbors(char **board, unsigned int size, unsigned int x_pos, unsigned int y_pos);
char **get_neighbors(char **board, unsigned int size, unsigned int x_pos, unsigned int y_pos);
char **get_neighbors_positions(char **board, unsigned int size, unsigned int x_pos, unsigned int y_pos, int **arr);



char **init_board(unsigned int n) {
	char **board;

	board= malloc(sizeof(char*)* n);
	for (int i = 0; i < n; i++)
	{
		board[i]=malloc(sizeof(char)*n);
		for (int j = 0; j < n; j++)
		{
			board[i][j]='?';
		}
	}
	return board;
}
void print_x_index(unsigned int num) {
	for (int i = 0; i < num; i++)
	{
		my_putstr("| ");
		my_putchar('A'+i);
		my_putchar(' ');
	}
	my_putstr("| # |");
}
void print_lines(unsigned int num){

	for (int i = 0; i < num + 1; i++)
	{
		my_putstr("====");
	}
}
void print_board(char **board,int size){

	print_lines(size);
	my_putchar('\n');
	print_x_index(size);
	my_putchar('\n');	
	for( int i = 0; i < size; i++) {

		print_lines(size);
		my_putchar('\n');
		for (int j = 0; j < size; j++)
		{
			my_putstr("| ");
			my_putchar(board[i][j]);
			my_putstr(" ");
		}
		my_putchar('|');
		my_putchar(' ');
		my_putchar('0'+i);
		my_putstr(" |");
		my_putchar('\n');
	}
	print_lines(size);
	my_putchar('\n');
}
void set_mines(char **board,unsigned int num_mines, unsigned int size) {
	int mines_left= num_mines;
	while(mines_left > 0){
		unsigned int x_pos= rand() % size;
		unsigned int y_pos= rand() % size;
		if(board[y_pos][x_pos] != '0'){
			board[y_pos][x_pos] = '0';
			mines_left--;
		}
	}

}
void initialize(char **board, unsigned int size){
	for( int i= 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if(board[i][j] != '0') {
				unsigned int mines = count_neighbors(board,size,j,i);
				
				if(mines == 0) {
					board[i][j]= ' ';
				}
				else{
					board[i][j]= '0' + mines;
				}

			}

		}
	}
}
void show_neighbors(char **board,char **show_board, unsigned int size, unsigned int x_pos, unsigned int y_pos) {
	if(show_board[y_pos][x_pos]!= '?'){
		return;
	}
	if(board[y_pos][x_pos]!= ' ' ) {
		show_board[y_pos][x_pos]=board[y_pos][x_pos];
		return;
	}
	int **positions=malloc(sizeof(int*) * 8);
	for (int i = 0; i < 8; i++)
	{
		positions[i]= malloc(sizeof(int) * 2);
		positions[i][0]=-1;
		positions[i][1]=-1;
	}
	char ** neighbors = get_neighbors_positions(board,size, x_pos, y_pos,positions);
	char ** neighbors_show = get_neighbors(show_board,size, x_pos, y_pos);

	show_board[y_pos][x_pos]=' ';
	for (int i = 0; i < 8; i++)
	{
		if(neighbors[i]==NULL ) {
			continue;
		}
		
		if(positions[i][0] == -1 || positions[i][1] == -1){
			continue;
		}
		if(*neighbors[i]==' ' ) {
			
			printf("positions y:%d\n",positions[i][0] );
			printf("positions x:%d\n",positions[i][1] );

			show_neighbors(board,show_board,size,positions[i][1],positions[i][0]);

		}
		
	}
	free(neighbors);
	free(neighbors_show);
	for (int i = 0; i < 8; i++)
	{
		free(positions[i]);
	}
	free(positions); 
}
unsigned int count_neighbors(char **board, unsigned int size, unsigned int x_pos, unsigned int y_pos) {

	char **neighbors = get_neighbors(board, size, x_pos, y_pos);
	unsigned int counter = 0;
	for (int i = 0; i < 8; i++)
	{
		if(neighbors[i] == NULL){
			continue;
		}
		if( *neighbors[i] == '0') {
			counter++;
		}

	}
	free(neighbors);
	return counter;
}
char **get_neighbors(char **board, unsigned int size, unsigned int x_pos, unsigned int y_pos ) {
	int **positions=malloc(sizeof(int*) * 8);
	for (int i = 0; i < 8; i++)
	{
		positions[i]= malloc(sizeof(int) * 2);
	}
	char **tab= get_neighbors_positions(board,  size, x_pos,  y_pos,positions);
	for (int i = 0; i < 8; i++)
	{
		free(positions[i]);
	}
	free(positions); 
	return tab;
}
char **get_neighbors_positions(char **board, unsigned int size, unsigned int x_pos, unsigned int y_pos, int **positions) {
	
	char **neighbors =malloc(sizeof(char*) * 8);
	

	for (int i = 0; i < 8; i++)
	{
		neighbors[i]=NULL;
	}
	int pos= 0;
	int **arr = positions;
	if(x_pos > 0) {
		neighbors[pos] = board[y_pos]+x_pos - 1;
		arr[pos][0]=y_pos;
		arr[pos][1]=x_pos - 1;
		pos++;
		if(y_pos > 0) {
			neighbors[pos] = board[y_pos - 1]+x_pos - 1;
			arr[pos][0]=y_pos - 1;
			arr[pos][1]=x_pos - 1;
			pos++;
		}
		if(y_pos < size - 1) {
			neighbors[pos] = board[y_pos + 1]+x_pos - 1 ;
			arr[pos][0]=y_pos + 1;
			arr[pos][1]=x_pos - 1;
			pos++;
		}
	}
	if(x_pos < size - 1) {
		neighbors[pos] = board[y_pos]+x_pos + 1;
		arr[pos][0]=y_pos;
		arr[pos][1]=x_pos + 1;
		pos++;
		if(y_pos > 0) {
			neighbors[pos] = board[y_pos - 1]+x_pos + 1;
			arr[pos][0]=y_pos - 1;
			arr[pos][1]=x_pos + 1;
			pos++;
		}
		if(y_pos < size - 1) {
			neighbors[pos] = board[y_pos + 1]+x_pos + 1 ;
			arr[pos][0]=y_pos + 1;
			arr[pos][1]=x_pos + 1;
			pos++;
		}
	}
	if(y_pos > 0) {
		neighbors[pos] = board[y_pos - 1]+x_pos;
		arr[pos][0]=y_pos - 1;
		arr[pos][1]=x_pos;
		pos++;
	}
	if(y_pos < size - 1) {
		neighbors[pos] = board[y_pos + 1]+x_pos ;
		arr[pos][0]=y_pos + 1;
		arr[pos][1]=x_pos ;
		pos++;
	}
	return neighbors;
}
int main(int argc, char const *argv[])
{
	//clear();
	srand(time(NULL)); 
	unsigned int size= 10;
	unsigned int mines = 10;
	char **board= init_board(size);
	char **board2= init_board(size);
	set_mines(board,mines,size);

	initialize(board,size);
	print_board(board2,size);
	show_neighbors(board,board2,size,0,0);
	print_board(board2,size);
	print_board(board,size);
	return 0;
}