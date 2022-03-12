move(1,X,Y,_) :-
   write('chuyen dia tren dinh tu '), write(X), write(' to '), write(Y), nl.
move(N,X,Y,Z) :-
   N>1,
   M is N-1,
   move(M,X,Z,Y),
   move(1,X,Y,_),
   move(M,Z,Y,X).
   
% move(3,cot1,cot3,cot2). %



/*
move(N,X,Y,Z) :-

3>1
M = 2
move(2,cot1,cot2,cot3).
2>1
M = 1
move(1,cot1,cot3,cot2).(1)
move(1,cot1,cot2,_).(2)
move()

*/