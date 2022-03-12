/* cac cau truy van:

movie(american_beauty, X).
movie(X, 2000).
movie(X,Y),(Y<2000).
movie(X,Y),(Y > 1990).

(actor(A,X,_),actor(B,X,_),A@>B).
director(M,D),actress(M,scarlett_johansson,_).
actor(X,Y,_),director(X,Y).
(actor(X,Y,_),director(X,Y));(actress(K,Z,_),director(K,Z)).
actor(X,john_goodman,_), actor(X,jeff_bridges,_).

*/
