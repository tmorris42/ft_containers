NAME = ft_containers.out
REAL = real.out
REAL_TOGGLE = -DFT_REAL_VERSION=1

SRCS_DIR = srcs
INCLUDE_DIR = includes
OBJS_DIR = objs

SRCS = main.cpp UnitTest.cpp vector.cpp
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
INCLUDES = -I$(INCLUDE_DIR)

CC_OVERRIDE ?= clang++
CC	:= $(CC_OVERRIDE)
FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

DEBUG_FLAGS ?= -g3
ifdef $(DEBUG_OVERRIDE)
FLAGS = $(FLAGS) $(DEBUG_FLAGS)
endif

all: $(NAME)

$(REAL): Makefile
	$(CC) $(REAL_TOGGLE) $(FLAGS) $(addprefix $(SRCS_DIR)/, $(SRCS)) $(INCLUDES) -o $(REAL)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	@mkdir -p objs
	$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

real:
	$(CC) $(REAL_TOGGLE) $(FLAGS) $(addprefix $(SRCS_DIR)/, $(SRCS)) $(INCLUDES) -o $(REAL)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME) $(REAL)

re: fclean all

test: $(NAME) $(REAL)
	@echo "Generating user log"
	@./$(NAME) > mine.log
	@echo "Generating real log"
	@./$(REAL) > real.log
	@echo "Comparing output"
	@echo "-----------------"
	@diff -s mine.log real.log

.PHONY: all clean fclean re real test
