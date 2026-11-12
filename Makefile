#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/05 11:20:42 by marisous          #+#    #+#              #
#    Updated: 2026/11/12 09:40:32 by marisous         ###   ########.fr        #
#                                                                              #
#******************************************************************************#
VALG	= 1
ASAN	= 0
DEBUG	= -g -O0
QUIET	= 0
RMRUN	= 1
NMEM	= 0

CC	= cc
CFLAGS	= -Wall -Wextra -Werror -I.
PREXEC	= ulimit -v 131072; timeout 5s

OBJ_FOLDER	= objs

ifeq ($(VALG),1)
	EXEC	= valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 --track-origins=yes -s
	PREXEC	= ulimit -v 262144; timeout 5s
else
	ifeq ($(ASAN),1)
		COMP	= -fsanitize=address,leak
		PREXEC	= timeout 5s env ASAN_OPTIONS=halt_on_error=1
	endif
endif

NAME	= run_gnl

HDRS	= get_next_line.h

SRCS	= get_next_line.c get_next_line_utils.c

OBJS	= $(addprefix $(OBJ_FOLDER)/, 	$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG) $^ main.c -o $@

$(OBJ_FOLDER)/%.o: %.c $(HDRS)
	@mkdir -p objs/
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

clean: 
	rm -rf $(OBJ_FOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re norm eclean

test:
	@echo NAME=$(NAME)
	@echo OBJS=$(OBJS)
	@echo SRCS=$(SRCS)

norm:
	norminette $(SRCS) $(HDRS) | grep -v ": OK!"
	@echo Norminette: all OK!

eclean:
	rm -fv compile_commands.json
	bear -- make
	$(MAKE) fclean

