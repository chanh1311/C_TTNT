#include "Stack.c"
#include <stdlib.h>
const char* action[] = {"First","Pour Full X","Pour Full Y","Pour Empty X","Pour Empty Y","Pour X to Y", "Pour Y to X"};
Node* DFS_Algorithm(State state){
	// tao open va close //
	Stack opened;
	Stack closed;
	makeNull_Stack(&opened);
	makeNull_Stack(&closed);
	// tao node parent va gan gia tri //
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	// day parent vao opened //
	push(root,&opened);
	
	// Duyet tat ca phan tu trong closed //
	while(!check_EmptyStack(opened)){
		// xet phan tu top trong opened //
		Node* node = top(opened);
		pop(&opened);
		push(node,&closed);
		
		
		
		// kiem tra no co phai trang thai muc tieu hay khong //
		if(goalCheck(node->state))
			return node;
			
		// thuc hien cac phep toan tren nut nay de tao ra cac nut khac //
		int opt = 1;
		for( opt ; opt <= 6; opt++){
			State newstate;
			if(call_Operator(node->state,&newstate,opt)){
			// Neu trang thai da ton tai thi bo qua //
				if(find_Stack(newstate,opened) || find_Stack(newstate,closed))
					continue;
				// Tao nut moi va gan gia tri //
				Node* newnode = (Node*)malloc(sizeof(Node));
				newnode->Parent = node;
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
	while(node->Parent != NULL){
		push(node,&print_Stack);
		node = node->Parent;
	}
	// them phan tu dau tien vao Stack //
	push(node,&print_Stack);
	
	// Hien thi lan luot cac hanh dong! //
	int act = 0;
	while(!check_EmptyStack(print_Stack)){
		printf("\n Action %d: %s ",act,(action[top(print_Stack)->no_function]));
		printState(top(print_Stack)->state);
		pop(&print_Stack);
		act++;
	}
}
