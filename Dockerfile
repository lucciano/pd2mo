FROM ubuntu:15.04

RUN apt-get update && apt-get install -y wget
RUN apt-get update && apt-get install -yq subversion git build-essential automake qt4-dev-tools bison++ libginac-dev libboost-dev libboost-test-dev libscotch-dev libmetis-dev libhdf5-dev



RUN apt-get update && apt-get install -y libconfig-dev libgsl0-dev gfortran
RUN svn checkout svn://svn.code.sf.net/p/qssengine/code-0/trunk qssengine-code-0
RUN cd qssengine-code-0/src && make 

RUN svn checkout svn://svn.code.sf.net/p/modelicacc/code/trunk modelicacc-code 
RUN cd modelicacc-code && autoreconf -f && ./configure && make install

RUN apt-get update && apt-get install -y libhdf5-dev
RUN svn checkout svn://svn.code.sf.net/p/powerdevs/code/trunk powerdevs-code 
RUN cd powerdevs-code && make && make install-lib  

RUN apt-get update && apt-get install -y gnuplot-x11 build-essential libqtcore4 libqtgui4 libqt4-svg scilab zenity gksu
RUN wget http://downloads.sourceforge.net/project/powerdevs/powerdevs_amd64_953.deb && dpkg -i powerdevs_amd64_953.deb



