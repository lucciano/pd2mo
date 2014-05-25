CPPLIBS=-lboost_unit_test_framework -lpdppt -lQtGui -lQtCore -lmocc -lsimpd
CPPFLAGS=-I/usr/include/qt4 -I/usr/include/qt4/QtCore -I/usr/include/mocc -I./src -I/usr/include/ -I. -g

OBJ_COMMON=src/pd2mo.o src/traverser.o src/prefixmovars.o src/setParameters.o inih/ini.o inih/cpp/INIReader.o
TEST=test/powerdevs test/modelicacc test/pd2mo test/inih test/simp

all: $(TEST) $(OBJ_COMMON)

clean:
	rm src/*.o
	rm test/*.o
	rm test/powerdevs
	rm test/modelicacc
	rm test/pd2mo
	rm test/simp


test: $(TEST) $(OBJ_COMMON)
	test/modelicacc
	test/powerdevs
	test/inh
	test/pd2mo
	test/simp

test/simp: test/simp.o
	$(CXX) -o $@ $< $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/powerdevs: test/powerdevs.o
	$(CXX) -o $@ $< $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/modelicacc: test/modelicacc.o
	$(CXX) -o $@ $< $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/pd2mo: test/pd2mo.o $(OBJ_COMMON)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(BOOST_FLAGS) -o $@  $< $(OBJ_COMMON) $(CPPLIBS)

test/inih: test/inih.o $(OBJ_COMMON)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(BOOST_FLAGS) -o $@  $< $(OBJ_COMMON) $(CPPLIBS)

inih/ini.o : inih/ini.c
	$(CC) -c $<

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) $< -o $@
