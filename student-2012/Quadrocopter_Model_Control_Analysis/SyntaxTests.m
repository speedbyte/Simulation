A = [1+1i -1+1i -1-1j; 1-1i 1i 1; -1 -1i 1i];

[R,C]=size(A);
Max_Vec_Length = R*C;
Sec_1 = 1:Max_Vec_Length;
Sec_2 = 1:Max_Vec_Length;
Sec_3 = 1:Max_Vec_Length;
Sec_4 = 1:Max_Vec_Length;

Sec_1_Cnt = 0;
Sec_2_Cnt = 0;
Sec_3_Cnt = 0;
Sec_4_Cnt = 0;

%sectors
%       ^Im
%       |         
%   4   |  1
%-------------->Re
%   3   |  2
%       |

for i=1:R
    for j=1:C
      j=A(i,j);
    if(real(j)>=0) % Sec_1 or Sec_2
        if(imag(j)>=0) %Sec_1
            Sec_1_Cnt=Sec_1_Cnt+1;
            Sec_1(Sec_1_Cnt)=j;
%            disp('TMP_SEC_1:')
%            disp(j)
        else           %Sec_2
            Sec_2_Cnt=Sec_2_Cnt+1;
            Sec_2(Sec_2_Cnt)=j;
%            disp('TMP_SEC_2:')
%            disp(j)
        end
    else            % Sec_3 or Sec_4
        if(imag(j)>=0) %Sec_4
            Sec_4_Cnt=Sec_4_Cnt+1;
            Sec_4(Sec_4_Cnt)=j;
%            disp('TMP_SEC_4:')
%            disp(j)
        else           %Sec_3
            Sec_3_Cnt=Sec_3_Cnt+1;
            Sec_3(Sec_3_Cnt)=j;
%            disp('TMP_SEC_3:')
%            disp(j)
        end
    end
    end
end

Sec_1=Sec_1(1:Sec_1_Cnt);
Sec_2=Sec_1(1:Sec_2_Cnt);
Sec_3=Sec_1(1:Sec_3_Cnt);
Sec_4=Sec_1(1:Sec_4_Cnt);

Sec_1 = sum(abs(Sec_1(:)))/size(Sec_1, 2);
Sec_2 = sum(abs(Sec_2(:)))/size(Sec_2, 2);
Sec_3 = sum(abs(Sec_3(:)))/size(Sec_3, 2);
Sec_4 = sum(abs(Sec_4(:)))/size(Sec_4, 2);

Om_Re_Plus = (Sec_1+Sec_2)/2
Om_Re_Minus = (Sec_3+Sec_4)/2
Om_Im_Plus = (Sec_1+Sec_4)/2
Om_Im_Minus = (Sec_3+Sec_2)/2

clear Sec_1 Sec_2 Sec_3 Sec_4 Sec_1_Cnt Sec_2_Cnt Sec_3_Cnt Sec_4_Cnt R C i j Max_Vec_Length
