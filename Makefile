CPPLIBS=-lboost_unit_test_framework -lpdppt -lQtGui -lQtCore -lmocc 
CPPFLAGS=-I/usr/include/qt4 -I/usr/include/qt4/QtCore -I/usr/include/mocc -I./src -I/usr/include/ -I.

OBJ_COMMON=src/traverser.o

all: test $(OBJ_COMMON)

clean:
	rm test/*.o
	rm test/powerdevs
	rm test/modelicacc
	rm test/pd2mo


test:test/powerdevs test/modelicacc test/pd2mo
	test/modelicacc
	test/powerdevs
	test/pd2mo

test/powerdevs: test/powerdevs.o
	$(CXX) -o $@ $< $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/modelicacc: test/modelicacc.o
	$(CXX) -o $@ $< $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/pd2mo: test/pd2mo.o $(OBJ_COMMON)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(BOOST_FLAGS) -o $@  $< $(OBJ_COMMON) $(CPPLIBS)
 
%.o : %.cpp
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) $< -o $@
