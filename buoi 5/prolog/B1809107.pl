biet(X,Z) :- hohang(X,Y),hohang(Y,Z).
hohang(X1,Y1) :- di(X1,Y1).
hohang(X2,Y2) :- co(X2,Y2).
di(lan,hong).
di(hong,mai).
co(hong,phuong).

%biet(X,Y).
