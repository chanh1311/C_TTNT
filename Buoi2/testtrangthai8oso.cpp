#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <set>
#include <stack>
#include <queue>
#include <fstream>


using namespace std;

const int BOARD_ROWS = 3;
const int BOARD_COLS = 3;
const int EMPTY_TILE = 0;
const int MAX_OP = 4;			// so luong cac hanh dong trong bai toan nay

// Hang chuoi de in ra ten cac hanh dong
const char* action[] = {"Trang thai bat dau", 
						"TRAI",
						"PHAI",
						"LEN",
						"XUONG"};

//-------------------Dinh nghia trang thai cua bai toan------------------------------//
struct State {
	int num[BOARD_ROWS][BOARD_COLS];
	int empty_row;		// Luu chi muc dong cua o trong
	int empty_col;		// Luu chi muc cot cua o trong
};

void print_state(State s) {
	for(int row = 0; row < BOARD_ROWS; row++) {
		for(int col = 0; col < BOARD_COLS; col++) {
			if(s.num[row][col] == 0)
				printf("_   ");
			else
				printf("%d   ", s.num[row][col]);	
		}
		printf("\n");
	}	
}

//So sanh hai trang thai co bang nhau khong
bool compareStates(State s1, State s2){
	// Kiem tra o trong cua 2 trang thai
	if(s1.empty_row != s2.empty_row || s1.empty_col != s2.empty_col)
		return false;
	
	// Kiem tra tung vi tri cua 2 trang thai s1 va s2
	for(int row = 0; row < BOARD_ROWS; row++) {
		for(int col = 0; col < BOARD_COLS; col++) {
			if(s1.num[row][col] != s2.num[row][col]) {
				return false;	
			}	
		}
	}
	return true;
}




//----------------------Doc du lieu tu file--------------------------//

State* read_file(string file) {
	//ifstream fin(file);
	ifstream fin(file.c_str());
	
	State *s = new State();
	for(int row = 0; row < BOARD_ROWS; row++) {
		for(int col = 0; col < BOARD_COLS; col++) {
			fin >> s->num[row][col];	
		}
	}
	fin >> s->empty_row >> s->empty_col;
	return s;
}
//----------------------------------Cac hanh dong-----------------------------//
bool up(State current_state, State &new_state) {
	
	//print_state(current_state);
	
	int empty_row = current_state.empty_row;
	int empty_col = current_state.empty_col;
	//printf("empty_row: %d", empty_row);
	printf("%d",empty_row);
	printf("%d",empty_col);
	if(empty_row > 0) {
		
		new_state = current_state;
		//print_state(new_state);
		
		new_state.empty_col = empty_col;
		new_state.empty_row = empty_row - 1;
		
		new_state.num[empty_row][empty_col] = current_state.num[empty_row - 1][empty_col];
		new_state.num[empty_row - 1][empty_col] = EMPTY_TILE;
		
		return true;
	}
	
	//print_state(new_state);
	
	return false;
}

/**
 * Dinh nghia hanh dong DOWN: di chuyen o trong di xuong
 */
bool down(State current_state, State &new_state) {
    //print_state(current_state);
	
	int empty_row = current_state.empty_row;
	int empty_col = current_state.empty_col;
	printf("%d",empty_row);
	printf("%d",empty_col);
	// 
	if (empty_row < BOARD_ROWS - 1){
		
		new_state = current_state;
		
		new_state.empty_col = empty_col;
		new_state.empty_row = empty_row + 1;
		
		new_state.num[empty_row][empty_col] = current_state.num[empty_row + 1][empty_col];
		new_state.num[empty_row + 1][empty_col] = EMPTY_TILE;
		
		return true;
	}	
    return false;
}


/**
 * Dinh nghia hanh dong LEFT: di chuyen o trong sang trai
 */
bool left(State current_state, State &new_state) {
	
    int empty_row = current_state.empty_row;
	int empty_col = current_state.empty_col;
	
	printf("%d",empty_row);
	printf("%d",empty_col);
	if (empty_col > 0){
		
		new_state = current_state;
		
		new_state.empty_row = empty_row;
		new_state.empty_col = empty_col - 1;
		
		new_state.num[empty_row][empty_col] = current_state.num[empty_row][empty_col - 1];		// o trong //
		new_state.num[empty_row][empty_col - 1] = EMPTY_TILE;									// o thay doi //
		
		return true;
	}	
	
	
    return false;
}


/**
 * Dinh nghia hanh dong UP: di chuyen o trong sang phai
 */
bool right(State current_state, State &new_state) {
	
    int empty_row = current_state.empty_row;
	int empty_col = current_state.empty_col;
	
	printf("%d",empty_row);
	printf("%d",empty_col);
	if (empty_col < BOARD_COLS - 1){
		
		new_state = current_state;
		
		new_state.empty_row = empty_row;
		new_state.empty_col = empty_col + 1;
		
		new_state.num[empty_row][empty_col] = current_state.num[empty_row][empty_col + 1];		// o trong //
		new_state.num[empty_row][empty_col + 1] = EMPTY_TILE;									// o thay doi //
		
		return true;
	}	
	
    
    return false;
}
// Ham goi cac hanh dong chuyen trang thai//
bool call(State s, State& out, int option) {
    switch (option) {
        case 1:
            return left(s, out);
        case 2:
            return right(s, out);
        case 3:
            return up(s, out);
        case 4:
            return down(s, out);
        default:
            return false;
    }
}
int main(){
	State *start_state;
	State result_state;
	// Khai bao trang thai bat dau.
	// Trang thai bat dau duoc cau hinh trong file test.txt
	start_state = read_file("start_easy.txt");
	printf("Trang thai bat dau: \n");
	print_state(*start_state);
	
	for(int i = 1; i <= 4; i++){
		bool thuchien = call(*start_state, result_state,i);
		if(thuchien){
			printf("\n");	
			print_state(result_state);
		}
		
	}
}
