REPORT=masters
LATEX=pdflatex
BIBTEX=bibtex
REF1=refs

CLS = $(wildcard *.cls)
TEX = $(wildcard *.tex)
REFS = $(REF1).bib
SRCS = $(TEX) $(REFS)

FIG_TMP = tmp.eps
FIGS = $(patsubst %, figs/out/%.pdf, \
         App-DC-Custos \
         App-DC-Traditional \
         App-FS-Custos-Integrated \
         App-FS-Custos-Layered \
         App-FS-Fuse \
         App-FS-Traditional-Integrated \
         App-FS-Traditional-Layered \
         App-Mgmt \
         App-SS \
         Arch-ACS \
         Arch-KeyRequest-All \
         Arch-OU \
         Arch-Overview \
         Arch-Sharded \
         SecuityToAccessibility-Custos \
         SecuityToAccessibility-Traditional \
         TrustModel-Seperated+Data \
         TrustModel-Seperated \
         TrustModel-Traditional \
         )

all: pdf

figs: $(FIGS)

pdf: $(SRCS) $(CLS) figs
	$(LATEX) $(REPORT)
	$(BIBTEX) $(REPORT)
	$(LATEX) $(REPORT)
	$(LATEX) $(REPORT)
	$(LATEX) $(REPORT)

figs/out/%.pdf: figs/src/%.svg
	inkscape --export-area-drawing --export-eps="$(FIG_TMP)" --file="$<"
	epstopdf "$(FIG_TMP)" --outfile="$@"
	rm "$(FIG_TMP)"

bibsort: refs.bib
	bibtool -s -o ./refs.bib -i ./refs.bib

clean-tex:
	$(RM) *.dvi *.aux *.log *.blg *.bbl *.out *.lof *.lot *.toc

clean-fig:
	$(RM) figs/out/*.pdf *.eps

clean: clean-tex clean-fig	
	$(RM) $(REPORT).pdf
	$(RM) *~ .*~
