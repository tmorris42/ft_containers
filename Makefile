NAME = ft_containers.out
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
INCLUDE_DIR = includes

SRCS_DIR = srcs
OBJS_DIR = objs

TEST_SRCS = UnitTest.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_DIR = tests
# HEADER = 

CC_OVERRIDE ?= clang++
CC	:= $(CC_OVERRIDE)
ifdef $(DEBUG_OVERRIDE)
DEBUG_FLAGS ?= -g3
else
DEBUG_FLAGS = #empty
endif
FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic $(DEBUG_FLAGS)
INCLUDES = -I$(INCLUDE_DIR) -I$(TEST_DIR)

all: $(NAME)

$(NAME): $(OBJS_DIR)/$(OBJS) $(OBJS_DIR)/$(TEST_OBJS)
	$(CC) $(FLAGS) $(OBJS_DIR)/$(OBJS) $(OBJS_DIR)/$(TEST_OBJS) $(INCLUDES) -o $(NAME)

$(OBJS_DIR)/$(OBJS): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	@mkdir -p objs
	$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(OBJS_DIR)/$(TEST_OBJS): $(OBJS_DIR)/%.o : $(TEST_DIR)/%.cpp $(TEST_DIR)/%.hpp
	@mkdir -p objs
	$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf objs
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
