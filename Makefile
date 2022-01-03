NAME = ft_containers.out
REAL = real.out
REAL_TOGGLE = -DFT_REAL_VERSION=1

SRCS_DIR = srcs
INCLUDE_DIR = includes
OBJS_DIR = objs

SRCS = main.cpp UnitTest.cpp
HEADER_FILES := vector.hpp
HEADERS := $(addprefix $(INCLUDE_DIR)/, $(HEADER_FILES))
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
REAL_OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.real.o))
INCLUDES = -I$(INCLUDE_DIR)

CC_OVERRIDE ?= clang++
CC	:= $(CC_OVERRIDE)
FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

DEBUG_FLAGS ?= -g3
ifdef DEBUG_OVERRIDE
FLAGS := $(FLAGS) $(DEBUG_FLAGS)
endif

all: $(NAME) $(REAL)

$(REAL): $(REAL_OBJS) $(HEADERS)
	$(CC) $(REAL_TOGGLE) $(FLAGS) $(REAL_OBJS) $(INCLUDES) -o $(REAL)

$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(FLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

$(OBJS_DIR)/%.real.o : $(SRCS_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	@mkdir -p objs
	$(CC) $(REAL_TOGGLE) -c $(FLAGS) $(INCLUDES) $< -o $@

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	@mkdir -p objs
	$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

real: $(REAL)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME) $(REAL)

re: fclean all

test: $(NAME) real
	@echo "Generating user logs"
	@./$(NAME) -v > mine.log 2>mine.err.log
	@echo "Generating real logs"
	@./$(REAL) -v > real.log 2>real.err.log
	@echo "Comparing output"
	@echo "-----------------"
	@diff -s mine.log real.log
	@diff -s mine.err.log real.err.log

.PHONY: all clean fclean re test
