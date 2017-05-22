clear all;

files=[];

%
%param fileNamePrfx: Prefix of file
%param fileID the id of the file
%param x_vel_stimuli: [rep_seq_t rep_seq_y] with rep_seq_t = [start end],
%rep_seq_y = [start end]
%
%param y_vel_stimuli: [rep_seq_t rep_seq_y] with rep_seq_t = [start end],
%rep_seq_y = [start end]
%
%param rate_psi_stimuli: [rep_seq_t rep_seq_y] with rep_seq_t = [start end],
%rep_seq_y = [start end]
%
%param img_fps: Frames per socond of the cam
%
%param img_size: Resolution of cameras image
%
%param block_size: Block size of block matching algorithm
%

%--------------------------------------------------------------------------
% Test Environment 1
% Stimuli:
%   x_vel_stimuli: [0 9 0 9]
%   y_vel_stimuli: [0 9 0 0]
%   rate_spi_stimuli: [0 9 0 0]
% Image Config:
%   fps: 100
%   Size: [500 500]
%   Image: 
% Block Matching Config:
%   Block Size: [31 31]
%   Block Overlap: [0 0]
%   Max. Displaysment: [7 7]
%--------------------------------------------------------------------------

%Variation of Block Size
%--------------------------------------------------------------------------

% files=[TEST_FCN('Rec', 11, [0 10 0 0.1], [0 10 0 0], [0 10 0 0], 10, [500 500], [31 31], [0:0.1:20])]
% 
% files=strvcat(files,TEST_FCN('Rec', 12, [0 10 0 0.1], [0 10 0 0], [0 10 0 0], 10, [500 500], [131 131], [0:0.1:20]))
% 
% files=strvcat(files,TEST_FCN('Rec', 13, [0 10 0 0.1], [0 10 0 0], [0 10 0 0], 10, [500 500], [231 231], [0:0.1:20]))
% 
% files=strvcat(files,TEST_FCN('Rec', 14, [0 10 0 0.1], [0 10 0 0], [0 10 0 0], 10, [500 500], [331 331], [0:0.1:20]))
% 
% files=strvcat(files,TEST_FCN('Rec', 15, [0 10 0 0.1], [0 10 0 0], [0 10 0 0], 10, [500 500], [431 431], [0:0.1:20]))

%Variation of Frames Per Second
%--------------------------------------------------------------------------
HSE_Bottom_1=imresize(imread('D:\GoogleMapsBilder\PAR\HSE_Bottom_1.jpg'), 1);
%HSE_Bottom_2=imresize(imread('D:\GoogleMapsBilder\PAR\HSE_Bottom_2.jpg'), 1);
iterations=5;
for i=1:2
LOAD_SYSTEM('Optical_Movement_Detection_PAR');
TEST_FCN('ParRec', 21, [0 1 0 0.5], [0 10 0 0], [0 10 0 0], 10, [100 100], [31 31], [0:0.1:20], 'HSE_Bottom_1');
end

%files=strvcat(files,TEST_FCN('Rec', 22, [0 1 0 0.5], [0 1 0 0], [0 1 0 0], 10, [500 500], [31 31], [0:0.1:20]))

%files=strvcat(files,TEST_FCN('Rec', 23, [0 1 0 0.5], [0 1 0 0], [0 1 0 0], 10, [500 500], [31 31], [0:0.1:20]))

%files=strvcat(files,TEST_FCN('Rec', 24, [0 1 0 0.5], [0 10 0], [0 1 0 0], 10, [500 500], [31 31], [0:0.1:20]))

%files=strvcat(files,TEST_FCN('Rec', 25, [0 1 0 0.5], [0 1 0 0], [0 1 0 0], 10, [500 500], [31 31], [0:0.1:20]))

% %Variation of Image Size
%--------------------------------------------------------------------------
