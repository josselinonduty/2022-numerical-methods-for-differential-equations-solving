# ------------ Main configuration ------------
CC=gcc
BINDIR=bin
EXEC=main
# ------------ Debug configuration ------------
DEBUG=valgrind
DFLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes
# ------------ Build configuration ------------
SRCDIR=src
INCLUDEDIR=include
SRC=$(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/**/*.c)
OBJ=$(SRC:%.c=%.o)
CFLAGSBASE=-Wall -fPIC -pedantic -std=c11 -I$(INCLUDEDIR)
CFLAGS=$(CFLAGSBASE) -O3
LDFLAGSBASE=-lm
LDFLAGS=$(LDFLAGSBASE)
# ------------ Lint configuration ------------
LINT=indent
LINTFLAGS=-nbad -bap -nbc -bbo -hnl -br -brs -c33 -cd33 -ncdb -ce -ci4  -cli0 -d0 -di1 -nfc1 -i8 -ip0 -l80 -lp -npcs -nprs -npsl -sai -saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1
# ------------ End of configuration ------------

# ---------------------------------
#               Targets            
# ---------------------------------

.PHONY: all lint build run display
.PHONY: clean/all clean clean/objects clean/exec

all: build

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@echo "Building $<..."
	@$(CC) -o $@ -c $< $(CFLAGS)

$(SRCDIR)/%/%.o: $(SRCDIR)/%/%.c
	@echo "Building $<..."
	@$(CC) -o $@ -c $< $(CFLAGS)

lint: $(SRC)
	@for file in $^; do \
			$(LINT) $(LINTFLAGS) $$file; \
	done
	@find ./$(SRCDIR)/ -name "*.c~" -type f -delete

production/debug: $(INPUT) build
	$(DEBUG) -s $(DFLAGS) $(BINDIR)/$(EXEC) $(SUBCOMMAND) $(INPUT) $(OUTPUT) 2>&1 | tee $(BINDIR)/.valgrind.rpt

production/debug/headless: $(INPUT) build
	$(DEBUG) -s $(DFLAGS) $(BINDIR)/$(EXEC) $(SUBCOMMAND) $(INPUT) $(OUTPUT) 2>&1 | tee $(BINDIR)/.valgrind.rpt | \
		grep -q "All heap blocks were freed -- no leaks are possible"; \
		if [ $$? -ne 0 ]; then \
			echo "Memory leaks detected!"; \
			exit 1; \
		fi;

build: $(BINDIR)/$(EXEC)

display: run
	@COMMAND=""; \
	for file in $(wildcard ./export/*.csv); do \
		COMMAND="$$COMMAND '$$file' using 2:3 with lines title "; \
		COMMAND="$$COMMAND '$$(basename $$file .csv)' noenhanced, "; \
	done; \
	gnuplot -e "plot $$COMMAND" -p

$(BINDIR)/$(EXEC): $(OBJ)
	@mkdir -p $(BINDIR)
	@echo "Building $(BINDIR)/$(EXEC)..."
	@$(CC) -o $(BINDIR)/$(EXEC) $(OBJ) $(LDFLAGS)

run: build
	@./$(BINDIR)/$(EXEC)

clean/all: clean

clean: clean/objects clean/exec

clean/objects:
	@find ./$(SRCDIR)/ -name "*.o" -type f -delete

clean/exec:
	@rm -f ./$(BINDIR)/$(EXEC)