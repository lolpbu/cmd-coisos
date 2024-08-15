@ECHO OFF
SETLOCAL

SET EXE="coiso.exe"
SET SRCDIR="."
SET INCDIR="include"
SET BINDIR="out"
SET EXT="cpp"
SET CC="g++"
SET OBJS="%BINDIR%/*.o"

IF "%1"=="create" GOTO :CREATE 
IF "%1"=="clean" GOTO :CLEAN
IF "%1"=="help" GOTO :HELP
IF "%1"=="file" GOTO :FILE
GOTO :MAKE 



:HELP
ECHO make        -^> compile
ECHO make run    -^> compile ^& run
ECHO make create -^> create bin, src ^& include dirs
ECHO make clean  -^> clean bin dir
ECHO make help   -^> ...
GOTO :EOF



:MAKE 
REM /p = path to search
REM /m = search mask (* wildcard)
REM /s = recurse into subfolders
REM /c = command to each file found 
FORFILES /P %SRCDIR% /M *.%EXT% /S /C "CMD /C ECHO compilando arquivo @file && %CC% -I %INCDIR% -c @relpath -o %BINDIR%\\@FNAME.o"
ECHO linkando arquivos em %EXE%
%CC% %OBJS% -o %EXE%
ECHO pronto :3

IF "%1"=="run" (
    CLS
    %EXE%
)

GOTO :EOF



:FILE
REM compilando arquivo %2
REM %CC% -I %INCDIR% -c %2 -o %BINDIR%\%2
FORFILES /P %SRCDIR% /M %2 /S /C "CMD /C ECHO compilando arquivo @file && %CC% -I %INCDIR% -c @relpath -o %BINDIR%\\@FNAME.o"
ECHO linkando arquivos em %EXE%
%CC% %OBJS% -o %EXE%
ECHO pronto :3
GOTO :EOF


:CREATE
MKDIR %INCDIR% %BINDIR% %SRCDIR%
GOTO :EOF



:CLEAN
DEL /Q /S *.o *.exe %BINDIR%\*



:EOF
ENDLOCAL