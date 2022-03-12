men(john).
men(fred).
men(harry).
women(mary).
women(julie).
women(susan).
women(anne).
blonde(john).
blonde(julie).
blonde(susan).
dark(fred).
dark(harry).
brunette(mary).
brunette(anne).
rich(X) :- cogi(X,gold).
cogi(fred,gold).
cogi(julie,gold).
cogi(anne,house).
cogi(john,car).
like(X,Y) :- men(X),women(Y).
like(X,Y) :- women(X), men(Y).

thich(john,X) :- like(john,X),rich(X).
thich(harry,X) :- like(harry,X),rich(X).

thich(john,X) :- like(john,X),blonde(X).
thich(fred,X) :- like(fred,X),brunette(X).



thich(mary,X) :- like(mary,X),dark(X).
thich(julie,X) :- like(julie,X),dark(X).
thich(julie,X) :- like(julie,X),rich(X).
