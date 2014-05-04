CPPLIBS=-lboost_unit_test_framework -lpdppt -lQtGui -lQtCore -lmocc 
CPPFLAGS=-I/usr/include/qt4 -I/usr/include/qt4/QtCore -I/usr/include/mocc -I./src -I/usr/include/ -I. -g

OBJ_COMMON=src/pd2mo.o src/traverser.o src/prefixmovars.o inih/ini.o inih/INIReader.o
TEST=test/powerdevs test/modelicacc test/pd2mo test/inih

all: $(TEST) $(OBJ_COMMON)

clean:
	rm src/*.o
	rm test/*.o
	rm test/powerdevs
	rm test/modelicacc
	rm test/pd2mo


test: $(TEST) $(OBJ_COMMON)
	test/modelicacc
	test/powerdevs
	test/inh
	test/pd2mo

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

inih/INIReader.o : inih/cpp/INIReader.cpp 
	$(CXX) -c $<

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) $< -o $@
