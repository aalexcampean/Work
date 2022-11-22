% Student exercise profile
:- set_prolog_flag(occurs_check, error).        % disallow cyclic terms
:- set_prolog_stack(global, limit(8 000 000)).  % limit term space (8Mb)
:- set_prolog_stack(local,  limit(2 000 000)).  % limit environment space

% 6. Generate the list of all arrangements of K elements of a given list.
% Eg: [2, 3, 4] K=2 => [[2,3], [3,2], [2,4], [4,2], [3,4], [4,3]] (not necessary in this order)


%insertElement(L - list, E - element, R - result list)
%insertElement(i,i,o) - flow model
insertElement(L, E, [E|L]).
%insertElement([H|T], E, [H|R]) :- 
%         insertElement(T, E, R).
%mathematical model:
%insertElement(l1...ln, e)	= e U l1l2...ln, if we insert the element on the first position
%							= l1 U insertElement(l2...ln, e), otherwise


%arrangements(L - list, K - number of elements, R - result list)
%arrangements(i, i, o) - flow model
arrangements([E|_], 1, [E]).
arrangements([_|T], K, R) :-
    arrangements(T, K, R).
arrangements([H|T], K, R1) :-
    K > 1,
    K1 is K - 1,
    arrangements(T, K1, R),
    insertElement(R, H, R1).
%mathematical model:
%arrangements(l1...ln, k)	= l1, if k = 1, n >= 1
%							= arrangements(l2...ln, k), if k >= 1
%							= insert(l1, arrangements(l2...ln, k-1)), if k > 1


%oneSolution(L - list, K - number of elements, R - result list)
%oneSolution(i, i, o) - flow model
oneSolution(L, K, R) :-
    arrangements(L, K, R).


%allSolutions(L - list, K - number of elements, R - result list)
%allSolutions(i, i, o) - flow model
allSolutions(L, K, R) :-
    findall(RPartial, oneSolution(L, K, RPartial), R).