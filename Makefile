REPORT=masters
LATEX=pdflatex
BIBTEX=bibtex --min-crossrefs=1000
REF1=refs

CLS = $(wildcard *.cls)
TEX = $(wildcard *.tex)
REFS = $(REF1).bib
SRCS = $(TEX) $(REFS)

all: pdf

pdf: $(SRCS) $(CLS)
	$(LATEX) $(REPORT)
	$(BIBTEX) $(REPORT)
	$(LATEX) $(REPORT)
	$(LATEX) $(REPORT)

clean:
	$(RM) *.dvi *.aux *.log *.blg *.bbl *.out *.lof *.lot *.toc
	$(RM) *~
