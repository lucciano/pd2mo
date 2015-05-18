PowerDEVS to Modelica (pd2mo)
=============================

Requires
========

Build Requirement
=================
 * libboost-test-dev
 * PowerDEVS's libpdppt and simulation engine
~~~
  svn checkout svn://svn.code.sf.net/p/powerdevs/code/trunk powerdevs-code
  cd powerdevs-code ; make install-lib
~~~

 * Modelicacc's libmodelicacc (requires libboost)
~~~
  svn checkout svn://svn.code.sf.net/p/modelicacc/code/trunk modelicacc-code
  cd modelicacc-code ; autoconf -f ; ./configure ; sudo make install
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
