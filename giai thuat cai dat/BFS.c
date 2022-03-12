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

	int act=1;
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
