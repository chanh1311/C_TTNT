/* B1809107 
Nguyen Van Chanh
STT 19
*/




#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <set>
#include <stack>
#include <queue>
#include <fstream>


#include <malloc.h>
#define maxlength 1000


const int BOARD_ROWS = 3;
const int BOARD_COLS = 3;
const int EMPTY_TILE = 0;
const int MAX_OP = 4;

using namespace std;
const char* action[]={"Trang thai dau","di chuyen sang trai","di chuyen sang phai","di chuyen len tren","di chuyen xuong duoi"};




// cai dat trang thai //
typedef struct {
	int A[BOARD_ROWS][BOARD_COLS];
	int i,j;		//vi tri hien tai cua o trong
}State;

// hien thi //
void print_state(State s) {
	for(int row = 0; row < BOARD_ROWS; row++) {
		for(int col = 0; col < BOARD_COLS; col++) {
			if(s.A[row][col] == 0)
				printf("_   ");
			else
				printf("%d   ", s.A[row][col]);	
		}
		printf("\n");
	}	
}
//// khoi tao //
//void makenullState(State *S){
//	int i,j;
//	for (i=0;i<3;i++)
//		for (j=0;j<3;j++)
//			S->A[i][j]=-1;
//	S->i = 0;
//	S->j = 0;
//}
void printState(State S){
	int i,j;
	for (i=0;i<3;i++){
		for (j=0;j<3;j++)
			printf("%d ",S.A[i][j]);
		printf("\n");
	}	
}

//int goalcheck(State SS, State GS){
//	int i,j;
//	for (i=0;i<3;i++)
//		for (j=0;j<3;j++)
//			if (SS.A[i][j] != GS.A[i][j])
//				return 0;
//	return 1;
//}
//void copyState(State S, State *result){
//	int i,j;
//	for (i=0;i<3;i++)
//		for (j=0;j<3;j++)
//			result->A[i][j]=S.A[i][j];
//	result->i=S.i;
//	result->j=S.j;
//}

//So sanh hai trang thai co bang nhau khong
bool compareStates(State s1, State s2){
	// Kiem tra o trong cua 2 trang thai
	if(s1.i!= s2.i || s1.j != s2.j)
		return false;
	
	// Kiem tra tung vi tri cua 2 trang thai s1 va s2
	for(int row = 0; row < BOARD_ROWS; row++) {
		for(int col = 0; col < BOARD_COLS; col++) {
			if(s1.A[row][col] != s2.A[row][col]) {
				return false;	
			}	
		}
	}
	return true;
}

// --------- cau truc Node --------------  //
typedef struct Node{
	State state;
	struct Node* parent;
	int no_function;
	int g;		// Luu gia tri duong di cua nut goc den nut hien tai
	int h;		// Luu ket qua uoc luong cua ham heuristic cua nut hien tai den trang thai dich
	int f;		// f = g + h
} Node;



struct node_cmp {
    bool operator() (Node* n1, Node* n2) {
        return n1->f > n2->f;
    }
};

// --------------Ham heuratic------------------- //
int h1(State s1, State s2) {
	int count = 0;
	for(int row = 0; row < BOARD_ROWS; row++) {
		for(int col = 0; col < BOARD_COLS; col++) {
			if(s1.A[row][col] != 0) {
				if(s1.A[row][col] != s2.A[row][col]) {
					count++;
				}
			}
		}
	}
	return (count);
}


int h2(State s, State s2) {
    int count = 0;
    for (int row = 0; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS; col++) {
            if (s.A[row][col] != EMPTY_TILE) {
                for (int r = 0; r < BOARD_ROWS; r++) {
                    for (int c = 0; c < BOARD_COLS; c++) {
                        if (s.A[row][col] == s2.A[r][c]) {
                            count += abs(r - row) + abs(c - col);
                            r = BOARD_ROWS; //hack to break 2 loops
                            break;
                        }
                    }
                }
            }
        }
    }
    
    return count;
}






