# The Remote-Hire Playbook — LaTeX Edition

A comprehensive, production-grade guide on technical judgment, end-to-end ML engineering, personal branding, and engineered direct outreach for high-paying remote US/European startup roles.

Compiled for **Aman Singh** (*B.Stat Hons., Indian Statistical Institute, Kolkata*).

---

## Quick Start: Building the PDF

To compile `main.tex` into `main.pdf`, run one of the following commands from the `remote-hire-playbook-latex` directory:

### Option 1: Automated Build with `latexmk` (Recommended)
`latexmk` automatically manages the required number of compilation passes so that the Table of Contents, hyperlinks, and cross-references resolve cleanly:

```bash
latexmk -pdf main.tex
```

### Option 2: Live Watch Mode (Auto-Recompile on Edit)
To automatically recompile the PDF in the background whenever you edit and save any `.tex` file in `sections/` or `main.tex`:

```bash
latexmk -pvc -pdf main.tex
```
*(Press `Ctrl + C` in the terminal to exit watch mode).*

### Option 3: Manual Compilation with `pdflatex`
If using `pdflatex` directly, execute two consecutive passes so that cross-references and the 3-page table of contents settle accurately:

```bash
pdflatex -interaction=nonstopmode main.tex
pdflatex -interaction=nonstopmode main.tex
```

---

## Cleaning Build Artifacts

To remove auxiliary temporary files (`.aux`, `.log`, `.toc`, `.fls`, `.fdb_latexmk`) while preserving the compiled `main.pdf`:

```bash
# Using latexmk:
latexmk -c

# Or using PowerShell:
Remove-Item main.aux, main.log, main.toc -ErrorAction SilentlyContinue
```

---

## Repository Structure

```
remote-hire-playbook-latex/
│
├── main.tex                    # Master document: preamble, custom environments, styling & \input list
├── main.pdf                    # Output compiled 55-page PDF document
├── README.md                   # Complete documentation & build guide
├── README.txt                  # Plaintext quick reference
│
└── sections/                   # Modular chapter files (built in numerical order)
    ├── 00-titlepage.tex        # Cover page and usage guide
    ├── 00-toc.tex              # Table of contents generator
    ├── 01-foundations.tex      # Part 1: The Mindset Shift & AI Era Judgment
    ├── 02-outreach-engineering.tex # Part 2: The Outreach Engineering Equation & Multipliers
    ├── 03-production-projects-a.tex # Part 3: Problem Selection & Data Strategy
    ├── 04-production-projects-b.tex # Part 4: Experimentation, Deployment & Drift Monitoring
    ├── 05-production-projects-c.tex # Part 5: README Structure & Interactive Demos
    ├── 06-linkedin-branding.tex    # Part 6: Personal Branding, Headline Formulas & 30-Day Plan
    ├── 07-direct-outreach.tex      # Part 7: Sourcing Funded Startups & 48h Prototypes
    ├── 08-beyond-job-postings.tex  # Part 8: Creating Your Own Opening
    ├── 09-roadmap.tex              # Part 9: 16-Week Implementation Roadmap
    ├── 10-evaluating-programs.tex  # Part 10: Critical Evaluation of Paid Cohorts
    ├── 11-checklists.tex           # Part 11: Master Implementation Checklist & Metrics Dashboard
    └── 12-appendix.tex             # Part 12: 15 Fatal ML Mistakes, 3 Project Templates & Interview Bank
```

---

## Custom Styling & Callout Environments

The document defines several custom `tcolorbox` callout styles in `main.tex`:

| Environment | Accent Color | Visual Purpose |
| :--- | :--- | :--- |
| `\begin{keytakeaway} ... \end{keytakeaway}` | Teal (`#0F766E`) | Core principles and essential rules |
| `\begin{caution} ... \end{caution}` | Red (`#C0392B`) | Reality checks, critical caveats, and risk warnings |
| `\begin{template} ... \end{template}` | Slate Blue (`#3B5BA9`) | Copy-paste outreach messages and scripts (monospace) |
| `\begin{example} ... \end{example}` | Slate Gray (`#F4F6F8`) | Concrete illustrative case studies and walkthroughs |

### Quick Symbols
- `\good` — Renders a green checkmark (\ding{51})
- `\bad` — Renders a red cross (\ding{55})

---

## Prerequisites & Packages

- **TeX Engine:** MiKTeX (with auto-package-installer enabled) or TeX Live.
- **Key LaTeX Packages:** `geometry`, `titlesec`, `titletoc`, `tcolorbox`, `longtable`, `booktabs`, `colortbl`, `fancyhdr`, `hyperref`, `bookmark`, `tikz`, `pifont`, `amsmath`, `amssymb`.
