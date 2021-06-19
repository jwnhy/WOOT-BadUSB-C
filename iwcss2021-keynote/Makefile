TARGETS = main

LATEX	= xelatex
BIBTEX	= bibtex

all:    $(TARGETS) debug

$(TARGETS):
		$(LATEX) $@
		-$(BIBTEX) $@ > $(BIBTEX)_out.log
		$(LATEX) $@

debug:
		-grep Warning *.log
clean:  
		rm -f images/*.aux images/*.log *.toc *.nav *.snm *.out *.aux *.bbl *.blg *.log *.dvi *.bak *~ $(TARGETS:%=%.pdf)
