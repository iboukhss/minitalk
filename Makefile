CFLAGS = -Wall -Wextra -g3 -fsanitize=undefined,address

LIBFT = ft_memset.c ft_atoi.c

all: client server

client: client.c
	$(CC) $(CFLAGS) $< -o $@

server: server.c
	$(CC) $(CFLAGS) $< -o $@

norm:
	-norminette client.c server.c minitalk.h

clean:
	$(RM) *.o

fclean:
	$(RM) client server

re: fclean all

.PHONY: all norm clean fclean re
