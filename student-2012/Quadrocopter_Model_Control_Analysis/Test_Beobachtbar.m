sys = linmod('test')
[ABAR, BBAR, CBAR, T, K] = obsvf(sys.a, sys.b, sys.c);
display('Anzahl beobachtbarer Zustände: '), sum(K)