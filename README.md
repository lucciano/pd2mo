PowerDEVS to Modelica (pd2mo)
=============================

Requires
========

Build Requirement
=================

 * PowerDEVS's libpdppt and simulation engine
~~~
  svn checkout svn://svn.code.sf.net/p/powerdevs/code/trunk powerdevs-code
  cd powerdevs-code ; make install-lib
~~~

 * Modelicacc's libmodelicacc
~~~
  svn checkout svn://svn.code.sf.net/p/modelicacc/code/trunk modelicacc-code
  cd modelicacc-code ; make install
~~~
  
## Other software ##

### OpenModelica ###
https://www.openmodelica.org/download/download-linux

### PowerDEVS ###
https://sourceforge.net/projects/powerdevs/files/?source=navbar

### Modelica C Compiler ###
http://sourceforge.net/p/modelicacc/code/HEAD/tree/

### QSS Solver ###
https://sourceforge.net/projects/powerdevs/files/?source=navbar


cambiar el nombre del modelo
solo expandir el segundo componente del rango
solo expandir cuando tenga dos componentes.
expandir el producto interno cuando alguno de los dos es bidimensional y tiene rango en la segunda componente.
