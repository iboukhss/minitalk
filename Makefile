CFLAGS = -Wall -Wextra -g3 -fsanitize=undefined,address

all: client server

client: client.o ft_memset.o ft_atoi.o
	$(CC) $(CFLAGS) $^ -o $@

server: server.o ft_memset.o ft_printf.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

norm:
	-norminette client.c server.c minitalk.h ft_atoi.c ft_printf.c ft_memset.c libft.h

clean:
	$(RM) *.o

fclean: clean
	$(RM) client server

re: fclean all

.PHONY: all norm clean fclean re
