CC = gcc
SRC = task4.c tree.c game_of_life.c
OUT = task4.out

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT)

run:
	mkdir -p out
	./$(OUT) in/data16.in out/data16.out
	./$(OUT) in/data17.in out/data17.out
	./$(OUT) in/data18.in out/data18.out
	./$(OUT) in/data19.in out/data19.out
	./$(OUT) in/data20.in out/data20.out

clean:
	rm -f $(OUT) out/*.out
	