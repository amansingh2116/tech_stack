The Remote-Hire Playbook - LaTeX source
=========================================

Files:
  main.tex           - preamble, colors, custom boxes, \input list (controls chapter order)
  sections/*.tex      - one file per chapter

Current chapter order (see the \input list in main.tex to reorder):
  01-foundations                   - Part 1: The Mindset Shift
  02-outreach-engineering          - Part 2: The Outreach Engineering Framework
  03/04/05-production-projects-*   - Part 3-5: Building Production-Grade Projects
  06-open-source-contributions     - Part 6: Open-Source Contributions as Proof-of-Work
  07-linkedin-branding             - Part 7: Personal Branding & LinkedIn
  08-direct-outreach               - Part 8: Direct Outreach to Startup Founders
  09-cold-email-principles         - Part 9: Cold-Email Principles
  10-cold-email-templates          - Part 10: Cold-Email Templates by Audience
  11-sourcing-tools                - Part 11: Sourcing Tools and AI-Assisted Search
  12-case-study-1200-emails        - Part 12: Case Study - Scaling to 1,200+ Cold Emails
  13-beyond-job-postings           - Part 13: Finding Opportunities Beyond Job Postings
  14-getting-paid                  - Part 14: Getting Paid (EOR, W-8BEN, GST)
  15-roadmap                       - Part 15: The 16-Week Implementation Roadmap
  16-evaluating-programs           - Part 16: Evaluating the Paid Programs, Critically
  17-checklists                    - Part 17: Final Checklists & Quick Reference
  18-appendix                      - Part 18: Appendix (mistakes, templates, interview prep,
                                      template library, resource links, tool directory)

Note: file name numbers don't need to match chapter numbers exactly (LaTeX auto-numbers
chapters from the \input order in main.tex) - they're just kept roughly in sync for your
own navigation.

To compile (requires a TeX distribution, e.g. TeX Live, with pdflatex):
  pdflatex main.tex
  pdflatex main.tex    (run a second time so the table of contents and
                         cross-references resolve correctly)

The output is main.pdf.

Notes:
- Custom environments defined in main.tex: keytakeaway (green), caution
  (red), template (blue, monospace), example (grey) - use these for any
  new callout boxes you add.
- Every cross-reference uses \label{} / \ref{} (e.g. \ref{ch:open-source}), not
  hardcoded chapter numbers - so you can freely reorder, insert, or delete chapters
  in the \input list and every reference throughout the document updates automatically
  on the next compile. Just give any new chapter a unique \label{ch:your-label} right
  after its \chapter{} line.
- Known gotcha: a line ending in "\\" immediately followed by a line starting with "["
  (e.g. a template's sign-off "Best,\\" then "[Your Name]") gets misparsed by LaTeX as
  \\[optional-spacing]. Fix: write "\\{}" instead of "\\" on that line.
- Uses only standard packages (geometry, tcolorbox, longtable, hyperref,
  titlesec, etc.) - no custom fonts beyond default Computer Modern, so it
  should compile on any reasonably current TeX Live/MikTeX install without
  extra package downloads.
