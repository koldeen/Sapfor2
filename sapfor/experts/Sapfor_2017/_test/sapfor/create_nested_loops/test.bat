setlocal
rmdir /s /q sapfor_out
SET PARSER_EXEC=..\..\..\_bin\x64\Debug\Parser.exe
SET SAPFOR_EXEC=..\..\..\_bin\x64\Debug\Sapfor.exe
%PARSER_EXEC% program.f90
if not exist "sapfor_out" mkdir sapfor_out
%SAPFOR_EXEC% -pass 3 -F sapfor_out -print
FC /w program.expected.f90 sapfor_out/program.f90
