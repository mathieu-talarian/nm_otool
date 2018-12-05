NAME= ft_nm
SRC_PATH= src
SRC_NAME= \
main.c \
nm.c handle_64b.c \
handle_32.c \
handle_func.c\
handle_output.c\
type.c \
ft_sec_lst.c \
ft_sym_lst.c \
value_to_add.c \
fat_arch.c \
utils.c \
is_corrupted.c \
_utils.c 


OBJ_PATH= obj

IC = -Iinclude -Ilib/libft/include

CC = gcc
CFLAGS = -Wall -Wextra -Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIBFTDIR = lib/libft

all: $(NAME)

$(NAME): $(OBJ) .libft
	$(CC)  -o nm $(OBJ) -Ilib/libft -lft -Llib/libft

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
		@mkdir $(OBJ_PATH) 2> /dev/null || true
		$(CC)  -o $@ -c $< $(IC)

test: .libft $(OBJ)
	$(CC) main_test/main.c obj/*.o $(IC) -o malloc -Llib/libft -lft
	./malloc

clean:
	make clean -C lib/libft
	@rm -fv $(OBJ)
	@rmdir -v $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	make fclean -C lib/libft
	@rm -rfv malloc

run: all
	./nm nm

.libft:
	make -C $(LIBFTDIR)
.libftclean:
	make clean -C $(LIBFTDIR)
.libftfclean:
	make fclean -C $(LIBFTDIR)

retest: fclean test

re: fclean all
