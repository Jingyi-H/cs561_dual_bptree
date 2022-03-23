

MKDIR_P = mkdir -p
all: analysis main workloadgenerator
	$(MKDIR_P) tree_dat
	

simple_analysis: betree.h analysis.cpp -DBPLUS
	g++ -g -std=c++11 betree.h analysis.cpp -o analysis.o 

analysis: betree.h analysis.cpp
	g++ -g -std=c++11 betree.h analysis.cpp -o analysis.o -DTIMER -DBPLUS

main: main.cpp betree.h dual_betree.h dual_betree.cpp
	g++ -g -std=c++11 -o $@ $^

workloadgenerator: workload_generator.cpp
	g++ -g -std=c++0x -o $@ $^

clean: 
	$(RM) *.o
	rm main
	rm workloadgenerator
	$(RM) tree_dat/*
	rm -r tree_dat/
