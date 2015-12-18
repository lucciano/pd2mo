all: slides_luciano.pdf tesina_luciano.pdf
slides_luciano.pdf: slides_luciano.tex 
	pdflatex -shell-escape slides_luciano.tex

tesina_luciano.pdf : tesina_luciano.tex ch-a.tex ch01.tex ch02.tex ch03.tex ch04.tex ch05.tex ch06.tex tesina_luciano.bib esquema tesina_luciano.bib
	pdflatex  -shell-escape tesina_luciano.tex
	bibtex8 tesina_luciano
	pdflatex  -shell-escape tesina_luciano.tex

esquema: esquema.dot
	dot -Tpng esquema.dot -o esquema.png

graphs:
	cd output/adr/ && gnuplot 28302480.plt && gnuplot adr.plt && gnuplot combined.plt
	cd output/buck_disk/ && gnuplot 32978672.plt && gnuplot buck_disc_qss.plt && gnuplot combined.plt
	cd output/inverters/ && gnuplot 18002960.plt && gnuplot inverters_qss.plt && gnuplot combined.plt
	cd output/lcline/ && gnuplot 21110912.plt && gnuplot lcline_qss.plt && gnuplot combined.plt
	cd output/lotka_volterra/ && gnuplot 26738368.plt && gnuplot lotka_volterra.plt && gnuplot combined.plt

clean:
	rm *.aux *.nav *.toc
