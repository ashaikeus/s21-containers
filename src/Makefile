CC:=gcc
FLAGS:=-Wall -Wextra -Werror -std=c++17
TEST_FLAGS:=-lcheck -lgtest

export LDFLAGS:="-L/opt/homebrew/lib"
export CPPFLAGS:="-I/opt/homebrew/include" -lstdc++

SRCS:=$(wildcard s21*.cpp)
HDRS:=$(wildcard s21*.h)
OBJS:=$(SRCS:%.cpp=%.o)
TEST_SRCS:=$(wildcard test.cpp)

LIB_NAME:=s21_matrix_oop.a

all: clean test 

%.o: %.cpp
	@$(CC) $(FLAGS) -c $< -o $@

test:
	@echo "\033[1;34mCreating tests\033[0m"
	@$(CC) $(FLAGS) $(CPPFLAGS) $(LDFLAGS) $(SRCS) $(TEST_SRCS) $(TEST_FLAGS) -o test
	@leaks -q --atExit -- ./test
	@# @./test
	@echo "\033[1;42m DONE \033[0m" 

clean:
	@echo "\033[1;34mCleaning\033[0m"
	@rm -rf build/ gcov_report/ report_files/ a.out test *.info *.a *.gcda app Dvi *.gcov *.gcno *.gcov *.gcno report *.o
	@echo "\033[1;42m DONE \033[0m"

$(LIB_NAME): $(OBJS)
	@echo "\033[1;34mCreating $(LIB_NAME) library\033[0m"
	@ar rc $(LIB_NAME) $^
	@ranlib $(LIB_NAME)
	@echo "\033[1;42m DONE \033[0m"

gcov_report:
	@$(CC) $(TEST_FLAGS) $(CPPFLAGS) $(LDFLAGS) $(FLAGS) $(TEST_SRCS) $(SRCS) -o test --coverage
	@./test
	@mkdir -p gcov_report
	@mv *.gcda ./gcov_report
	@mv *.gcno ./gcov_report
	@gcov ./gcov_report/*.gcno
	@lcov -t "s21_matrix_cpp" -o s21_matrix_cpp.info -c -d ./gcov_report
	@mv *.gcov ./gcov_report
	@genhtml -o report s21_matrix_cpp.info
	@open report/index.html

style: 
	@echo "\033[1;34mStyling\033[0m"
	@cp ../materials/linters/.clang-format ./
	@clang-format -i *.cpp
	@clang-format -i *.h
	@rm -rf .clang-format
	@echo "\033[1;42m DONE \033[0m"