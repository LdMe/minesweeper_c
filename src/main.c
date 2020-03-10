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
		my_putchar('A'+i);
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
		show_neighbors(board,show_board,size,positions[i][1],positions[i][0]);

		
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
int get_number(unsigned int *num,unsigned int size) {
	char num_str[3];
	scanf ("%[^\n]%*c", num_str);
	size--;
	char letter= num_str[0];
	if(letter=='q'){
		return 1;
	}
	if(letter=='s'){
		return 2;
	}
	if(letter >= 'a'  && letter <= 'a'+ size){
		num[0]= num_str[0] -'a';
	} 
	else if(letter >= 'A' && letter <= 'A'+ size) {
		num[0]= num_str[0] -'A';
	}
	else{
		return -1;
	}
	letter= num_str[1];
	if(letter >= 'a'  && letter <= 'a'+ size){
		num[1]= num_str[1] -'a';
	} 
	else if(letter >= 'A' && letter <= 'A' + size) {
		num[1]= num_str[1] -'A';
	}
	else{
		return -1;
	}
	return 0;

}
int game_ended(char **board, char **show_board,unsigned int size){
	int not_ended = 0;
	int lost = 0;
	for(int i =0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if(board[i][j]=='0'){
				if(show_board[i][j]!= '?'){
					lost = 1;
				}
			}
			if(show_board[i][j]== '?'){
				if(board[i][j]!='0'){
					not_ended=1 ;
				}
			}
		}
	}
	if(lost == 1){
		return -1;
	}
	if(not_ended ==1 ) {
		return 0;
	}
	return 1;
}
int play_round(char** board, char **show_board, unsigned int size){
	unsigned int num[2];
	my_putstr("Write two letters to reveal that square\n");
	int number= get_number(num,size);
	while(number == -1) {
		my_putstr("Write two letters to reveal that square\n");

		number= get_number(num,size);
		if(number != -1){
			break;
		}
	}
	if(number==1){
		return 2;
	}
	if(number==2){
		print_board(board,size);
		print_board(show_board,size);
		return 0;
	}
	my_putchar(num[0]+'0');
	my_putchar(num[1]+'0');
	my_putchar('\n');
	show_neighbors(board, show_board,size,num[0],num[1]);
	print_board(show_board,size);
	int ended= game_ended(board,show_board,size);
	return ended;

}

int main(int argc, char const *argv[])
{
	//clear();
	srand(time(NULL)); 
	unsigned int size= 10;
	unsigned int mines = 10;
	if(argc > 1) {
		size=atoi(argv[1]);
	}
	if(argc > 2) {
		mines=atoi(argv[2]);
	}
	char **board= init_board(size);
	char **board2= init_board(size);
	set_mines(board,mines,size);
	
	initialize(board,size);
	print_board(board2,size);
	int result= play_round(board,board2,size);
	while(result==0){
		result = play_round(board,board2,size) ;
	}
	if(result==1){
		my_putstr("Congratulations! You win!\n");
	}
	if(result==-1){
		my_putstr("Game over!\n");
	}
	return 0;
}