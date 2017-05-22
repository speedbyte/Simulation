clear all;
close all;

files=[];

run quadrocopter_param

LOAD_SYSTEM('System_Design_Quadrocopter')

%--------------------------------------------------------------------------
% Test Environment 1
%--------------------------------------------------------------------------
%[Opt_Var_Trans Opt_Var_ST_Trans Opt_Limit_Trans Opt_Ori_SG_Trans Opt_Var_Rot Opt_Var_ST_Rot Opt_Limit_Rot Opt_Ori_SG_Rot Opt_Delay_Global Opt_ST_Global]
%       1               2               3               4              5             6               7             8             9               10
%--------------------------------------------------------------------------
%files=[TEST_FCN('Rec', 11, [5 0], [0 0], [0 0], [5 2], [0, 0.1, inf, 1, 0, 0.1, inf, 1, 0.000, 0.001], inf)]
% 

%Theta
 files=[             STEP_TEST_FCN('STE_THE', 10, [5 10], [0 0], [0 0], 10)]
counter=1;
for i=20:10:150
  files=strvcat(files, STEP_TEST_FCN('STE_THE', 10+counter, [5 i], [0 0], [0 0], 10))
  counter=counter+1;
end

counter=1;
%Phi
  files=[             STEP_TEST_FCN('STE_PHI', 10, [0 0], [5 10], [0 0], 10)]
 counter=1;
 for i=20:10:150
   files=strvcat(files, STEP_TEST_FCN('STE_PHI', 10+counter, [0 0], [5 i], [0 0], 10))
   counter=counter+1;
 end
 
%Psi
counter=1;
  files=[             STEP_TEST_FCN('STE_PSI', 10, [0 0], [0 0], [5 10], 10)]
 counter=1;
 for i=20:10:150
   files=strvcat(files, STEP_TEST_FCN('STE_PSI', 10+counter, [0 0], [0 0], [5 i], 10))
   counter=counter+1;
 end
 
 
 