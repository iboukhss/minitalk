CC = gcc
CFLAGS = -Wall -Wextra -g -fsanitize=undefined

all: client server

client: client.c
	$(CC) $(CFLAGS) $< -o $@

server: server.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o

fclean:
	rm -f client server

re: fclean all

.PHONY: all clean fclean re
