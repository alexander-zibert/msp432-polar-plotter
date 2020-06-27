.PHONY: test

CXX=clang++
LIB_DIR=include
TEST_DIR=test
VENDOR_DIR=vendor
CXX_FLAGS=-Wall -Wextra -pedantic -pedantic-errors -fno-threadsafe-statics -fno-exceptions -std=c++2a -O2
TEST_FILE=run_test.out

INCLUDES=-I$(TEST_DIR) -I$(LIB_DIR) -I$(VENDOR_DIR)

SRCS=$(wildcard $(TEST_DIR)/*.cpp)

OBJS=$(SRCS:.cpp=.o)
 
test: $(OBJS)
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -o $(TEST_FILE) $(OBJS)
	./$(TEST_FILE)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm $(OBJS) 2> /dev/null
	rm $(TEST_FILE) 2> /dev/null