int heuristic(State s1, State s2, int func) {
	if(func == 1)
		return h1(s1, s2);
	else
		return h2(s1, s2);
}

// ----------Queue uu tien------------//

int find_state_in_priority_queue(State state, priority_queue<Node*, vector<Node*>, node_cmp> q) {
	while(!q.empty()) {
		if(compareStates(q.top()->state, state))
			return 1;
		q.pop();
	}
	return 0;
}
 /////////////////////////////////////////////////////////////////
Node* find_node(State state, priority_queue<Node*, vector<Node*>, node_cmp> q) {
	while(!q.empty()) {
		if(compareStates(q.top()->state, state))
			return q.top();
		q.pop();
	}  
    return NULL;
}


//-------------------- Cac Hanh Dong------------------------//
//Di chuyen sang trai
int left(State cur_state, State *result){
	if (cur_state.j>0){
		copyState(cur_state,result);
		result->j--;
		result->A[result->i][result->j+1]=result->A[result->i][result->j];
		result->A[result->i][result->j]=-1;
		return 1;
	}
	return 0;

}
//Di chuyen sang phai
int right(State cur_state, State *result){
	if (cur_state.j<2){
		copyState(cur_state,result);
		
		result->j++;
		result->A[result->i][result->j-1]=result->A[result->i][result->j];
		result->A[result->i][result->j]=-1;
		return 1;
	}
	return 0;

}
//Di chuyen len tren
int up(State cur_state, State *result){
	if (cur_state.i>0){
		copyState(cur_state,result);
		result->i--;
		result->A[result->i+1][result->j]=result->A[result->i][result->j];
		result->A[result->i][result->j]=-1;
		return 1;
	}
	return 0;

}
//Di chuyen xuong duoi
int down(State cur_state, State *result){
	if (cur_state.i<2){
		copyState(cur_state,result);
		result->i++;
		result->A[result->i-1][result->j]=result->A[result->i][result->j];
		result->A[result->i][result->j]=-1;
		return 1;
	}
	return 0;

}

// ham goi cac hanh dong
bool call(State cur_state, State& result, int option){
	switch (option){
		case 1: return left(cur_state,&result); // di chuyen sang trai
		case 2: return right(cur_state,&result); // di chuyen sang phai
		case 3: return up(cur_state,&result); // di chuyen len tren
		case 4: return down(cur_state,&result); // di chuyen xuong duoi
		
		default: printf("Yeu cau khong hop le.");
			return false;
	}
}
//bool call(State s, State& out, int option) {
//    switch (option) {
//        case 1:
//            return sangTrai(s, &out);
//        case 2:
//            return sangPhai(s, &out);
//        case 3:
//            return lenTren(s, &out);
//        case 4:
//            return xuongDuoi(s, &out);
//        default:
//            return false;
//    }
//}

//__________________ Doc FIle _______________________//
State* read_file(string file) {
	//ifstream fin(file);
	ifstream fin(file.c_str());
	
	State *s = new State();
	for(int row = 0; row < BOARD_ROWS; row++) {
		for(int col = 0; col < BOARD_COLS; col++) {
			fin >> s->A[row][col];	
		}
	}
	fin >> s->i >> s->j;
	return s;
}
//----------------- Giai thuat hau an (Greedy)-----------------------//

