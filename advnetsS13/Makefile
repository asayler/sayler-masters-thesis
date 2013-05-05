REPORT=custos_advnetsS13
LATEX=pdflatex
BIBTEX=bibtex --min-crossrefs=1000
REF1=ref

TEX = $(wildcard *.tex)
CLS = $(wildcard *.cls)
SRCS = $(TEX)
REFS=$(REF1).bib 

all: pdf

pdf: $(SRCS) $(CLS)
	$(LATEX) $(REPORT)
	$(BIBTEX) $(REPORT)
	$(LATEX) $(REPORT)
	$(LATEX) $(REPORT)

clean: 
	$(RM) *.dvi *.aux *.log *.blg *.bbl *.out
	$(RM) *~
