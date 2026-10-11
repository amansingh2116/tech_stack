# The Remote-Hire Playbook — LaTeX Edition

A comprehensive, production-grade guide on technical judgment, end-to-end ML engineering, open-source proof-of-work, personal branding, cold email outreach engineering, and international contractor logistics for landing high-paying remote US/European startup roles.

Compiled for **Aman Singh** (*B.Stat Hons., Indian Statistical Institute, Kolkata*).

**Current Document Stats:** **88 pages** • **18 chapters** • Beautiful custom `tcolorbox` typography & tables.

---

## 📖 PDF Output

- **Primary Compiled PDF:** [`main.pdf`](main.pdf) (88 pages, ~843 KB)
- **Master TeX File:** [`main.tex`](main.tex)

---

## 🚀 Quick Start: Building & Viewing the PDF

To compile `main.tex` into `main.pdf`, run one of the following commands from the `remote-hire-playbook-latex` directory:

### Option 1: Automated Script (Windows)
```cmd
.\build.bat
```
Runs `latexmk -pdf main.tex` to perform the exact number of passes needed to resolve citations, hyperlinks, and the multi-page table of contents.

To clean up intermediate files afterwards:
```cmd
.\clean.bat
```

### Option 2: Automated Build with `latexmk`
```bash
latexmk -pdf main.tex
```

### Option 3: Continuous Watch Mode (Auto-Recompile on Save)
To automatically recompile the PDF in the background whenever you edit and save any `.tex` file in `sections/` or `main.tex`:
```bash
latexmk -pvc -pdf main.tex
```
*(Press `Ctrl + C` in the terminal to exit watch mode).*

### Option 4: Manual Compilation with `pdflatex`
If using `pdflatex` directly, execute two consecutive passes so that cross-references and the table of contents settle accurately:
```bash
pdflatex -interaction=nonstopmode main.tex
pdflatex -interaction=nonstopmode main.tex
```

---

## 🧹 Cleaning Build Artifacts

To remove auxiliary temporary files (`.aux`, `.log`, `.toc`, `.fls`, `.fdb_latexmk`, `.out`) while keeping the compiled `main.pdf`:

```bash
# Using latexmk:
latexmk -c

# Or using the provided batch file:
.\clean.bat
```

---

## 📂 Repository Structure & Chapter Directory

```
remote-hire-playbook-latex/
│
├── main.tex                         # Master LaTeX file: preamble, fonts, colors, custom boxes, \input list
├── main.pdf                         # Output compiled 88-page publication PDF
├── build.bat                        # One-click Windows build script (latexmk)
├── clean.bat                        # One-click auxiliary file cleaner (latexmk -c)
├── README.md                        # Complete documentation & chapter outline
├── README.txt                       # Plaintext quick reference & cross-referencing notes
│
└── sections/                        # Modular chapter files (auto-numbered via \input order)
    ├── 00-titlepage.tex             # Cover page, author attribution & usage notice
    ├── 00-toc.tex                   # Automated 4-page table of contents
    ├── 01-foundations.tex           # Part 1: The Mindset Shift (AI era judgment, cultural gaps, 4 shifts)
    ├── 02-outreach-engineering.tex  # Part 2: The Outreach Engineering Framework (Equation & 3 trust multipliers)
    ├── 03-production-projects-a.tex # Part 3: Building Production-Grade Projects (Problem selection & data strategy)
    ├── 04-production-projects-b.tex # Part 4: From Experiment to Deployed System (Drift monitoring & serving)
    ├── 05-production-projects-c.tex # Part 5: Documentation & The Demo That Gets Callbacks (Walkthroughs & READMEs)
    ├── 06-open-source-contributions.tex # Part 6: Open-Source Contributions as Proof-of-Work (Repeatable units & objections)
    ├── 07-linkedin-branding.tex     # Part 7: Personal Branding: Positioning & LinkedIn (Headlines & 30-day plan)
    ├── 08-direct-outreach.tex       # Part 8: Direct Outreach to Startup Founders (4-step model & 48h prototypes)
    ├── 09-cold-email-principles.tex  # Part 9: Cold-Email Principles (Deliverability, warmup, copywriting psychology)
    ├── 10-cold-email-templates.tex   # Part 10: Cold-Email Templates by Audience (Founders, CTOs, engineers, recruiters)
    ├── 11-sourcing-tools.tex        # Part 11: Sourcing Tools and AI-Assisted Search (Apollo, Clay, Crunchbase, Boolean)
    ├── 12-case-study-1200-emails.tex# Part 12: Case Study: Scaling to 1,200+ Cold Emails (Funnel data, conversion analysis)
    ├── 13-beyond-job-postings.tex   # Part 13: Finding Opportunities Beyond Job Postings (Stealth hiring & unadvertised roles)
    ├── 14-getting-paid.tex          # Part 14: Getting Paid: EOR, Contracting, W-8BEN & GST (Invoicing & compliance)
    ├── 15-roadmap.tex               # Part 15: The 16-Week Implementation Roadmap (Week-by-week execution schedule)
    ├── 16-evaluating-programs.tex   # Part 16: Evaluating the Paid Programs, Critically (ROI vs free alternatives)
    ├── 17-checklists.tex            # Part 17: Final Checklists & Quick Reference (Pre-flight audits & funnel metrics)
    └── 18-appendix.tex              # Part 18: Appendix: Reference Material (15 fatal ML mistakes, templates, interview bank)
```

