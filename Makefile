SRC_LIB		=	./libft
LIBFT		=	libft.a

NAME		= 	philo

HD			=	philo.h

HD_B		=	philo_bonus.h

FLAGS		= 	-Wall -Werror -Wextra

SRS			= 	init.c	main.c	 movements.c	simulation.c	utils.c

SRS_B		= 	init_bonus.c	main_bonus.c	 movements_bonus.c	\
				simulation_bonus.c	utils_bonus.c

OBJS		=	$(SRS:.c=.o)

OBJS_B		=	$(SRS_B:.c=.o)

all bonus	:
				$(MAKE) $(NAME)

bonus		: 	export BONUS_MODE := 1

%.o			:	%.c	Makefile $(if $(BONUS_MODE), $(HD_B), $(HD))
				gcc $(FLAGS) -g -c $< -o $@

$(NAME)		:	$(if $(BONUS_MODE), $(OBJS_B), $(OBJS))
				gcc $(FLAGS) -g $(OBJS) -o $(NAME)

clean		:
				rm -f $(OBJS) $(OBJS_B)

fclean		:	clean
				rm -f $(NAME)

re			:	fclean all

re_bns		:	fclean bonus

.PHONY		: 	all bonus clean fclean re re_bns