Node* Greedy(State init_state, State goal_state, int func){
		
	// Khai bao hai hang doi Open va Close
	// Khac voi BFS, trong giai thuat Greedy cung nhu Best First Search,
	// chung ta su dung Hang Doi Uu Tien (xem giao trinh trang 59) 
	// (sap xep thu tu dua tren gia tri f cua cac node)
	priority_queue<Node*, vector<Node*>, node_cmp> priority_queue_Open; 
	priority_queue<Node*, vector<Node*>, node_cmp> priority_queue_Close;
	int step = 0;
	
	// Tao nut trang thai cha
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = init_state;
	root->parent = NULL;
	root->no_function = 0;
	root->h = heuristic(root->state, goal_state, func);
	root->f = root->h;
	priority_queue_Open.push(root);
	
	while(!priority_queue_Open.empty()){
		
		Node* node = priority_queue_Open.top();	// Lay ra gia tri BEN TRAI cua Open de kiem tra
		priority_queue_Open.pop();
		priority_queue_Close.push(node);
		
		// Kiem  tra xem dinh lay ra co phai la trang thai muc tieu
		if(compareStates(node->state, goal_state))
		{
			//printf("\nTong so nut trong Open la: %d", priority_queue_Open.size());
			//printf("\nTong so nut trong Close la: %d", priority_queue_Close.size());
			return node;
		}
		
		
		// Goi cac phep toan tren trang thai
		//printf("\n");
		int option;
		for(option=1; option<=MAX_OP; option++) {
			State newstate;
			
			if(call(node->state, newstate, option)) {
				
				// Neu trang thai moi sinh ra da ton tai thi bo qua
				
				if(find_state_in_priority_queue(newstate, priority_queue_Open) || 
					find_state_in_priority_queue(newstate, priority_queue_Close))
					continue;
				
				// Neu trang thai moi chua ton tai thi them vao hang doi
				Node *newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newstate;
				newNode->parent = node;
				newNode->no_function = option;
				newNode->h = heuristic(newstate, goal_state, func);
				newNode->f = newNode->h;
				priority_queue_Open.push(newNode);
				//printf("\nTrang thai moi duoc dua vao hang doi OPEN\n");
				//print_state(newstate);
				//printf("f = %d", newNode->f);
			}
		}
	}
	return NULL;
}

// ------------Giai thuat A*---------------------- //
Node* Astart(State init_state, State goal_state, int func){
		
	
	priority_queue<Node*, vector<Node*>, node_cmp> priority_queue_Open; 
	priority_queue<Node*, vector<Node*>, node_cmp> priority_queue_Close;
	int step = 0;
	
	// Tao nut trang thai cha
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = init_state;
	root->parent = NULL;
	root->no_function = 0;
	root->h = heuristic(root->state, goal_state, func);
	root->g = 0;
	root->f = root->h + root->g;
	priority_queue_Open.push(root);
	
	while(!priority_queue_Open.empty()){
		
		Node* node = priority_queue_Open.top();	// Lay ra gia tri BEN TRAI cua Open de kiem tra
		priority_queue_Open.pop();
		priority_queue_Close.push(node);
		
		// Kiem  tra xem dinh lay ra co phai la trang thai muc tieu
		if(compareStates(node->state, goal_state))
		{
			printf("\nTong so nut trong Open la: %d", priority_queue_Open.size());
			printf("\nTong so nut trong Close la: %d", priority_queue_Close.size());
			return node;
		}
		
		
		
		// Goi cac phep toan tren trang thai
		//printf("\n");
		int option;
		for(option=1; option<=MAX_OP; option++) {
			State newstate;
			
			if(call(node->state, newstate, option)) {
				
				// Neu trang thai moi sinh ra da ton tai thi bo qua
				
				if(find_state_in_priority_queue(newstate, priority_queue_Close))
					continue;
					
				Node* n= find_node(newstate, priority_queue_Open);
				
				if(n==NULL)	{
					// Neu trang thai moi chua ton tai thi them vao hang doi
					Node *newNode = (Node*)malloc(sizeof(Node));
					newNode->state = newstate;
					newNode->parent = node;
					newNode->no_function = option;
					newNode->h = heuristic(newstate, goal_state, func);
					newNode->g = node->g+1;
					newNode->f = newNode->h + newNode->g;
					priority_queue_Open.push(newNode);
					
					
				} else {
					n->g = node->g+1;
                    n->f = n->g+n->h;
				}
			}
		}
	}
	return NULL;
}

