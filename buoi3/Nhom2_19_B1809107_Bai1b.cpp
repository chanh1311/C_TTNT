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
#define Maxlength 100

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
//Trang thai muc tieu//
int goalCheck(State state){
	return(state.empty_rock == 3 && state.da[0] == 2 && state.da[1] == 2 && state.da[2] == 2 && state.da[3] == 0 && state.da[4] == 1 && state.da[5] == 1 && state.da[6] == 1);
	
}
// cau truc 1 Node //
typedef struct Node{
	State state;
	struct Node* parent;
	int no_function;
}Node;

const char* action[] = {"Trang thai dau", "Ech vang nhay 1 buoc den phien da trong","Ech vang nhay 2 buoc den phien da trong","Ech nau nhay 1 buoc den phien da trong","Ech nau nhay 2 buoc den phien da trong"};
//________________________Cau truc Stack_______________________//
typedef struct{
	Node* Elements[Maxlength]; // array Elements là bien con tro luu dia chi //
	int Top_idx;
}Stack;
// Khoi tao Stack rong //
void makeNull_Stack(Stack *stack){
	stack->Top_idx = Maxlength;	
}
// Check Stack co rong hay khong //
int check_EmptyStack(Stack stack){
	return stack.Top_idx == Maxlength;
}
// Check Stack co day hay khong //

int full_Stack(Stack stack){
	return stack.Top_idx == 0;
	
}




// dua 1 nut vao dinh Stack //
void push(Node* x,Stack *stack){
	if(full_Stack(*stack))	// truyen vao gia tri duoc con tro tro toi //
		printf("Error! Stack is full");
	else{
		stack->Top_idx -= 1;
		stack->Elements[stack->Top_idx] = x; 
	}
		
}

// xoa 1 nut khoi dinh Stack //
void pop(Stack *stack){
	if(!check_EmptyStack(*stack))
		stack->Top_idx += 1;
	else 
		printf("Error! Stack is empty");
}
 // Tra ve phan tu(dia chi luu tru kieu con tro) tren dinh ngan xep //
Node* top(Stack stack){
	if(!check_EmptyStack(stack)){
		return stack.Elements[stack.Top_idx];
	}
	return NULL;	
}
// So sanh 2 trang thai //
int compareStates(State state1,State state2){
		int i;
		if(state1.empty_rock != state2.empty_rock) return 0;
		for(int i = 0; i <= 6 ; i++){
			if(state1.da[i] != state2.da[i]) return 0;
		}
	return 1;
}
// Tim trang thai trong Stack Open/Close //
int find_Stack(State state, Stack openStack){
	while(!check_EmptyStack(openStack)){					// kiem tra state co phai top cua Stack khong //
		if(compareStates(state,top(openStack)->state))
			return 1;
		pop(&openStack);
	}
	return 0;
							
}
Node* DFS_Algorithm(State state){
	// tao opened va closed //
	Stack opened;
	Stack closed;
	makeNull_Stack(&opened);
	makeNull_Stack(&closed);
	// tao node parent va gan gia tri //
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->parent = NULL;
	root->no_function = 0;
	// day parent vao opened //
	push(root,&opened);
	
	int tongtrangthai = 0;
	// Duyet tat ca phan tu trong opened //
	while(!check_EmptyStack(opened)){
		tongtrangthai++;
		// xet phan tu top trong opened //
		Node* node = top(opened);
		pop(&opened);
		push(node,&closed);
		
		
		
		// kiem tra no co phai trang thai muc tieu hay khong //
		if(goalCheck(node->state)){			// thoat //
			printf("************Tong trang thai da duyet la: %d",tongtrangthai);
			return node;		
		}
		// thuc hien cac phep toan tren nut nay de tao ra cac nut khac //
		int opt = 1;
		for( opt ; opt <= 4; opt++){
			State newstate;
			init_State(&newstate);
			if(callOperator(node->state,&newstate,opt)){
			// Neu trang thai da ton tai thi bo qua //
				if(find_Stack(newstate,opened) || find_Stack(newstate,closed))
					continue;
				// Tao nut moi va gan gia tri //
				Node* newnode = (Node*)malloc(sizeof(Node));
				newnode->parent = node;
				newnode->state = newstate;
				newnode->no_function = opt;
			 
			// Neu trang thai chua ton tai thi dua nut moi tao vao closed //
				push(newnode,&opened);
				
			}
		}
	}
	return NULL;
}
// Hien thi ket qua duyet theo chieu sau //

void print_WaysToGetGoal(Node* node){
	// Khoi tao Stack //
	Stack print_Stack;
	makeNull_Stack(&print_Stack);
	
	// do nguoc len tren //
	while(node->parent != NULL){
		push(node,&print_Stack);
		node = node->parent;
	}
	// them phan tu dau tien vao Stack //
	push(node,&print_Stack);
	
	// Hien thi lan luot cac hanh dong! //
	int act = 0;
	while(!check_EmptyStack(print_Stack)){
		printf("\n Action %d: %s ",act,action[top(print_Stack)->no_function]);
		print_State(top(print_Stack)->state);
		pop(&print_Stack);
		act++;
	}
	printf("\n************Tong so trang thai bai toan la: %d",act);
}


// ham chinh //
int main(){
	State cur_state;
	init_State(&cur_state);
	
	
	Node* p = DFS_Algorithm(cur_state);
	print_WaysToGetGoal(p);
	
	
	return 1;
}
