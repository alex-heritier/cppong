GTEST_DIR = /Users/Alex/Downloads/gtest

FLAGS = -g -Wall  -std=c++11 -stdlib=libc++
LFLAGS = $(FLAGS) -lncurses
CFLAGS = $(FLAGS) -c

TEST_LFLAGS = $(FLAGS) -isystem ${GTEST_DIR}/include lib/libgtest.a
TEST_CFLAGS = $(FLAGS) -c -I$(GTEST_DIR)/include -pthread

build/pong: lib/game.o lib/graphics.o lib/paddle.o lib/log.o lib/ball.o lib/label.o
	g++ $(LFLAGS) lib/game.o lib/graphics.o lib/paddle.o \
		lib/log.o lib/ball.o lib/label.o -o build/pong
	
lib/game.o: src/game.cpp
	g++ $(CFLAGS) src/game.cpp -o lib/game.o
	
lib/graphics.o: src/graphics.h src/graphics.cpp src/drawable.h
	g++ $(CFLAGS) src/graphics.cpp -o lib/graphics.o
	
lib/paddle.o: src/paddle.h src/paddle.cpp
	g++ $(CFLAGS) src/paddle.cpp -o lib/paddle.o
	
lib/log.o: src/log.h src/log.cpp
	g++ $(CFLAGS) src/log.cpp -o lib/log.o
	
lib/ball.o: src/ball.h src/ball.cpp
	g++ $(CFLAGS) src/ball.cpp -o lib/ball.o
	
lib/label.o: src/label.h src/label.cpp
	g++ $(CFLAGS) src/label.cpp -o lib/label.o
	
build/test: lib/test.o
	g++ $(TEST_LFLAGS) lib/test.o -o build/test
	
lib/test.o: src/test.cpp
	g++ $(TEST_CFLAGS) src/test.cpp -o lib/test.o
	
run: build/pong
	./build/pong
	
test: build/test
	./build/test
	
clean:
	rm lib/*.o
	rm build/*
	rm log.txt