mainTARGETS = callgrind.out hist.eps time.txt
CXX=$(shell root-config --cxx)
LD=$(shell root-config --ld)
LDFLAGS=$(shell root-config --libs)
CXXFLAGS=$(shell root-config --cflags)
MYFLAGS=-fabi-version=6 -O2 -g -Wall -Wextra -m64 -mabm -maes  -malign-stringops  -mavx  -mfancy-math-387  -mfentry  -mfp-ret-in-387  -mglibc  -mhard-float  -mieee-fp   -msse  -msse2  -msse3 -mfma -ftree-vectorize -std=c++11 -funroll-loops #-fprofile-use #-fprofile-generate 
CALLGRIND= valgrind --tool=callgrind -v --dump-instr=yes --trace-jump=yes --smc-check=all-non-file --callgrind-out-file=callgrind.out ./main > main.log &> callgrind.log

numerics.o: numerics.cc MLP.C oldMLP.C
	$(CXX) $(CXXFLAGS) $< -o $@ $(MYFLAGS) -c
main.o: main.cc MLP.C
	$(CXX) $(CXXFLAGS) $< -o $@ $(MYFLAGS) -c
time.o: time.cc MLP.C
	$(CXX) $(CXXFLAGS) $< -o $@ $(MYFLAGS) -c
time: time.o
	$(LD) $(LDFLAGS) $< -o $@ $(MYFLAGS)
numerics: numerics.o
	$(LD) $(LDFLAGS) $< -o $@ $(MYFLAGS)
main: main.o
	$(LD) $(LDFLAGS) $< -o $@ $(MYFLAGS)

callgrind.out: main
	$(CALLGRIND)

hist.eps: numerics
	./numerics

time.txt: time
	time ./time > time.txt 2>&1

