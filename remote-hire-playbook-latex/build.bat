@echo off
echo ========================================================
echo Building The Remote-Hire Playbook PDF
echo ========================================================
latexmk -pdf main.tex
if %ERRORLEVEL% EQU 0 (
    echo.
    echo [SUCCESS] PDF successfully built: main.pdf
) else (
    echo.
    echo [ERROR] Build encountered errors. Please check above logs.
)
