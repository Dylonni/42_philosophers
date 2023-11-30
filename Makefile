# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daumis <daumis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 14:26:36 by daumis            #+#    #+#              #
#    Updated: 2023/07/27 13:44:03 by daumis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_MAIN	=	src/main.c \
			src/checks.c \
			src/tools.c \
			src/monitor.c \
			src/routine.c \
			src/free.c \
			src/mutex_actions.c \
					

SRCS        = ${SRC_MAIN}
OBJ_DIR     = .objs
OBJS        = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))

CC		= cc
RM		= rm -f
CFLAGS		= -Wall -Wextra -Werror

NAME            = philo

all: $(OBJ_DIR) $(OBJS) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@printf '\033[A\033[19C'"⌛ [\e[1;96mCompiling\033[0m]\033[35m $<\033[0m \n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	@printf '\033[A\033[20C'"\033[32;1m  ✅ Project has compiled successfully!          \033[0m"
	@printf "\n\n    [🏳️ FLAGS: \033[0;35m$(CFLAGS)\033[0m]"
	@echo "\033[32;1m\n 💾 Executable \e[7m./$(NAME)\e[27m has been created in: \n    └─ 📂 \033[4;36m ~ $(PWD)\033[0m"

clean:
	$(RM) -r $(OBJ_DIR)

fclean:
	@echo "\033[1;93m\n                        [Cleaning directories with \033[0;96mfclean\033[1;93m]\n\033[0m"
	@make clean
	$(RM) $(NAME)

re:
	@make fclean
	@echo "\033[1;93m\n                             [Calling \033[0;96mmake all\033[1;93m rule]\n\n\033[0m"
	@make -s all

.PHONY: all clean fclean re
