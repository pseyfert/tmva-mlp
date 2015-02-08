CXX=$(shell root-config --cxx)
LD=$(shell root-config --ld)
LDFLAGS=$(shell root-config --libs)
CXXFLAGS=$(shell root-config --cflags)
MYFLAGS=-O2 -g -Wall -Wextra -m64 -mabm -maes  -malign-stringops  -mavx  -mfancy-math-387  -mfentry  -mfp-ret-in-387  -mglibc  -mhard-float  -mieee-fp  -mlong-double-80  -msse  -msse2  -msse3
CALLGRIND= valgrind --tool=callgrind -v --dump-instr=yes --trace-jump=yes --smc-check=all-non-file --callgrind-out-file=callgrind.out ./main > main.log &> callgrind.log
# add in 3  -ftree-vectorize -ftree-vectorize -ftree-vectorizer-verbose=7

%.o: %.cc MLP.C
	$(CXX) $(CXXFLAGS) $< -o $@ $(MYFLAGS) -c
%: %.o
	$(LD) $(LDFLAGS) $< -o $@ $(MYFLAGS)

callgrind.out: main
	$(CALLGRIND)

