# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niclaw <nicklaw@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/24 13:59:17 by niclaw            #+#    #+#              #
#    Updated: 2023/05/16 16:07:25 by niclaw           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### EXECUTABLE ###
# This is where you want to put the name of your program or library that you will be compiling

NAME	= philo

### DIR ###
# all the dir to neatly keep your .c and .h

SRC_DIR		= 
BONUS_DIR	= bonus/
HEAD		= 
SHARE_DIR	= share/
BUILD_DIR =	./build/

### TESTER GIT URL ###
# add some git url to your makefile to make your evaluator life easier

TESTER1		=
TESTER2		=
TESTER3		=
TESTER4		=

### SOURCE FILE ###
# the name of your .c go here. SRC is for mandatory, BONUS is for the bonus. 
# SHARE is for .c file that your mandatory and bonus use. LIBFT is where your specific libft .c file go.

SRC	=	main.c phil_action.c phil_manage.c phil_util.c phil_util2.c

BONUS	=	

SHARE	=

### PATH ###
# DO NOT CHANGE
SRCS		= ${addprefix ${SRC_DIR}, ${SRC}}
BONUS_SRCS	= ${addprefix ${BONUS_DIR}, ${BONUS}}
SHARE_SRCS	= ${addprefix ${SHARE_DIR}, ${SHARE}}

### OBJECT FILE ###
# DO NOT CHANGE
OBJS		= ${SRCS:%.c=$(BUILD_DIR)%.o}
BONUS_OBJS	= ${BONUS_SRCS:.c=.o}
SHARE_OBJS	= ${SHARE_SRCS:.c=.o}

## LIBFT TARGET ##
LIBFT	= ${LIB_DIR}libft.a
PRINT	= ${PRINT_DIR}libftprintf.a

### Philosopher ###
# Extra specific for philosopher project
PTHR = -pthread
ARG  =  4 90 60 60
### COMPILATION ###
# the compilation flag that will we will use for the project

CC	= gcc
CFLAGS	=   -g -Wall -Wextra -Wextra $(PTHR) 
#-fsanitize=leak  ASAN_OPTIONS=detect_leaks=1
RM	= rm -f

### COLORS ###
# up to your creativity 
NOC		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m

### TMP ###
# if needed
MSG = "Upload to git"


### RULES ###
${NAME}:	${OBJS} ${SHARE_OBJS} ${LIB_DIR}
	${CC} ${CFLAGS} ${OBJS} ${SHARE_OBJS}\
	-o ${NAME}
	@echo "$(GREEN) $@ Linking done!$(NOC)"

$(BUILD_DIR)%.o:	%.c 
	@mkdir -p $(BUILD_DIR)${SRC_DIR}
	@mkdir -p $(BUILD_DIR)${SHARE_DIR}
	@mkdir -p $(BUILD_DIR)${BONUS_DIR}
	${CC} ${CFLAGS} -c $< -o $(BUILD_DIR)${<:.c=.o}
	
#build: 
#	@mkdir -p ${addprefix ${BUILD}, ${SRC_DIR}}
#	@mkdir -p ${addprefix ${BUILD}, ${SRC_DIR}/utils}
#	@mkdir -p ${addprefix ${BUILD}, ${SHARE_DIR}}
#	@mkdir -p ${addprefix ${BUILD}, ${BONUS_DIR}}
#	@echo "Build done!"
	 


all: ${NAME}

bonus:	${BONUS_OBJS} ${SHARE_OBJS} 
	@${CC} ${CFLAGS} ${addprefix ${BUILD}, ${BONUS_OBJS}} ${addprefix ${BUILD}, ${SHARE_OBJS}}\
	-o ${BONUS_NAME}
	@echo "$(GREEN)${BONUS_NAME}$(NOC)"

clean:
	@echo "$(RED)clean$(NOC)"
	${RM} -r ${BUILD_DIR}

fclean:	clean
	@echo "$(RED)fclean$(NOC)"
	${RM} ${NAME} ${BONUS_NAME}

re:	fclean all


mem:	
	leaks --atExit -- ./$(NAME) $(ARG)
# valgrind  --leak-check=summary  --show-leak-kinds=all ./$(NAME) $(ARG)
	#valgrind --tool=drd --first-race-only=yes ./$(NAME) $(ARG)

#tester:

norm:
	norminette

gitpush:
	git add .
	git status
	git commit -m "${MSG}"
	git push

help:
	@clear
	@echo "$(GREEN)Avaibles options:$(NOC)"
	@echo "$(RED)==================$(NOC)"
	@echo "$(RED)| $(YELLOW)make ${NAME} $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make bonus     $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make norm      $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make tester    $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make clean     $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make fclean    $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make re        $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make help      $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make test      $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make mem      $(RED)|$(NOC)"
	@echo "$(RED)==================$(NOC)"

object:
	@echo $(OBJS)
.PHONY:	all clean fclean re bonus mem norm name build

# this will add the file dependencies below, i.e. it modifies this file
depend:
		makedepend -I${HEAD} -I${LIBDIR} -- ${SRC_DIR}$(SRCS)

# DO NOT DELETE THIS LINE -- make depend depends on it.