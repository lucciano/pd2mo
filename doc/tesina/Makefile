doc: tesina_luciano.tex tesina_luciano.bib esquema
	pdflatex  -shell-escape tesina_luciano.tex
	bibtex tesina_luciano
	pdflatex  -shell-escape tesina_luciano.tex

esquema: esquema.dot
	dot -Tpng esquema.dot -o esquema.png
