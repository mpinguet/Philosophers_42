NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g

SRCS =	action.c \
		error_management.c \
		time.c \
		mutex.c \
		philo_utils.c \
		philo_utils2.c \
		main.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ Compilation terminée !"

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "🧹 Fichiers objets supprimés."

fclean: clean
	@rm -f $(NAME)
	@echo "🧼 Fichier exécutable supprimé."

re: fclean all

.PHONY: all clean fclean re


