
# Andrew West - Makefile for the P2P Simulator
# Inefficient but terse compilation of the two executables

# Compilers
CC = gcc
JC = javac

# Libraries to include.
LIBS = -lm

# Optimization flag
OPT = -O3

# Cleanup macro
CLEANUP = -rm -f *.o

# Macros for whole libraries
CORE_FILES = core_lib/*.c core_lib/*.h
GEN_FILES = gen_lib/*.c gen_lib/*.h
SIM_FILES = sim_lib/*.c sim_lib/*.h
TSYS_FILES = tsys_lib/*.c tsys_lib/*.h
PARSE_FILES = parser/*.java

# Header search path
FIND_HEADER = -I core_lib -I tsys_lib -I sim_lib

# ----------------------------------------------

# Give the commands to compile the executables.

all: gen_trace sim_run parse

all.condor: gen_trace.condor sim_run.condor parse

gen_trace: $(CORE_FILES) $(GEN_FILES)
	@echo [Compiling trace generator]
	$(CC) $(LIBS) $(OPT) $(FIND_HEADER) -c core_lib/*.c gen_lib/*.c
	$(CC) $(LIBS) $(OPT) *.o -o gen_trace -lm
	$(CLEANUP)
	@echo [Trace generator compilation successful!]
	
gen_trace.condor: $(CORE_FILES) $(GEN_FILES)
	@echo [Compiling CONDOR trace generator]
	$(CC) $(LIBS) $(OPT) $(FIND_HEADER) -c core_lib/*.c gen_lib/*.c
	condor_compile $(CC) $(LIBS) $(OPT) *.o -o gen_trace.condor
	$(CLEANUP)
	@echo [Trace generator CONDOR compilation successful!]
	
sim_run: $(CORE_FILES) $(SIM_FILES) $(TSYS_FILES)
	@echo [Compiling trust simulator]
	$(CC) $(LIBS) $(OPT) $(FIND_HEADER) -c core_lib/*.c sim_lib/*.c tsys_lib/*.c
	$(CC) $(LIBS) $(OPT) *.o -o sim_run -lm
	$(CLEANUP)
	@echo [Trust simulator compilation successful!]
	
sim_run.condor: $(CORE_FILES) $(SIM_FILES) $(TSYS_FILES)
	@echo [Compiling CONDOR trust simulator]
	$(CC) $(LIBS) $(OPT) $(FIND_HEADER) -c core_lib/*.c sim_lib/*.c tsys_lib/*.c
	condor_compile $(CC) $(LIBS) $(OPT) *.o -o sim_run.condor
	$(CLEANUP)
	@echo [Trust simulator CONDOR compilation successful!]

parse: $(PARSE_FILES)
	@echo [Compiling output parser]
	$(JC) parser/*.java
	@echo [Output parser compiled!]
	
delete:
	rm parser/*.class
	rm gen_trace sim_run

