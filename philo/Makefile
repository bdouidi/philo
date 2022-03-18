# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 20:49:26 by user42            #+#    #+#              #
#    Updated: 2022/02/28 20:49:28 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	srcs/main.c srcs/parsing/check_arg.c srcs/parsing/utils/lib.c \
		srcs/time.c srcs/msg.c srcs/routine.c srcs/run_routine.c
@OBJS	= $(SRCS:.c=.o)
CFLAGS	= -Wall -Wextra -Werror -pthread -g 
NAME	= philo

all: $(NAME)


$(NAME): $(@OBJS)
	@echo "\033[33m- Compiling philo..."
	cc ${CFLAGS} -o ${NAME} ${@OBJS}
	@echo "\033[32mDone."
	@echo "\033[31m========================"
	@echo "YOUR PHILO IS READY"
	@echo "========================"

clean:
	rm -rf $(@OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: libft, all, clean, fclean, re
