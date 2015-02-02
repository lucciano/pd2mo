CPPLIBS=-lboost_unit_test_framework -lpdppt -lQtGui -lQtCore -lmocc -lsimpd
CPPFLAGS=-I/usr/include/qt4 -I/usr/include/qt4/QtGui/ -I/usr/include/qt4/QtCore -I/usr/include/mocc -I./src -I/usr/include/ -I. -g -std=c++0x

OBJ_COMMON=src/pd2mo.o src/traverser.o src/prefixmovars.o src/setParameters.o src/flatter.o src/evalp.o src/motools.o src/mda.o src/uda.o src/if.o src/range.o src/prodint.o
TEST=test/powerdevs test/modelicacc test/pd2mo test/simp test/getopt test/flatter test/annotation test/mda test/uda test/prodint

all: $(TEST) $(OBJ_COMMON) pd2mo
clean:
	rm src/*.o
	rm test/*.o
	rm test/powerdevs
	rm test/modelicacc
	rm test/pd2mo
	rm test/simp
	rm test/getopt
	rm test/flatter
	rm test/annotation
	rm test/mda
	rm test/uda


test: $(TEST) $(OBJ_COMMON)
	test/modelicacc
	test/powerdevs
	test/inh
	test/pd2mo
	test/simp
	test/getopt
	test/flatter
	test/annotation
	test/mda
	test/uda
	test/prodint


pd2mo: src/main.o $(OBJ_COMMON)
	$(CXX) -o $@ $< $(OBJ_COMMON)$(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/prodint: test/prodint.o $(OBJ_COMMON)
	$(CXX) -o $@ $< $(OBJ_COMMON) $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/uda: test/uda.o $(OBJ_COMMON)
	$(CXX) -o $@ $< $(OBJ_COMMON) $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/mda: test/mda.o $(OBJ_COMMON)
	$(CXX) -o $@ $< $(OBJ_COMMON) $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/annotation : test/annotation.o 
	$(CXX) -o $@ $< $(OBJ_COMMON) $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/flatter: test/flatter.o 
	$(CXX) -o $@ $< $(OBJ_COMMON) $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/getopt: test/getopt.o
	$(CXX) -o $@ $< $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/simp: test/simp.o
	$(CXX) -o $@ $< $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/powerdevs: test/powerdevs.o
	$(CXX) -o $@ $< $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/modelicacc: test/modelicacc.o
	$(CXX) -o $@ $< $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/pd2mo: test/pd2mo.o $(OBJ_COMMON)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(BOOST_FLAGS) -o $@  $< $(OBJ_COMMON) $(CPPLIBS)

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) $< -o $@
