[A,B,C,D]=linmod('testeqom'); %Zustandsmatrizen aus Model

System = ss(A, B, C, D);
rank(ctrb(System))                      %Prüfung der Steuerbarkeit
rank(obsv(System))                      %Prüfung der Beobachtbarkeit