// ----------------Hien thi-------------------  //
void print_WaysToGetGoal_with_Heuristic(Node* node) {
	int no_action = 0;
	stack<Node*> stackPrint;
	
	// Duyet nguoc ve nut parent
	while(node->parent != NULL) {
		stackPrint.push(node);
		node = node->parent;
	}
	stackPrint.push(node);
	
	// In ra thu tu hanh dong
	
	while(!stackPrint.empty()){
		printf("\nAction %d: %s\n", no_action, action[stackPrint.top()->no_function]);
		print_state(stackPrint.top()->state);
		printf("g = %d", stackPrint.top()->g);
		printf("\nh = %d", stackPrint.top()->h);
		printf("\nf = %d", stackPrint.top()->f);
		stackPrint.pop();
		no_action++;
	}
}
int main() {
//	State *start_state;
//	
//	// Khai bao trang thai bat dau.
//	// Trang thai bat dau duoc cau hinh trong file test.txt
//	start_state = read_file("start_easy.txt");
//	printf("Trang thai bat dau: \n");
//	print_state(*start_state);
//	
//	
//	// Khai bao trang thai muc tieu.
//	// Trang thai muc tieu duoc cau hinh trong file goal.txt
//	State *goal_state;
//	goal_state = read_file("goal_easy.txt");
//	printf("\n");
//	printf("Trang thai muc tieu: \n");
//	print_state(*goal_state);
//	
//
//	
//	// Hien thi theo giai thuat A* //
//	printf("\n");
//	printf("*** Giai bai toan su dung ham heuristic h1 voi tim kiem Asao ***");
//	Node* astart_h1_result = Astart(*start_state, *goal_state, 1);
//	printf("\n");
//	print_WaysToGetGoal_with_Heuristic(astart_h1_result);
//	
//	//	printf("check");
//	// Em khong hieu vi sao toi day lai khong hien thi duoc cac trang thai, 2 giai thuat em tham khao cua thay, e can thoi gian de tim ra nguyen nhan //
//	
//	// Giai thuat hao an //
//	printf("\n");
//	printf("*** Giai bai toan su dung ham heuristic h1 voi tim kiem hau an ***");
//	Node* greedy_h1_result = Greedy(*start_state, *goal_state, 1);
//	printf("\n");
//	print_WaysToGetGoal_with_Heuristic(greedy_h1_result);
	
	// Them 2 file start_easy.txt va goal_easy.txt de chay //
	
	// Khai bao trang thai bat dau.
	// Trang thai bat dau duoc cau hinh trong file test.txt
	State *start_state;
	start_state = read_file("start_easy.txt");
	printf("Trang thai bat dau: \n");
	print_state(*start_state);
	
	
	// Khai bao trang thai muc tieu.
	// Trang thai muc tieu duoc cau hinh trong file goal.txt
	State *goal_state;
	goal_state = read_file("goal_easy.txt");
	printf("\n");
	printf("Trang thai muc tieu: \n");
	print_state(*goal_state);
	
	
	// ---------------Tim kiem Heuristic------------------ //
	
	printf("\n");
	printf("******************** Giai bai toan su dung ham heuristic h1 voi tim kiem hau an *******************");
	Node* greedy_h1_result = Greedy(*start_state, *goal_state, 1);
	printf("\n");
	print_WaysToGetGoal_with_Heuristic(greedy_h1_result);
	
	
	printf("\n");
	printf("******************** Giai bai toan su dung ham heuristic h2 voi tim kiem hau an *********************");
	Node* greedy_h2_result = Greedy(*start_state, *goal_state, 2);
	printf("\n");
	print_WaysToGetGoal_with_Heuristic(greedy_h2_result);
	
	
	printf("\n");
	printf("******************** Giai bai toan su dung ham heuristic h1 voi tim kiem A* **************************");
	Node* astart_h1_result = Astart(*start_state, *goal_state, 1);
	printf("\n");
	print_WaysToGetGoal_with_Heuristic(astart_h1_result);
	
	printf("\n");
	printf("******************** Giai bai toan su dung ham heuristic h2 voi tim kiem A* **************************");
	Node* astart_h2_result = Astart(*start_state, *goal_state, 2);
	printf("\n");
	print_WaysToGetGoal_with_Heuristic(astart_h2_result);
	
	
	return 0;
	

}