---

## 📑 Detailed Chapter Overview

| Part | Chapter | Key Topics & Deliverables |
| :---: | :--- | :--- |
| **01** | **The Mindset Shift** | Why standard applications fail; the shift from student to engineer; AI judgment over syntax; addressing 5 cultural and behavioral gaps. |
| **02** | **The Outreach Engineering Framework** | The Outreach Equation; why distribution beats raw skill; the 3 trust multipliers; 10-minute activation exercise. |
| **03** | **Production Projects: Problem & Data** | Why toy projects get rejected; selecting defensible business problems; data ingestion pipelines; data validation with Great Expectations. |
| **04** | **From Experiment to Deployed System** | Experiment tracking with MLflow/W&B; FastAPI inference engines; Docker containerization; data/concept drift monitoring (Evidently AI). |
| **05** | **Documentation & High-Impact Demos** | The 5-second README hook; interactive Streamlit/Gradio web apps; Loom video walkthrough scripts; deployment on Hugging Face Spaces/Render. |
| **06** | **Open-Source as Proof-of-Work** | The Repeatable-Unit Principle; finding good first issues; getting PRs merged in production repos; overcoming the 3 objections to hiring from India. |
| **07** | **Personal Branding & LinkedIn** | Positioning yourself as a specialized product; headline formulas; 5-block About section; 3-slot Featured section; 30-day content calendar. |
| **08** | **Direct Outreach to Founders** | The 4-step outreach model; identifying recently funded startups; building 48-hour customized prototypes; reciprocity and small CTAs. |
| **09** | **Cold-Email Principles** | Technical email deliverability; secondary domain setup and warmup; subject line psychology; 75–125 word brevity rules; follow-up cadences. |
| **10** | **Cold-Email Templates by Audience** | Tailored copy for non-technical Founders, technical CTOs/VPs of Eng, Staff Engineers, and in-house Talent Leads. |
| **11** | **Sourcing Tools & AI Search** | Systematic lead finding with Apollo.io, Clay, Crunchbase, Wellfound, GitHub search queries, and Boolean Google operators. |
| **12** | **Case Study: 1,200+ Cold Emails** | Real-world campaign breakdown: niche selection, sending infrastructure, reply and interview conversion rates, two contrasting lead teardowns. |
| **13** | **Beyond Job Postings** | Sourcing opportunities before they hit public boards; monitoring funding rounds, engineering blog teardowns, and Twitter/X tech conversations. |
| **14** | **Getting Paid: Legal & Tax Setup** | Employer of Record (EOR) vs Independent Contractor; W-8BEN filing; Wise/Payoneer/SWIFT wire setups; India GST registration & Letter of Undertaking (LUT) for zero-rated export of services. |
| **15** | **16-Week Implementation Roadmap** | Phased progression from foundational project builds to open-source contributions, audience sourcing, and active outreach pipelines. |
| **16** | **Evaluating Paid Cohorts Critically** | Objective evaluation of expensive training programs; separating genuine value from vanity credentials; high-leverage free alternatives. |
| **17** | **Final Checklists & Quick Reference** | Pre-flight outreach audit; production project checklist; weekly funnel metric tracking dashboard. |
| **18** | **Appendix & Reference Material** | 15 fatal ML engineering mistakes and their fixes; 3 production project starter blueprints; comprehensive technical interview question bank. |

---

## 🎨 Design System & Custom Environments

The document features a modern custom design system built with `tcolorbox`, `titlesec`, and `xcolor`:

| Environment | Primary Color | Purpose |
| :--- | :--- | :--- |
| `\begin{keytakeaway} ... \end{keytakeaway}` | Teal (`#0F766E`) | Core architectural rules, mental models, and principles |
| `\begin{caution} ... \end{caution}` | Crimson Red (`#C0392B`) | Traps, deliverability warnings, and common failure modes |
| `\begin{template} ... \end{template}` | Monospace Slate (`#3B5BA9`) | Ready-to-adapt cold email and LinkedIn message templates |
| `\begin{example} ... \end{example}` | Light Slate (`#F4F6F8`) | Concrete case studies, real snippets, and detailed teardowns |

### Quick Symbols
- `\good` — Renders a green checkmark (\ding{51})
- `\bad` — Renders a red cross (\ding{55})

---

## ⚙️ Prerequisites & Package Requirements

- **TeX Distribution:** MiKTeX (with auto-install enabled) or TeX Live 2022+.
- **Standard LaTeX Packages Used:** `geometry`, `titlesec`, `titletoc`, `tcolorbox`, `longtable`, `booktabs`, `colortbl`, `fancyhdr`, `hyperref`, `bookmark`, `tikz`, `pifont`, `amsmath`, `amssymb`, `parskip`, `multicol`.
