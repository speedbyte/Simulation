set MATLAB=C:\Programme\R2009b
set MSVCDir=c:\programme\microsoft visual studio 9.0\VC

"C:\Programme\R2009b\rtw\bin\win32\envcheck" INCLUDE "c:\programme\microsoft visual studio 9.0\VC\include"
if errorlevel 1 goto vcvars32
"C:\Programme\R2009b\rtw\bin\win32\envcheck" PATH "c:\programme\microsoft visual studio 9.0\VC\bin"
if errorlevel 1 goto vcvars32
goto make

:vcvars32
set VSINSTALLDIR=c:\programme\microsoft visual studio 9.0
set VCINSTALLDIR=c:\programme\microsoft visual studio 9.0\VC
set FrameworkSDKDir=c:\programme\microsoft visual studio 9.0\SDK\v3.5
call "C:\Programme\R2009b\toolbox\rtw\rtw\private\vcvars32_900.bat"

:make
cd .
nmake -f controller.mk  GENERATE_REPORT=0
@if errorlevel 1 goto error_exit
exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
An_error_occurred_during_the_call_to_make
