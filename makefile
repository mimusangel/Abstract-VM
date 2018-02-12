SRC_PATH = ./src/
OBJ_PATH = ./obj/

SRC_NAME = Factory.cpp Manager.cpp Parser.cpp main.cpp
OBJ_NAME = $(SRC_NAME:.cpp=.o)
NAME = avm

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

CC = g++
CFLAGS = -Wall -Werror -Wextra -MMD -pedantic -Wuninitialized -std=c++11
LIBS =

all:
	@echo "\033[36;44m Make $(NAME) \033[0m"
	@make $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@echo "\033[32;44m Make clean $(NAME) \033[0m"
	rm -rf $(OBJ) $(OBJ_PATH)

fclean: clean
	@echo "\033[32;44m Make fclean $(NAME) \033[0m"
	rm -f $(NAME)

re: fclean all

-include $(OBJ:.o=.d)

.PHONY: lib clean fclean re