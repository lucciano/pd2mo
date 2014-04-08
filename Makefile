CPPLIBS=-lboost_unit_test_framework 
CPPFLAGS=
all: test
clean:
	rm test/*.o
	rm test/powerdevs

test:test/powerdevs test/modelicacc
	test/powerdevs
	test/modelicacc

test/powerdevs: test/powerdevs.o
	$(CXX) -o $@ $< $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

test/modelicacc: test/modelicacc.o
	$(CXX) -o $@ $< $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) 

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) $< -o $@
