NAME = ft_containers.out

SRCS_DIR = srcs
INCLUDE_DIR = includes
OBJS_DIR = objs

SRCS = main.cpp UnitTest.cpp
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

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	@mkdir -p objs
	$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
