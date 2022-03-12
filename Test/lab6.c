
#include<stdio.h>
#include<stdlib.h>

// Khai bao cac hang can thiet cho bai toan //
#define tankcapacity_X 9
#define tankcapacity_Y 4
#define empty 0
#define Maxlength 100
#define goal 6
#define z 10
const char* action[] = {"First","Pour Full X","Pour Full Y","Pour Empty X","Pour Empty Y","Pour X to Y", "Pour Y to X"};

// ___________________Cau truc trang thai_____________________ //

//khai bao cau truc trang thai//
typedef struct {
	int x;	//luong nuoc trong binh x//
	int y;
			//luong nuoc trong binh y//
}State;

//Bieu dien trang thai bat dau//
void makeNullState(State *state){
	state->x = 0;
	state->y = 0;
}
//Hien thi trang thai//
void print_State(State state){
	printf("\n  X: %d --- Y: %d\n",state.x,state.y);
}
//Trang thai muc tieu//
int goalCheck(State state){
	return (state.x == 6 || state.y == 6);
}





/******************Cai dat cac hanh dong cua trang thai********************/
// lam day binh X //
int pourWaterFullX(State cur_state, State *result){
	if(cur_state.x < tankcapacity_X){
		result->x = tankcapacity_X;
		result->y = cur_state.y ;
		return 1;
	}
	return 0;
}
//Lam day binh Y//
int pourWaterFullY(State cur_state,State *result){
	if(cur_state.y < tankcapacity_Y){
		result->x = cur_state.x;
		result->y = tankcapacity_Y;
		return 1;
	}
	return 0;
}
//Lam rong binh X//
int pourWaterEmptyX(State cur_state,State *result){
	if(cur_state.x > 0){
		result->x = 0;
		result->y = cur_state.y;
		return 1;
	}
	return 0;
}
//lam rong binh Y//
int pourWaterEmptyY(State cur_state,State *result){
	if(cur_state.y > 0){
		result->x = cur_state.x;
		result->y = 0;
		return 1;
	}
	return 0;	
}
// max //
int max(int a, int b){
	if(a > b) return a;
	return b;	
}
// min //
int min(int a, int b){
	if (a < b) return a;
	return b;
}
// Rot x sang y //
int pourWaterXY(State cur_state,State *result){
	if(cur_state.x > 0 && cur_state.y < tankcapacity_Y){
		result->x = max(cur_state.x - (tankcapacity_Y - cur_state.y),empty);
		result->y = min(cur_state.x + cur_state.y,tankcapacity_Y);
		return 1;
	}
	return 0;
}
// Rot y sang x //
int pourWaterYX(State cur_state, State *result){
	if(cur_state.y > 0 && cur_state.x < tankcapacity_X){
		result->x = min(cur_state.x + cur_state.y,tankcapacity_X);
		result->y = max(cur_state.y - (tankcapacity_X - cur_state.x),empty);
		return 1;	
	}
	return 0;
}
// Xay dung ham de goi cac hanh dong//
int call_Operator(State cur_state,State *result,int option){
	switch(option){
		case 1: return pourWaterFullX(cur_state,result);
		case 2: return pourWaterFullY(cur_state,result);
		case 3: return pourWaterEmptyX(cur_state,result);
		case 4: return pourWaterEmptyY(cur_state,result);
		case 5: return pourWaterXY(cur_state,result);
		case 6: return pourWaterYX(cur_state,result);
		default:
			printf("Error calls Operator");
			return 0;	
	}
}
// ___________________Cau truc Node_____________________ //
typedef struct Node{
	State state;
	struct Node* Parent; // Bien Parent là bien con tro luu dia chi //
	int no_function;
}Node;

//____________________Cai Dat Hang Doi______________________//

