function varargout = Copter_GUI(varargin)
% COPTER_GUI M-file for Copter_GUI.fig
%      COPTER_GUI, by itself, creates a new COPTER_GUI or raises the existing
%      singleton*.
%
%      H = COPTER_GUI returns the handle to a new COPTER_GUI or the handle to
%      the existing singleton*.
%
%      COPTER_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in COPTER_GUI.M with the given input arguments.
%
%      COPTER_GUI('Property','Value',...) creates a new COPTER_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Copter_GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Copter_GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Copter_GUI

% Last Modified by GUIDE v2.5 25-Apr-2010 23:31:36

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Copter_GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @Copter_GUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before Copter_GUI is made visible.
function Copter_GUI_OpeningFcn(hObject, ~, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Copter_GUI (see VARARGIN)

% Choose default command line output for Copter_GUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Copter_GUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Copter_GUI_OutputFcn(hObject, ~, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on slider movement.
function hsliderRoll_Callback(hObject, ~, handles)
% hObject    handle to hsliderRoll (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.hetextRollDes,'String',get(hObject,'value'));
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function hsliderRoll_CreateFcn(hObject, ~, handles)
% hObject    handle to hsliderRoll (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function hsliderPitch_Callback(hObject, ~, handles)
% hObject    handle to hsliderPitch (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.hetextPitchDes,'String',get(hObject,'value'));

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function hsliderPitch_CreateFcn(hObject, ~, handles)
% hObject    handle to hsliderPitch (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function hsliderYaw_Callback(hObject, ~, handles)
% hObject    handle to hsliderYaw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.hetextYawDes,'String',get(hObject,'value'));

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function hsliderYaw_CreateFcn(hObject, ~, handles)
% hObject    handle to hsliderYaw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



% --- Executes on slider movement.
function hsliderHeight_Callback(hObject, ~, handles)
% hObject    handle to hsliderHeight (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.hetextHeightDes,'String',get(hObject,'value'));
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function hsliderHeight_CreateFcn(hObject, ~, handles)
% hObject    handle to hsliderHeight (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



function hetextRollDes_Callback(hObject, ~, handles)
% hObject    handle to hetextRollDes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.hsliderRoll,'Value',str2double(get(hObject,'String')));
% Hints: get(hObject,'String') returns contents of hetextRollDes as text
%        str2double(get(hObject,'String')) returns contents of hetextRollDes as a double


% --- Executes during object creation, after setting all properties.
function hetextRollDes_CreateFcn(hObject, ~, handles)
% hObject    handle to hetextRollDes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function hetextPitchDes_Callback(hObject, ~, handles)
% hObject    handle to hetextPitchDes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.hsliderPitch,'Value',str2double(get(hObject,'String')));
% Hints: get(hObject,'String') returns contents of hetextPitchDes as text
%        str2double(get(hObject,'String')) returns contents of hetextPitchDes as a double


% --- Executes during object creation, after setting all properties.
function hetextPitchDes_CreateFcn(hObject, ~, handles)
% hObject    handle to hetextPitchDes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function hetextYawDes_Callback(hObject, ~, handles)
% hObject    handle to hetextYawDes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.hsliderYaw,'Value',str2double(get(hObject,'String')));
% Hints: get(hObject,'String') returns contents of hetextYawDes as text
%        str2double(get(hObject,'String')) returns contents of hetextYawDes as a double


% --- Executes during object creation, after setting all properties.
function hetextYawDes_CreateFcn(hObject, ~, handles)
% hObject    handle to hetextYawDes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function hetextHeightDes_Callback(hObject, ~, handles)
% hObject    handle to hetextHeightDes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.hsliderHeight,'Value',str2double(get(hObject,'String')));
% Hints: get(hObject,'String') returns contents of hetextHeightDes as text
%        str2double(get(hObject,'String')) returns contents of hetextHeightDes as a double


% --- Executes during object creation, after setting all properties.
function hetextHeightDes_CreateFcn(hObject, ~, handles)
% hObject    handle to hetextHeightDes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
