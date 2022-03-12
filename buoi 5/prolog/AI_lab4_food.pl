thucan(ga).
thucan(tao).
thucan(X) :-  an(Y,X), consong(Y), !.
consong(bill).
an(bill,dauphong).
an(john,X) :- thucan(X).
an(sue,X) :- an(bill,X).