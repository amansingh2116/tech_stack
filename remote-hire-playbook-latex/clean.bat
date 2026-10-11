@echo off
echo Cleaning LaTeX temporary auxiliary files...
latexmk -c
echo Auxiliary files removed. main.pdf preserved.
