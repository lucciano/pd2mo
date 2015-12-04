all: slides_luciano.pdf tesina_luciano.pdf
slides_luciano.pdf: slides_luciano.tex slides_luciano.bbl
	pdflatex -shell-escape slides_luciano.tex

slides_luciano.bbl: tesina_luciano.bib
	biber slides_luciano

tesina_luciano.pdf : tesina_luciano.tex ch-a.tex ch01.tex ch02.tex ch03.tex ch04.tex ch05.tex ch06.tex tesina_luciano.bib esquema tesina_luciano.bib
	pdflatex  -shell-escape tesina_luciano.tex

esquema: esquema.dot
	dot -Tpng esquema.dot -o esquema.png
