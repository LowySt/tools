@echo off

SET VC_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community
IF NOT DEFINED LIB (IF EXIST "%VC_PATH%" (call "%VC_PATH%\VC\Auxiliary\Build\vcvarsall.bat" amd64))

SET ARG=%1

IF "%ARG%"=="release" (
echo Release_Build
SET DEPLOY=-O2
SET NAME=Release_Test
)
IF "%ARG%"=="debug" (
echo Debug_Build 
SET DEPLOY=-Od 
SET NAME=Debug_Test
)

SET OPTS= %DEPLOY% -I F:\ProgrammingProjects\AddIncludes\PlatformAndTools\ -FC -GR- -EHa- -nologo -Zi

SET LIBS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib Opengl32.lib

SET CODE_HOME=%cd%
pushd out
cl %OPTS% %CODE_HOME%\main_test.cpp -Fe%NAME% %LIBS%
del *.ilk
del *.obj
popd
