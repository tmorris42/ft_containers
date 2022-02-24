NAME = ft_containers.out
REAL = real.out
REAL_TOGGLE = -DFT_REAL_VERSION=1

SRCS_DIR = srcs/
INCLUDE_DIR = includes/
OBJS_DIR = objs/
LOGS_DIR = logs/

SRCS = main.cpp UnitTest.cpp \
			test_iterator.cpp \
			test_vector_int.cpp \
			test_vector_string.cpp \
			test_vector_struct.cpp \
			test_vector_class.cpp \
			test_stack.cpp \
			test_rb_tree.cpp \
			test_map.cpp \
			test_set.cpp \


OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))
REAL_OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.real.o))
INCLUDES = -I$(INCLUDE_DIR)
DEPS = $(OBJS:.o=.d)

VALGRIND_LOG = $(addprefix $(LOGS_DIR), val.log)
TIME_FORMAT = "elapsed time: %e\tsystem time: %S\tuser time: %U"

CC_OVERRIDE ?= clang++
CC	:= $(CC_OVERRIDE)
FLAGS = -MMD -Wall -Wextra -Werror
MY_FLAGS = $(FLAGS) -std=c++98 -pedantic

DEBUG_FLAGS ?= -g3
ifdef DEBUG_OVERRIDE
FLAGS := $(FLAGS) $(DEBUG_FLAGS)
endif

$(NAME): $(OBJS) | $(OBJS_DIR)
	$(CC) $(MY_FLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

all: $(NAME) $(REAL)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(LOGS_DIR):
	@mkdir -p $(LOGS_DIR)

$(REAL): $(REAL_OBJS) | $(OBJS_DIR)
	$(CC) $(REAL_TOGGLE) $(FLAGS) $(REAL_OBJS) $(INCLUDES) -o $(REAL)

$(OBJS_DIR)%.real.o : $(SRCS_DIR)%.cpp | $(OBJS_DIR)
	$(CC) $(REAL_TOGGLE) -c $(FLAGS) $(INCLUDES) $< -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)%.cpp | $(OBJS_DIR)
	$(CC) $(MY_FLAGS) -c $(INCLUDES) $< -o $@

$(OBJS_DIR)%.real.d: $(SRCS_DIR)%.cpp | $(OBJS_DIR)
	$(CC) $(FLAGS) -c $(INCLUDES) $< > $@

real: $(REAL) | $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)
	rm -rf $(LOGS_DIR)

fclean: clean
	rm -f $(NAME) $(REAL)

re: fclean all | $(OBJS_DIR)

test: all | $(LOGS_DIR)
	@echo 'Generating user logs'
	@/usr/bin/time -f $(TIME_FORMAT) -o $(LOGS_DIR)mine.time.log ./$(NAME) -v > $(LOGS_DIR)mine.log 2>$(LOGS_DIR)mine.err.log
	@echo 'Generating real logs'
	@/usr/bin/time -f $(TIME_FORMAT) -o $(LOGS_DIR)real.time.log  ./$(REAL) -v > $(LOGS_DIR)real.log 2>$(LOGS_DIR)real.err.log 
	@echo 'Comparing output'
	@echo '-----------------'
	@diff -s $(LOGS_DIR)mine.log $(LOGS_DIR)real.log
	@diff -s $(LOGS_DIR)mine.err.log $(LOGS_DIR)real.err.log
	@echo '-----------------'
	@echo -n "$(NAME) "
	@cat $(LOGS_DIR)mine.time.log
	@echo -n "         $(REAL) "
	@cat $(LOGS_DIR)real.time.log

leaks: $(NAME) | $(LOGS_DIR)
	@echo 'Checking for leaks...'
	@valgrind --leak-check=full ./$(NAME) > $(VALGRIND_LOG) 2>&1
	@(cat $(VALGRIND_LOG) | grep 'LEAK SUMMARY\|invalid\|Invalid' > /dev/null \
		&& echo -n '\033[0;31m' && cat $(VALGRIND_LOG) | grep 'LEAK SUMMARY\|invalid\|Invalid' | wc -l | tr '\n' ' ' \
		&& echo 'leak(s) found\033[0m' \
		&& echo 'Check $(VALGRIND_LOG) for details') \
		|| echo '\033[0;32mNo leaks found!\033[0m';

-include $(DEPS)

.PHONY: all clean fclean re test leaks
