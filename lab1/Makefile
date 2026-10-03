CXX      := g++
SRC      := $(wildcard *.cpp)
OBJ      := $(patsubst %.cpp, %.o, $(SRC))
BIN      := main.out
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -fopenmp -I.
LDFLAGS  := -fopenmp -lm

$(BIN): $(OBJ)
	@$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean run rebuild bench

clean:
	@rm -f $(BIN) *.o bench.txt

THREADS ?= 4
run: $(BIN)
	@./$(BIN) $(THREADS)


N ?= 200000000
THREADS_LIST ?= 1 2 4 8
bench: $(BIN)
	@rm -f bench.txt
	@for t in $(THREADS_LIST) ; do \
		./$(BIN) $$t $(N) >> bench.txt ; \
	done
	@cat bench.txt

rebuild: clean run