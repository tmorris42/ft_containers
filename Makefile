NAME = ft_containers.out
REAL = real.out
REAL_TOGGLE = -DFT_REAL_VERSION=1

SRCS_DIR = srcs
INCLUDE_DIR = includes
OBJS_DIR = objs

SRCS = main.cpp UnitTest.cpp \
			test_iterator.cpp \
			test_vector_int.cpp \
			test_vector_string.cpp \
			test_vector_struct.cpp \
			test_vector_class.cpp \
			test_stack.cpp \
			test_rb_tree.cpp \
			test_map.cpp \


OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
REAL_OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.real.o))
INCLUDES = -I$(INCLUDE_DIR)

#https://stackoverflow.com/questions/97338/gcc-dependency-generation-for-a-different-output-directory
DEPS = $(OBJS:.o=.d)

CC_OVERRIDE ?= clang++
CC	:= $(CC_OVERRIDE)
FLAGS = -MMD -Wall -Wextra -Werror
MY_FLAGS = $(FLAGS) -std=c++98 -pedantic

DEBUG_FLAGS ?= -g3
ifdef DEBUG_OVERRIDE
FLAGS := $(FLAGS) $(DEBUG_FLAGS)
endif

all: $(NAME) $(REAL)

$(OBJS_DIR):
	@mkdir -p objs

$(REAL): $(REAL_OBJS) | $(OBJS_DIR)
	$(CC) $(REAL_TOGGLE) $(FLAGS) $(REAL_OBJS) $(INCLUDES) -o $(REAL)

$(NAME): $(OBJS) | $(OBJS_DIR)
	$(CC) $(MY_FLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

$(OBJS_DIR)/%.real.o : $(SRCS_DIR)/%.cpp | $(OBJS_DIR)
	$(CC) $(REAL_TOGGLE) -c $(FLAGS) $(INCLUDES) $< -o $@

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.cpp | $(OBJS_DIR)
	$(CC) $(MY_FLAGS) -c $(INCLUDES) $< -o $@

$(OBJS_DIR)/%.real.d: $(SRCS_DIR)/%.cpp | $(OBJS_DIR)
	$(CC) $(FLAGS) -c $(INCLUDES) $< > $@

real: $(REAL) | $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)
	rm -rf mine.log mine.err.log real.log real.err.log

fclean: clean
	rm -f $(NAME) $(REAL)

re: fclean all | $(OBJS_DIR)

test: all
	@echo "Generating user logs"
	@./$(NAME) -v > mine.log 2>mine.err.log
	@echo "Generating real logs"
	@./$(REAL) -v > real.log 2>real.err.log
	@echo "Comparing output"
	@echo "-----------------"
	@diff -s mine.log real.log
	@diff -s mine.err.log real.err.log

-include $(DEPS)

.PHONY: all clean fclean re test
