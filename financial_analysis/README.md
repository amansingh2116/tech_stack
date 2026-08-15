# Financial Analysis & Modeling: Course Notes & Documentation

This directory contains comprehensive course notes, professional reference handbooks, LaTeX source files, and rendered PDF documents covering **Financial Analytics, Accounting Fundamentals, Business Analysis, Time Value of Money (TVM), Excel Modeling, and Valuation**.

---

## Directory Structure

```text
financial_analysis/
├── introduction.md                 # Markdown summary notes for the course introduction
├── README.md                       # Local rendering guide & project documentation (this file)
├── tex/                            # LaTeX source files (.tex)
│   ├── introduction.tex            # Introduction & foundations handbook
│   ├── excel_module1_foundations.tex # Module 1: Interface, formatting, formulas & shortcuts
│   ├── excel_module2_professionals.tex # Module 2: Macros, references, data validation & auditing
│   └── excel_module3_pro.tex       # Module 3: Advanced lookup, logical, financial & error functions
└── pdf/                            # Compiled publication-quality PDF documents
    ├── introduction.pdf
    ├── excel_module1_foundations.pdf
    ├── excel_module2_professionals.pdf
    └── excel_module3_pro.pdf
```

---

## Why Are There Intermediate Files During Compilation?

When compiling LaTeX documents using engines like `pdflatex` or `xelatex`, the compiler performs multiple passes to resolve references, tables of contents, and hyperlinks. This process produces temporary auxiliary files:

| File Extension | File Type | Purpose |
| :--- | :--- | :--- |
| `.aux` | **Auxiliary File** | Stores cross-referencing data (`\label`, `\ref`, `\cite`) and section numbering. |
| `.toc` | **Table of Contents** | Stores section headers and page numbers extracted during the first pass to render `\tableofcontents`. |
| `.out` | **Hyperref Outline** | Generates clickable PDF bookmark trees and document outlines. |
| `.log` | **Compiler Log** | Detailed log of packages loaded, font metrics, box warnings, and error messages. |
| `.synctex.gz` | **SyncTeX Data** | Enables bi-directional sync between editor code and PDF viewer. |

### Keeping the Repository Clean (`.gitignore`)
These auxiliary files are temporary build artifacts and should **not** be committed to Git. The root [`.gitignore`](file:///c:/Users/amans/OneDrive/Documents/GitHub/tech_stack/.gitignore) file automatically excludes all `*.aux`, `*.log`, `*.out`, `*.toc`, and `*.synctex*` files, ensuring only the source `.tex` and final `.pdf` files are tracked.

---

## How to Render PDFs Locally

### Prerequisites
Make sure you have a LaTeX distribution installed on your machine:
- **Windows:** [MiKTeX](https://miktex.org/) (installed) or [TeX Live](https://www.tug.org/texlive/)
- **macOS:** [MacTeX](https://www.tug.org/mactex/)
- **Linux:** `sudo apt install texlive-latex-extra texlive-fonts-recommended`

Verify installation:
```bash
pdflatex --version
```

---

### Method 1: Render a Single Document (Command Line)

Navigate to the `financial_analysis/tex` directory and run `pdflatex` specifying the `pdf` folder as the output target:

```powershell
# 1. Navigate to tex directory
cd financial_analysis/tex

# 2. Compile document (run twice for TOC and references to resolve)
pdflatex -interaction=nonstopmode -output-directory="../pdf" introduction.tex
pdflatex -interaction=nonstopmode -output-directory="../pdf" introduction.tex

# 3. Clean up intermediate auxiliary files from the pdf folder
Get-ChildItem -Path "../pdf" -Exclude "*.pdf" | Remove-Item
```

---

### Method 2: Batch Render All Documents (PowerShell One-Liner)

To compile all `.tex` files in `tex/` to `pdf/` and clean up auxiliary files in one step, run this command from the repository root:

```powershell
Get-ChildItem -Path "financial_analysis/tex/*.tex" | ForEach-Object {
    Write-Host "Compiling $($_.Name)..." -ForegroundColor Cyan
    pdflatex -interaction=nonstopmode -output-directory="financial_analysis/pdf" $_.FullName
    pdflatex -interaction=nonstopmode -output-directory="financial_analysis/pdf" $_.FullName
}
Get-ChildItem -Path "financial_analysis/pdf" -Exclude "*.pdf" | Remove-Item
Write-Host "All PDFs successfully rendered to financial_analysis/pdf!" -ForegroundColor Green
```

---

### Method 3: Using `latexmk` (Automated Multi-Pass & Cleanup)

If `latexmk` (Perl-based automated builder) is installed:

```bash
cd financial_analysis/tex
latexmk -pdf -outdir=../pdf -interaction=nonstopmode introduction.tex
latexmk -c -outdir=../pdf  # Cleans auxiliary files, leaving only PDF
```

---

### Method 4: Visual Studio Code (`LaTeX Workshop` Extension)

1. Install the **LaTeX Workshop** extension in VS Code.
2. In VS Code settings (`settings.json`), configure the build output directory:
   ```json
   "latex-workshop.latex.outDir": "%DIR%/../pdf",
   "latex-workshop.latex.autoClean.run": "onBuilt"
   ```
3. Open any `.tex` file in `financial_analysis/tex/` and press `Ctrl + Alt + B` (or `Cmd + Option + B` on macOS) to build.
