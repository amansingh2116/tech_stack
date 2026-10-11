The Remote-Hire Playbook - LaTeX Source & Build Guide
======================================================

Files:
  main.tex            - Master document: preamble, custom callout boxes, \input list
  main.pdf            - Compiled 55-page field manual PDF
  README.md           - Full markdown documentation & component breakdown
  README.txt          - Plaintext build instructions
  sections/*.tex      - One modular file per chapter (numbered in build order)

HOW TO COMPILE:
----------------
Option 1 (Recommended - handles all passes and references automatically):
  latexmk -pdf main.tex

Option 2 (Live watch mode - auto-recompiles whenever you edit & save):
  latexmk -pvc -pdf main.tex

Option 3 (Direct pdflatex - requires 2 passes for table of contents & refs):
  pdflatex -interaction=nonstopmode main.tex
  pdflatex -interaction=nonstopmode main.tex

HOW TO CLEAN TEMPORARY FILES:
-----------------------------
To remove auxiliary build files (.aux, .log, .toc, .fls, etc.) without deleting main.pdf:
  latexmk -c
  (or in PowerShell: Remove-Item main.aux, main.log, main.toc -ErrorAction SilentlyContinue)

CUSTOM CALLOUT BOXES:
---------------------
Defined in main.tex:
  \begin{keytakeaway} ... \end{keytakeaway}  (Teal/Green box for core rules)
  \begin{caution} ... \end{caution}          (Red box for reality checks/warnings)
  \begin{template} ... \end{template}        (Slate Blue box, monospace for templates)
  \begin{example} ... \end{example}          (Light Gray box for case studies)
  \good / \bad                               (Green checkmark / red cross dingbats)

PREREQUISITES:
--------------
Standard TeX distribution (e.g. MiKTeX, TeX Live). Uses standard packages:
geometry, tcolorbox, longtable, booktabs, colortbl, fancyhdr, hyperref, bookmark, tikz.
