hay_luot_web(X):-biet_lap_trinh(X),biet_dung_mt(X).
biet_dung_mt(X):-biet_lap_trinh(X).
biet_lap_trinh(X):-hoc_gioi(X,toan).
hoc_gioi(nam,toan).
hoc_gioi(an,toan).
hoc_gioi(linh,van).

/*
hoc_gioi(nam,X).

hoc_gioi(X,toan).
biet_lap_trinh(X).
hay_luot_web(X).


*/