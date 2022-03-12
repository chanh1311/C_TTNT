
/* 
Ho ten: Nguyen Van Chanh
MSSV: B1809107
STT: 19
*/




#include<stdio.h>
#include<stdlib.h>

// Khai bao cac hang can thiet cho bai toan //
#define tankcapacity_X 9
#define tankcapacity_Y 4
#define empty 0
#define Maxlength 100
#define goal 6

const char* action[] = {"First","Pour Full X","Pour Full Y","Pour Empty X","Pour Empty Y","Pour X to Y", "Pour Y to X"};

// ___________________Cau truc trang thai_____________________ //

//khai bao cau truc trang thai//
typedef struct {
	int x;	//luong nuoc trong binh x//
	int y;	//luong nuoc trong binh y//
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
typedef struct{
	Node* Elements[Maxlength];
	int front,rear;
}Queue;
void makeNull_Queue(Queue *Q){
	Q->front=-1;
	Q->rear=-1;
}
int empty_Queue(Queue Q){
	return Q.front==-1;
}
int full_Queue(Queue Q){
	return (Q.rear-Q.front+1)%Maxlength==0;
}

Node* getFront(Queue Q){
	if (empty_Queue(Q))
		printf("Hang doi rong");
	else return Q.Elements[Q.front];
}
void del_Queue(Queue *Q){
	if (!empty_Queue(*Q)){
		if (Q->front==Q->rear)
			makeNull_Queue(Q);
		else Q->front=Q->front+1;		
	}
	else printf("Hang doi rong");

}
void push_Queue(Queue *Q, Node *node){
	if (!full_Queue(*Q)){
		if (empty_Queue(*Q))
			Q->front=0;
		Q->rear=Q->rear+1;
		Q->Elements[Q->rear]=node;
	}
	else printf("Hang doi day");
}

int find_State(State S, Queue Q){
	int i;
	for(i=Q.front;i<Q.rear;i++){
		if (Q.Elements[i]->state.x==S.x && Q.Elements[i]->state.y==S.y)	return 1;
	}
	return 0;
}

// _______________________BFS___________________________ //

Node* breathFirstSearch(State S){
	// Khoi tao opened va closed //
	Queue Opened;
	Queue Closed;
	makeNull_Queue(&Opened);
	makeNull_Queue(&Closed);
	
	// Tao va gan gia tri Node root //
	Node* root = (Node*)malloc(sizeof(Node));
	root->state=S;
	root->Parent=NULL;
	root->no_function=0;
	// Day Node root vao hang doi //
	push_Queue(&Opened,root);
	
	
	// Duyet den khi Opened rong //
	while (!empty_Queue(Opened)){
		
		// lay phan tu trong dau hang doi Opened va day no vao Closed //
		Node* node = getFront(Opened);	
		del_Queue(&Opened);
		push_Queue(&Closed,node);
		
		// Neu la ket qua thi tra ve //
		if (goalCheck(node->state))	
			return node;
		
		// Thuc thi lan luot cac trang thai moi //	
		int opt;
		for (opt = 1;opt <= 6; opt++){
			State newState;
			makeNullState(&newState);
			//Tao trang thai moi va thuc hien tiep neu trang thai chua ton tai //
			if(call_Operator(node->state,&newState,opt)){
				if (!find_State(newState,Closed) && !find_State(newState,Opened)) {
					
					// tao Node moi va gan trang thai chua ton tai cho Node //
					Node* newNode=(Node*)malloc(sizeof(Node));
					newNode->state=newState;
					newNode->Parent=node;
					newNode->no_function=opt;
					// Day Node vao Opened //
					push_Queue(&Opened,newNode);
				}
			}
			
		}
	}
	
	return NULL;
}
//chuyen tu mot hang doi sang hang doi khac voi thu tu nguoc lai
void reverse_Queue(Queue Q, Queue *result){
	makeNull_Queue(result);
	int i;
	for (i=Q.rear;i>=Q.front;i--){
		push_Queue(result,Q.Elements[i]);
	}
}

// Hien thi ket qua // 
void print(Node* node){
	printf("Ket qua duyet:\n");
	Queue Q;
	makeNull_Queue(&Q);
	
	// Do nguoc //
	while(node->Parent != NULL){
		push_Queue(&Q,node);
		node = node->Parent;
	}
	push_Queue(&Q,node);
	int act=0;
	Queue queuePrint;
	reverse_Queue(Q,&queuePrint);
	
	// Hien thi ket qua Duyet //
	while (!empty_Queue(queuePrint)){
		printf(" Hanh dong %d: %s \t",act, action[getFront(queuePrint)->no_function]);
		print_State(getFront(queuePrint)->state);
		del_Queue(&queuePrint);
		act++;
	}
}
//____________________Chuong trinh chinh_______________________//
int main(){
	State S={0,0};
	Node* duyet=(Node*)malloc(sizeof(Node));
	duyet=breathFirstSearch(S);
	print(duyet);
	return 0;
}

















































				


