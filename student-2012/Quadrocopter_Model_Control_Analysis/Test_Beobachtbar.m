sys = linmod('test')
[ABAR, BBAR, CBAR, T, K] = obsvf(sys.a, sys.b, sys.c);
display('Anzahl beobachtbarer Zust�nde: '), sum(K)