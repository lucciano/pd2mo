FROM ubuntu:14.10

RUN apt-get update && apt-get install -y wget
RUN apt-get update && apt-get install -y gnuplot-x11 build-essential libqtcore4 libqtgui4 libqt4-svg scilab zenity gksu

RUN wget http://downloads.sourceforge.net/project/powerdevs/powerdevs_amd64_953.deb && apt-get install powerdevs_amd64_953.deb
RUN apt-get install -yq subversion git build-essential automake qt4-dev-tools bison++ libginac-dev libboost-dev libboost-test-dev
RUN svn checkout svn://svn.code.sf.net/p/qssengine/code-0/trunk qssengine-code-0
RUN svn checkout svn://svn.code.sf.net/p/modelicacc/code/trunk modelicacc-code && cd modelicacc-code && autoreconf -f && ./configure && make && sudo make install 
RUN svn checkout svn://svn.code.sf.net/p/powerdevs/code/trunk powerdevs-code && cd powerdevs-code && make install-lib  

