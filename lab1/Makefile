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

# запуск в обычном режиме (поиск n по правилу Рунге), число потоков - через
# переменную окружения OMP_NUM_THREADS или через THREADS=... в командной строке
THREADS ?= 4
run: $(BIN)
	@./$(BIN) $(THREADS)

# прогон замера масштабируемости: 2, 4, 16, 32, 64 потока,
# результат построчно пишется в bench.txt (потоков n интеграл время)
bench: $(BIN)
	@rm -f bench.txt
	@for t in 2 4 16 32 64 ; do \
		./$(BIN) $$t >> bench.txt ; \
	done
	@cat bench.txt

rebuild: clean run