/*  MSSV: b1809107
	HoTen : Nguyen Van Chanh
	STT: 19
*/

#include <stdio.h>
#include <stdlib.h>

#define VANG 1
#define NAU 2
#define EMPTY 0
#define MAXLENGTH 100

typedef struct{
	int da[7];
	int empty_rock;
}State;

// ech vang nhay 1 buoc  den phien da trong //
int echVangNhay1Buoc(State cur_state, State *result){
	if(cur_state.empty_rock > 0 && cur_state.da[cur_state.empty_rock-1] == VANG){
		*result = cur_state;
		
		result->empty_rock = cur_state.empty_rock - 1;
		result->da[result->empty_rock] = EMPTY;
		result->da[cur_state.empty_rock] = VANG;
		return 1;
	}
	return 0;
}

// Ech vang nhay 2 buoc (qua dau ech nau) den phien da trong //
int echVangNhay2Buoc(State cur_state,State *result){
	if(cur_state.empty_rock > 1 && cur_state.da[cur_state.empty_rock - 2] == VANG && cur_state.da[cur_state.empty_rock-1] == NAU)
	{
		*result = cur_state;
		result->empty_rock = cur_state.empty_rock - 2;
		result->da[result->empty_rock] = EMPTY;
		result->da[cur_state.empty_rock] = VANG;
		return 1;
	}
	return 0;
}
// Ech nau nhay 1 buoc den phien da trong //
int echNauNhay1Buoc(State cur_state, State *result){
	if(cur_state.empty_rock <  6 && cur_state.da[cur_state.empty_rock + 1] == NAU){
		*result = cur_state;
		
		result->empty_rock = cur_state.empty_rock + 1;
		result->da[result->empty_rock] = EMPTY;
		result->da[cur_state.empty_rock] = NAU;
		
		return 1;
	}
	return 0;
}
// Ech Nau nhay 2 buoc(qua dau ech vang) //
int echNauNhay2Buoc(State cur_state,State *result){
	if(cur_state.empty_rock < 5 && cur_state.da[cur_state.empty_rock + 2] == NAU && cur_state.da[cur_state.empty_rock+1] == VANG)
	{
		*result = cur_state;
		
		result->empty_rock = cur_state.empty_rock + 2;
		result->da[result->empty_rock] = EMPTY;
		result->da[cur_state.empty_rock] = NAU;
		
		return 1;
	}
	return 0;
}
// goi cac phep toan //
int callOperator(State cur_state, State *result, int option){
	switch(option){
		case 1: return echVangNhay1Buoc(cur_state,result);
		case 2: return echVangNhay2Buoc(cur_state,result);
		case 3: return echNauNhay1Buoc(cur_state,result);
		case 4: return echNauNhay2Buoc(cur_state,result);
		default: printf("Errors calls Operators");
		
		return 1;
	}
}
// Khoi tao trang thai  //
void init_State(State *result){
	result->da[0] = 1;
	result->da[1] = 1;
	result->da[2] = 1;
	result->da[3] = 0;
	result->da[4] = 2;
	result->da[5] = 2;
	result->da[6] = 2;
	
	result->empty_rock = 3;
	
}
// Hien thi trang thai //
void print_State(State state){
	printf("\n %d--%d--%d--%d--%d--%d--%d",state.da[0],state.da[1],state.da[2],state.da[3],state.da[4],state.da[5],state.da[6]);
}
// cau truc 1 Node //
typedef struct Node{
	State state;
	struct Node* parent;
	int no_function;
}Node;

const char* action[] = {"Trang thai dau", "Ech vang nhay 1 buoc den phien da trong","Ech vang nhay 2 buoc den phien da trong","Ech nau nhay 1 buoc den phien da trong","Ech nau nhay 2 buoc den phien da trong"};


// ham chinh //
int main(){
	State cur_state,result;
	init_State(&cur_state);
	
	printf("------------Trang thai bat dau:------------");
	print_State(cur_state);
	
	printf("\n-----------Trang thai con:---------------");
	int opt;
	for(opt=1; opt < 5; opt++){
		int thuchien = callOperator(cur_state,&result,opt);
		if(thuchien == 1){
			printf("\nHanh dong %s thanh cong",action[opt]);
			print_State(result);
		}else{
			printf("\nHanh dong %s thuc hien khong thanh cong!",action[opt]);
		}
	}
	
	return 1;
}

