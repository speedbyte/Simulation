
files=['STE_THE011.mat';
    'STE_THE012.mat';
    'STE_THE013.mat';
    'STE_THE014.mat';
    'STE_THE015.mat';
    'STE_THE016.mat';
    'STE_THE017.mat';
    'STE_THE018.mat';
    'STE_THE019.mat';
    'STE_THE020.mat';
    'STE_THE021.mat';
    'STE_THE022.mat';
    'STE_THE023.mat'
    ];
hold on
figure(1);
STEP_PLOT_FILES(files, 3);
hold off;


files=[
'STE_PHI010.mat';
'STE_PHI011.mat';
'STE_PHI012.mat';
'STE_PHI013.mat';
'STE_PHI014.mat';
'STE_PHI015.mat';
'STE_PHI016.mat';
'STE_PHI017.mat';
'STE_PHI018.mat';
'STE_PHI019.mat';
% 'STE_PHI020.mat';
% 'STE_PHI021.mat';
% 'STE_PHI022.mat';
% 'STE_PHI023.mat';
% 'STE_PHI024.mat'
]
hold on
figure(2);
STEP_PLOT_FILES(files, 2);
hold off;


files=[
% 'STE_PSI010.mat';
% 'STE_PSI011.mat';
% 'STE_PSI012.mat';
% 'STE_PSI013.mat';
% 'STE_PSI014.mat';
% 'STE_PSI015.mat';
% 'STE_PSI016.mat';
% 'STE_PSI017.mat';
% 'STE_PSI018.mat';
% 'STE_PSI019.mat';
% 'STE_PSI020.mat';
% 'STE_PSI021.mat';
'STE_PSI022.mat';
'STE_PSI023.mat';
'STE_PSI024.mat'...
]
hold on;
figure(3);
STEP_PLOT_FILES(files, 4);
hold off;
