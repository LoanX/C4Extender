@echo off
ml64.exe /c /Cx  /nologo /Fo"x64\Debug\level_up.asm.obj" /W3 /Zi /errorReport:prompt  /Ta".\level_up.asm"
if errorlevel 1 goto VCReportError
goto VCEnd
:VCReportError
echo Project : error PRJ0019: A tool returned an error code from "Assembling..."
exit 1
:VCEnd