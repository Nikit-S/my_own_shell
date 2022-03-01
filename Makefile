NAME		=	minishell

SRCS	=	srcs/free_sigs.c \
				srcs/ft_change_dol.c \
				srcs/ft_change_dol_utils.c \
				srcs/ft_execve.c \
				srcs/ft_piping.c \
				srcs/ft_sp_fun.c \
				srcs/ft_split_fun.c \
				srcs/in_files.c \
				srcs/main.c \
				srcs/out_files.c \
				srcs/quotes_replace.c \
				srcs/quotes_parse.c \
				srcs/read_input.c \
				srcs/skip_space.c \
				srcs/value_exit.c \
				parser/parser.c \
				parser/parser_utils.c \
				srcs/ft_lexer.c \
				commands/ft_cd.c \
				commands/ft_echo.c \
				commands/ft_env.c \
				commands/ft_export.c \
				commands/ft_pwd.c \
				commands/ft_unset.c

LIBFT_PATH =  libft/

CC			=	gcc

FLAGS		= -Wall -Werror -Wextra #-fsanitize=leak

%.o:		%.c
			$(CC) $(FLAGS) -c $< -o $(<:.c=.o)


SRCS_OBJ		=	$(SRCS:.c=.o)

all:		libft_lib $(NAME)

libft_lib:
			make -C $(LIBFT_PATH)

$(NAME):	$(SRCS_OBJ) libft/libft.h libft/libft.a commands/commands.h incs/includes.h
			gcc $(SRCS_OBJ) libft/libft.a -lreadline -o $(NAME)

clean:
			rm -rf $(SRCS_OBJ)
			make -C $(LIBFT_PATH) clean

fclean:		clean
			make -C $(LIBFT_PATH) fclean
			rm -rf $(NAME)

re:			fclean all

.PHONY: 	all clean fclean re
