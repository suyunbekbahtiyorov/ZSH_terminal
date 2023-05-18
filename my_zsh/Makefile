CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = functions.c my_echo.c my_cd.c my_set__env.c my_env.c my_pwd.c my_which.c my_zsh.c main.c
OUT = my_zsh

run:
	$(CC) $(CFLAGS) -o $(OUT)  $(SRC)

fclean:
	rm -f $(OUT) *.o