%
%param fileNamePrfx: Prefix of file
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
%param block_size: Block size of blick matching algorithm
%
function [fileName]=TEST_FCN( fileNamePrfx, fileID, x_vel_stimuli, y_vel_stimuli, rate_psi_stimuli, img_fps, img_size, block_size, simTime, inputImage)

% Initializations
% ===============
tagCollect =[];
timeCollect =[];
TCollect =[];
plotcolors ='bgcmkbgcmkbgcmk';
nvals = 0;

%Paths to the objects
x_vel_stimuli_path = 'Optical_Movement_Detection_PAR/x_vel_stimuli';
y_vel_stimuli_path = 'Optical_Movement_Detection_PAR/y_vel_stimuli';
rate_psi_stimuli_path = 'Optical_Movement_Detection_PAR/rate_psi_stimuli';
To_File_path='Optical_Movement_Detection_PAR/To File';
Image_Processing_path='Optical_Movement_Detection_PAR/Image Processing';
Simulation_path='Optical_Movement_Detection_PAR';

% Backup original values
% ======================
% Params of Repeating Table Block
%     rep_seq_t: [1x1 struct]
%     rep_seq_y: [1x1 struct]

x_vel_stimuli_orig_t= regexprep(get_param(x_vel_stimuli_path,'rep_seq_t'),'\n','');
x_vel_stimuli_orig_y=regexprep(get_param(x_vel_stimuli_path,'rep_seq_y'),'\n','');

y_vel_stimuli_orig_t=regexprep(get_param(y_vel_stimuli_path,'rep_seq_t'),'\n','');
y_vel_stimuli_orig_y=regexprep(get_param(y_vel_stimuli_path,'rep_seq_y'),'\n','');

rate_psi_stimuli_orig_t=regexprep(get_param(rate_psi_stimuli_path,'rep_seq_t'),'\n','');
rate_psi_stimuli_orig_y=regexprep(get_param(rate_psi_stimuli_path,'rep_seq_y'),'\n','');

img_fps_orig=get_param(Image_Processing_path,'Ts_Opt');
img_size_orig=get_param(Image_Processing_path,'Cam_Img_Dim');
block_size_orig=get_param(Image_Processing_path,'Block_Matching_Size');

filename_rec_orig=get_param(To_File_path,'File name');

%load_cmd_orig=get_param(Image_Processing_path, 'load_cmd');

x_vel_str_t_start=numStrCat(x_vel_stimuli(1));
x_vel_str_t_end=numStrCat(x_vel_stimuli(2));
x_vel_str_y_start=numStrCat(x_vel_stimuli(3));
x_vel_str_y_end=numStrCat(x_vel_stimuli(4));

y_vel_str_t_start=numStrCat(y_vel_stimuli(1));
y_vel_str_t_end=numStrCat(y_vel_stimuli(2));
y_vel_str_y_start=numStrCat(y_vel_stimuli(3));
y_vel_str_y_end=numStrCat(y_vel_stimuli(4));

rate_psi_str_t_start=numStrCat(rate_psi_stimuli(1));
rate_psi_str_t_end=numStrCat(rate_psi_stimuli(2));
rate_psi_str_y_start=numStrCat(rate_psi_stimuli(3));
rate_psi_str_y_end=numStrCat(rate_psi_stimuli(4));

fps_str=numStrCat(img_fps);
img_size_str_h=numStrCat(img_size(1));
img_size_str_w=numStrCat(img_size(2));
blk_size_str_h=numStrCat(block_size(1));
blk_size_str_w=numStrCat(block_size(2));

% --> Record with To File
% filename_rec=strcat(fileNamePrfx,'_x_[',x_vel_str_t_start,'-',...
%     x_vel_str_t_end,'-',x_vel_str_y_start,'-',x_vel_str_y_end,']_y_[',y_vel_str_t_start,'-',y_vel_str_t_end,...
%     '-',y_vel_str_y_start,'-',y_vel_str_y_end,']_rpsi_[',rate_psi_str_t_start,'-',rate_psi_str_t_end,...
%     '-',rate_psi_str_y_start,'-',rate_psi_str_y_end,']_fps_',fps_str,'imgSize_[',img_size_str_h,'-',...
%     img_size_str_w,']_blkSize_[',blk_size_str_h,'-',blk_size_str_w,'].mat');

filename_rec=strcat(fileNamePrfx, numStrCat(fileID),'.mat');

fileName=filename_rec;
%Set file name
set_param(To_File_path,'File name',filename_rec);

%Set stimuli
set_param(x_vel_stimuli_path, 'rep_seq_t', strcat('[',num2str(x_vel_stimuli(1)),',',num2str(x_vel_stimuli(2)),']'));
set_param(x_vel_stimuli_path, 'rep_seq_y', strcat('[',num2str(x_vel_stimuli(3)),',',num2str(x_vel_stimuli(4)),']'));

set_param(y_vel_stimuli_path, 'rep_seq_t', strcat('[',num2str(y_vel_stimuli(1)),',',num2str(y_vel_stimuli(2)),']'));
set_param(y_vel_stimuli_path, 'rep_seq_y', strcat('[',num2str(y_vel_stimuli(3)),',',num2str(y_vel_stimuli(4)),']'));

set_param(rate_psi_stimuli_path, 'rep_seq_t', strcat('[',num2str(rate_psi_stimuli(1)),',',num2str(rate_psi_stimuli(2)),']'));
set_param(rate_psi_stimuli_path, 'rep_seq_y', strcat('[',num2str(rate_psi_stimuli(3)),',',num2str(rate_psi_stimuli(4)),']'));

set_param(Image_Processing_path, 'Ts_Opt', num2str(img_fps,5));
set_param(Image_Processing_path, 'Cam_Img_Dim',strcat('[',num2str(img_size(1)),',',num2str(img_size(2)),']'));
set_param(Image_Processing_path, 'Block_Matching_Size', strcat('[',num2str(block_size(1)),',',num2str(block_size(2)),']'));

%set_param(Image_Processing_path, 'load_cmd', inputImage);

%Execute Simulation
sim(Simulation_path, simTime);

%Restore parameters
set_param(x_vel_stimuli_path,'rep_seq_t', x_vel_stimuli_orig_t);
set_param(x_vel_stimuli_path,'rep_seq_y', x_vel_stimuli_orig_y);

set_param(y_vel_stimuli_path,'rep_seq_t', y_vel_stimuli_orig_t);
set_param(y_vel_stimuli_path,'rep_seq_y', y_vel_stimuli_orig_y);

set_param(rate_psi_stimuli_path,'rep_seq_t', rate_psi_stimuli_orig_t);
set_param(rate_psi_stimuli_path,'rep_seq_y', rate_psi_stimuli_orig_y);
%rate_spi_stimuli_orig format => [rep_seq_t rep_seq_y]

set_param(Image_Processing_path,'Ts_Opt', img_fps_orig);
set_param(Image_Processing_path,'Cam_Img_Dim', img_size_orig);
set_param(Image_Processing_path,'Block_Matching_Size', block_size_orig);

%set_param(Image_Processing_path,'load_cmd', load_cmd_orig);

set_param(To_File_path,'File name', filename_rec_orig);
end