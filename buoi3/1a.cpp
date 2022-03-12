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
