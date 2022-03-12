%alpha1(Y, O, U, R, H, E, A, T, Sol).

alpha1(Y, O, U, R, H, E, A, T, [Y, O, U, R, Y, O, U, H, E, A, R, T]) :-
    between(1, 9, Y),
	
    between(0, 9, O),
    O \=Y,
	
    between(0, 9, U),
    U \= O, U \= Y,
	
    between(0, 9, R),
    R \= O, R \= Y, R \= U,
	
    between(1, 9, H),
    H \= O, H \= Y, H \= U, H \= R,
	
    between(0, 9, E),
    E \= O, E \= Y, E \= U, E \= R, E \= H,
	
    between(0, 9, A),
    A \= O, A \= Y, A \= U, A \= R, A \= H, A \= E,
	
    between(0, 9, T),
    T \= O, T \= Y, T \= U, T \= R, T \= H, T \= E, T \= A,
	
    Your is Y*1000 + O*100 + U*10 + R,
    You is Y*100 + O*10 + U,
    Heart is H*10000 + E*1000 + A*100 + R*10 + T,
	
    Heart is Your + You.