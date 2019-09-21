function varargout = DrawShapes(varargin)
% DRAWSHAPES MATLAB code for DrawShapes.fig
%      DRAWSHAPES, by itself, creates a new DRAWSHAPES or raises the existing
%      singleton*.
%
%      H = DRAWSHAPES returns the handle to a new DRAWSHAPES or the handle to
%      the existing singleton*.
%
%      DRAWSHAPES('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DRAWSHAPES.M with the given input arguments.
%
%      DRAWSHAPES('Property','Value',...) creates a new DRAWSHAPES or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before DrawShapes_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to DrawShapes_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help DrawShapes

% Last Modified by GUIDE v2.5 25-Oct-2018 12:46:00

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @DrawShapes_OpeningFcn, ...
                   'gui_OutputFcn',  @DrawShapes_OutputFcn, ...
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


% --- Executes just before DrawShapes is made visible.
function DrawShapes_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to DrawShapes (see VARARGIN)
DrawGrapgh(hObject, eventdata, handles)
set (handles.Send,'Enable','OFF') ;
global flagLine    ;
global flagRect    ; 
global flagMulti   ;
flagLine   = 0  ;
flagRect   = 0  ; 
flagMulti  = 0  ;



% Choose default command line output for DrawShapes
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes DrawShapes wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = DrawShapes_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in DrawLine.
function DrawLine_Callback(hObject, eventdata, handles)
global h ;
global flagLine   ;
global LineLength ;
set (handles.Send,'Enable','ON') ;
% hObject    handle to DrawLine (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
DrawGrapgh(hObject, eventdata, handles)
h = imline ; 
pos = getPosition(h) ; 
LineLength = pdist(pos,'euclidean');
LineLength= round (LineLength) ;
if (LineLength<= 0.02)
    %repeat the line again
    m = msgbox('Error');
    DrawGrapgh(hObject, eventdata, handles)
else
    set (handles.edit2,"string", LineLength);
    flagLine = 1 ;
    set (handles.Send,'Enable','ON') ;
    if  (abs(pos(1,2)-pos(2,2)) < 0.9 )
        LineLength = LineLength + 110 ; %LINE IS Horizontal 
        set (handles.edit2,"string", LineLength);
    else 
        LineLength = LineLength + 120 ; %LINE IS Vertical
        set (handles.edit2,"string", LineLength);
    end
        

end

%%el mafrood hnsend LineLength 

% --- Executes on button press in Draw_Rectangle.
function Draw_Rectangle_Callback(hObject, eventdata, handles)
global flagRect   ; 
flagRect = 1 ;
global RecEndValue;
DrawGrapgh(hObject, eventdata, handles)
h = imrect ;
setColor(h,'black');
pos = getPosition(h) ; 
ShapeLength = round (pos(4)) ;
ShapeWidth= round (pos(3)) ;
RecEndValue = (ShapeLength*10)+(ShapeWidth);
if (ShapeLength <= 0.02 || ShapeWidth <= 0.02)
    %repeat the line again
    m = msgbox('Error');
    DrawGrapgh(hObject, eventdata, handles)
else
    set (handles.edit4,"string",ShapeLength);
    set (handles.edit3,"string",ShapeWidth);
end
flagRect = 1 ;
set (handles.Send,'Enable','ON') ;

%%el mafrood hnsend ShapeLength w ShapeWidth

% hObject    handle to Draw_Rectangle (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)




function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in DrawMultiLines.
function DrawMultiLines_Callback(hObject, eventdata, handles)
global flagMulti
% hObject    handle to DrawMultiLines (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
DrawGrapgh(hObject, eventdata, handles)
flag = get(handles.DrawMultiLines,'Value');
i = 1 ;
 while (flag && i <= 2)
     set(handles.DrawMultiLines,'string','Stop...');
     MultiLine(hObject, eventdata, handles) ;
     hold on ;
     i = i+1 ;
     flag = get(handles.DrawMultiLines,'value');
     if flag == 0
     set(handles.DrawMultiLines,'string','Draw MultiLines...');
     end
 end
 if i == 3 
     i = 1 ;
     flagMulti = 1 ;
     set (handles.Send,'Enable','ON') ;
 end
 set(handles.DrawMultiLines,'string','Draw MultiLines...');

 

 
 
 
 
 
 
 
function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double
% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function edit3_Callback(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of edit3 as text
%        str2double(get(hObject,'String')) returns contents of edit3 as a double
% --- Executes during object creation, after setting all properties.
function edit3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function edit4_Callback(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA
% Hints: get(hObject,'String') returns contents of edit4 as text
%        str2double(get(hObject,'String')) returns contents of edit4 as a double
% --- Executes during object creation, after setting all properties.
function edit4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function edit5_Callback(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of edit5 as text
%        str2double(get(hObject,'String')) returns contents of edit5 as a double
% --- Executes during object creation, after setting all properties.
function edit5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function DrawGrapgh(hObject, eventdata, handles)
cla(handles.axes1,'reset')
axes(handles.axes1)
axis([0 8 0 8]) ;
grid on ;

function Lines = MultiLine(hObject, eventdata, handles)
Lines = imline ; 



% --- Executes on button press in Send.
function Send_Callback(hObject, eventdata, handles)
global flagLine   ;
global flagRect   ; 
global flagMulti  ;
global LineLength;
global RecEndValue;

% hObject    handle to Send (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if (flagLine == 1)
    flagLine = 0 ;
    s = serial('COM11');
    fopen(s);
    pause(2);
    fwrite(s,LineLength,'uint8');
    
    
    fclose(s);
    % send Lenght & H/V
elseif (flagRect == 1)
    flagRect = 0 ;
     s = serial('COM11');
    fopen(s);
    pause(2);
    fwrite(s,RecEndValue,'uint8');
    fclose(s);
    
   elseif (flagMulti == 1)
    flagMulti = 0 ;
     s = serial('COM11');
    fopen(s);
    pause(2);
    fwrite(s,200,'uint8');
    fclose(s);
    
        %send L&W
end