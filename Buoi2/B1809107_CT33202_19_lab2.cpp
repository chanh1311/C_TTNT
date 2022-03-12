/* 	
MSSV : B1809107
HoTen: Nguyen Van Chanh
STT: 19
*/


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
	
	
	if (empty_col < BOARD_COLS - 1){	// cot phai la 0 hoac 1 moi di chuyen dc //
		
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
//--------------------------Cau Truc Node----------------------------//

typedef struct Node{
	State state;
	struct Node* parent;
	int no_function;
	int g;		// Luu gia tri duong di cua nut goc den nut hien tai
	int h;		// Luu ket qua uoc luong cua ham heuristic cua nut hien tai den trang thai dich
	int f;		// f = g + h
} Node;


// Dinh nghia ham so sanh gia tri f cua 2 node,
// dung de cai dat Hang Doi Uu Tien (Priority Queue).
// Giai thuat hau an (Greedy) va giai thuat Best First Search du dung Hang Doi Uu Tien
struct node_cmp {
    bool operator() (Node* n1, Node* n2) {
        return n1->f > n2->f;
    }
};


//Trang thai uu tien //


int find_state_in_priority_queue(State state, priority_queue<Node*, vector<Node*>, node_cmp> q) {
	while(!q.empty()) {
		if(compareStates(q.top()->state, state))
			return 1;
		q.pop();
	}
	return 0;
}

// Tim 1 node //
Node* find_node(State state, priority_queue<Node*, vector<Node*>, node_cmp> q) {
	while(!q.empty()) {
		if(compareStates(q.top()->state, state))
			return q.top();
		q.pop();
	}  
    return NULL;
}


//-------------------------Ham heristic-------------------------//
// 3.2. Dinh nghia cac ham heuristic

// ham heuristic h1: so luong vi trí sai khác cua trang thái s1 so voi s2

int h1(State s1, State s2) {
	int count = 0;
	for(int row = 0; row < BOARD_ROWS; row++) {
		for(int col = 0; col < BOARD_COLS; col++) {
			if(s1.num[row][col] != 0) {
				if(s1.num[row][col] != s2.num[row][col]) {
					count++;
				}
			}
		}
	}
	return (count);
}

// ham heuristic h2: tong khoang cach cua cac o den vi tri dung cua no trong trang thai muc tieu


int h2(State s, State s2) {
    int count = 0;
    for (int row = 0; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS; col++) {
            if (s.num[row][col] != EMPTY_TILE) {
                for (int r = 0; r < BOARD_ROWS; r++) {
                    for (int c = 0; c < BOARD_COLS; c++) {
                        if (s.num[row][col] == s2.num[r][c]) {
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


//          ham chon ham heuristic          //
int heuristic(State s1, State s2, int func) {
	if(func == 1)
		return h1(s1, s2);
	else
		return h2(s1, s2);
}
//----------------------------------Giai thuat tham an------------------------------//
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
//			printf("\nTong so nut trong Open la: %d", priority_queue_Open.size());
//			printf("\nTong so nut trong Close la: %d", priority_queue_Close.size());
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
// -------------------------------Giai thuat A*---------------------------- //
Node* Astart(State init_state, State goal_state, int func){
		
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
//			printf("\nTong so nut trong Open la: %d", priority_queue_Open.size());
//			printf("\nTong so nut trong Close la: %d", priority_queue_Close.size());
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
// hien thi ket qua //
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
		printf("g = %d", stackPrint.top()->g);// doi voi hau an thi khong can dong nay! //
		printf("\nh = %d", stackPrint.top()->h);
		printf("\nf = %d", stackPrint.top()->f);
		printf("\nDoi voi hau an(Greedy) thi khong tinh tham so g!");
		stackPrint.pop();
		no_action++;
	}
}



// ham main //
int main() {
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
	// Cam on thay da cho them thoi gian, nho vay ma em da hieu cach hoat dong cua doan code tren //
}
