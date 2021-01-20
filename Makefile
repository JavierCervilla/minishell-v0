# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/10 01:32:21 by jcervill          #+#    #+#              #
#    Updated: 2021/01/20 18:25:12 by jcervill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	Minishell

NAME_BONUS		=	Minishell_bonus

INC_DIR			=	./includes/

PRINTF_DIR 		=	$(INC_DIR)printf/


# <MANDATORY>
SRC_DIR			=	./src/mandatory/

READ_DIR		=	$(SRC_DIR)read/

SHELL_DIR 	=	$(SRC_DIR)shell/
# <MANDATORY/>

# <BONUS>
SRC_DIR_B		=	./src/bonus/

READ_DIR_B		=	$(SRC_DIR_B)read/

SHELL_DIR_B 	=	$(SRC_DIR_B)shell/
# <BONUS/>

CC				=	gcc

FLAGS			=	-c -Wall -Wextra  -I

all: $(NAME)

$(NAME):
	@make -C $(PRINTF_DIR)
	$(CC) $(SRC_DIR)*.c $(READ_DIR)ft_*.c $(SHELL_DIR)ft_*.c -lftprintf -L $(PRINTF_DIR)  -o  $(NAME)
	@echo "Done."

$(NAME_BONUS):
	@make -C $(PRINTF_DIR)
	$(CC) $(SRC_DIR_B)*.c $(READ_DIR_B)ft_*.c $(SHELL_DIR_B)ft_*.c -lftprintf -L $(PRINTF_DIR)  -o  $(NAME_BONUS)
	@echo "BONUS Done."

debug:
	$(CC) -g $(SRC_DIR)*.c $(READ_DIR)ft_*.c $(SHELL_DIR)ft_*.c -lftprintf -L $(PRINTF_DIR)    -o  $(NAME)
	@echo "Debug Done."

compile:
	$(CC) $(SRC_DIR)*.c $(READ_DIR)ft_*.c $(SHELL_DIR)ft_*.c -lftprintf -L $(PRINTF_DIR)    -o  $(NAME)

crun: compile
	clear
	@./$(NAME)

clean:
	@make -C $(PRINTF_DIR) clean
	@echo "Cleaning $(NAME)..."

fclean: clean
	@make -C $(PRINTF_DIR) fclean
	@rm -f $(READ_DIR)*.o
	@rm -f $(SHELL_DIR)*.o
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@rm -f $(IMG)
	@echo "Cleaning $(NAME)..."

bonus: $(NAME_BONUS)

bre: fclean bonus

bebug:
	$(CC) -g $(SRC_DIR_B)*.c $(READ_DIR_B)ft_*.c $(SHELL_DIR_B)ft_*.c -lftprintf -L $(PRINTF_DIR)  -o  $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean
