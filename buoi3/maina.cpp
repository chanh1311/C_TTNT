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
