cat(fubby).
hasblackspots(fubby).
dog(figaro).
haswhitespots(figaro).

owns(mary,pet(X)):-cat(X),hasblackspots(X).

loves(X,Y):-owns(X,Y).

/*
cat(X).
owns(X,Y).
loves(X,Y).
owns(mary,X).
*/