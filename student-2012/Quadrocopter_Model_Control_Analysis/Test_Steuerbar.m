[A, b, cT,d] = linmod('test');
Sys = ss(A,b,cT,d);
Qb = ctrb(Sys);
display('Anzahl steuerbarer Zust�nde: '), rank(Qb)