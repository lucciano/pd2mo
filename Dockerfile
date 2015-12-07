FROM ubuntu:15.04

RUN apt-get update && apt-get install -y wget
RUN apt-get update && apt-get install -yq subversion git build-essential automake qt4-dev-tools bison++ \
libginac-dev libboost-dev libboost-test-dev libscotch-dev libmetis-dev libhdf5-dev libhdf5-serial-dev libconfig-dev libgsl0-dev \
gfortran gnuplot-x11 build-essential libqtcore4 libqtgui4 libqt4-svg scilab zenity gksu 

#RUN wget http://downloads.sourceforge.net/project/sbml/libsbml/5.12.0/stable/Linux/64-bit/libSBML-5.12.0-Linux-x64.deb && dpkg -i libSBML-5.12.0-Linux-x64.deb

RUN svn checkout svn://svn.code.sf.net/p/modelicacc/code/trunk modelicacc-code 
RUN cd modelicacc-code && autoreconf -f && ./configure && make install

RUN svn checkout -r1437 svn://svn.code.sf.net/p/qssengine/code-0/trunk qssengine-code-0
RUN cd qssengine-code-0/src && make 

RUN svn checkout svn://svn.code.sf.net/p/powerdevs/code/trunk powerdevs-code 
RUN cp /usr/include/hdf5/serial/*.h /usr/include/
RUN cd powerdevs-code && make && make install-lib  

RUN apt-get update && apt-get install -y 
RUN wget http://downloads.sourceforge.net/project/powerdevs/powerdevs_amd64_953.deb && dpkg -i --force-depends powerdevs_amd64_953.deb



