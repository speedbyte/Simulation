[A,B,C,D]=linmod('testeqom'); %Zustandsmatrizen aus Model

System = ss(A, B, C, D);
rank(ctrb(System))                      %Pr�fung der Steuerbarkeit
rank(obsv(System))                      %Pr�fung der Beobachtbarkeit
