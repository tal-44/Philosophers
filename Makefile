 
NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I./includes

SRCS = src/main.c \
		src/philo.c \
		src/utils/cast.c \
		src/utils/utilsa.c \
		src/utils/utilsb.c \
		src/utils/utilsc.c \

OBJS = $(SRCS:src/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) compiled successfully."

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) executable removed."

re: fclean all

.PHONY: all clean fclean re
