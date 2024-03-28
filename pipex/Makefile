# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 19:41:13 by stephane          #+#    #+#              #
#    Updated: 2024/03/28 01:30:38 by svogrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	pipex
NAME_BONUS	:=	$(NAME)_bonus
NAME_DEBUG	:=	$(NAME)_debug
NAME_DEBUGB	:=	$(NAME)_bonusdebug
NAME_SAN	:=	$(NAME)_sanitize
NAME_SANB	:=	$(NAME)_bonussanitize

# sources ---------------------------------------------------------------------#

DIR_SRC		:=	src
SRC			:=	main.c \
				cmd_path.c \
				cmd_to_argv.c \
				exec_cmd.c \
				exit.c \
				redirection.c \
				str.c 

SRC			:=	$(SRC:%=$(DIR_SRC)/%)

# sources bonus ---------------------------------------------------------------#

SRC_BONUS	:=	bonus/main_bonus.c \
				bonus/heredoc_bonus.c \
				bonus/pipex_bonus.c \
				bonus/process_bonus.c \
				cmd_path.c \
				cmd_to_argv.c \
				exec_cmd.c \
				exit.c \
				redirection.c \
				str.c

SRC_BONUS	:=	$(SRC_BONUS:%=$(DIR_SRC)/%)

# includes --------------------------------------------------------------------#

DIR_INC		:=	libft/include \
				include
I_FLAG		:=	$(addprefix -I,$(DIR_INC)) -MMD -MP
				
# library ---------------------------------------------------------------------#

LIB_FT		:=	libft/libf.a

L_FLAG		:=	libft
L_FLAG		:=	$(addprefix -L,$(L_FLAG))

l_FLAG		:=	ft
l_FLAG		:=	$(addprefix -l,$(l_FLAG))

# objects ---------------------------------------------------------------------#

DIR_BUILD	:=	.build
OBJ			:=	$(SRC:$(DIR_SRC)/%.c=$(DIR_BUILD)/%.o)
OBJ_BONUS	:=	$(SRC_BONUS:$(DIR_SRC)/%.c=$(DIR_BUILD)/%.o)
OBJ_DEBUG	:=	$(SRC:$(DIR_SRC)/%.c=$(DIR_BUILD)/debug/%.o)
OBJ_DEBUGB	:=	$(SRC_BONUS:$(DIR_SRC)/%.c=$(DIR_BUILD)/debugbonus/%.o)
OBJ_SAN		:=	$(SRC:$(DIR_SRC)/%.c=$(DIR_BUILD)/sanitize/%.o)
OBJ_SANB	:=	$(SRC_BONUS:$(DIR_SRC)/%.c=$(DIR_BUILD)/sanitize/%.o)

DEPS		:=	$(OBJ:.o=.d) $(OBJ_SAN:.o=.d) $(OBJ_BONUS:.o=.d)

# compilation -----------------------------------------------------------------#

CC			:=	cc
CC_FLAGS	:=	-Wall -Wextra -Werror

VAL_FLAGS	:=	--leak-check=full --track-origins=yes --track-fds=yes
VAL_FLAGS_C	:=	 --show-leak-kinds=all --trace-children=yes

SAN_FLAGS	:=	-fsanitize=address -g

# make ------------------------------------------------------------------------#

MAKEFLAGS	+=	--no-print-directory

# run -------------------------------------------------------------------------#

RUNARGS		:=	Makefile cat cat out

#------------------------------------------------------------------------------#
# rules                                                                        #
#------------------------------------------------------------------------------#

all: 
	@$(MAKE) -j makeall

clean:
	@$(MAKE) -C libft clean
	@rm -rf $(DIR_BUILD)

fclean:
	@$(MAKE) -C libft fclean
	@rm -rf $(DIR_BUILD)
	@rm -f $(NAME) $(NAME_BONUS) $(NAME)_sanitized gmon.out 

re: fclean
	@$(MAKE) -j makeall

bonus:
	@$(MAKE) -j makebonus

rebonus: fclean bonus

run: all
	- ./$(NAME) $(RUNARGS)

runbonus: bonus
	- ./$(NAME_BONUS) Makefile cat wc cat out

debug:
	@$(MAKE) -j makedebug

debugbonus:
	@$(MAKE) -j makedebugb

valgrind: debug
	- valgrind $(VAL_FLAGS) $(VAL_FLAGS_C) ./$(NAME_DEBUG) $(RUNARGS)

valgrind_p: debug
	- valgrind $(VAL_FLAGS) ./$(NAME_DEBUG) $(RUNARGS)

sanitize:
	@$(MAKE) -j makesanitize
	- ./$(NAME_SAN) $(RUNARGS)

sanitizebonus:
	@$(MAKE) -j makesanitizeb
	- ./$(NAME_SANB) $(RUNARGS)

makeall:		$(NAME)
makebonus:		$(NAME_BONUS)
makedebug:		$(NAME_DEBUG)
makedebugb:		$(NAME_DEBUGB)
makesanitize:	$(NAME_SAN)
makesanitizeb:	$(NAME_SANB)

$(NAME): $(OBJ)
	@$(MAKE) -j -C libft
	@$(CC) $(CC_FLAGS) $(OBJ) $(L_FLAG) $(l_FLAG) -o $(NAME)
	$(info created : $(NAME))

$(NAME_BONUS): $(OBJ_BONUS)
	@$(MAKE) -j -C libft
	@$(CC) $(CC_FLAGS) $(OBJ_BONUS) $(L_FLAG) $(l_FLAG) -o $(NAME_BONUS)
	$(info created : $(NAME_BONUS))

$(NAME_DEBUG): $(OBJ_DEBUG)
	@$(MAKE) -j -C libft
	@$(CC) $(CC_FLAGS) $(OBJ_DEBUG) $(L_FLAG) $(l_FLAG) -g -o $(NAME_DEBUG)
	$(info created : $(NAME_DEBUG))

$(NAME_DEBUGB): $(OBJ_DEBUGB)
	@$(MAKE) -j -C libft
	@$(CC) $(CC_FLAGS) $(OBJ_DEBUGB) $(L_FLAG) $(l_FLAG) -g -o $(NAME_DEBUGB)
	$(info created : $(NAME_DEBUGB))

$(NAME_SAN): $(OBJ_SAN)
	@$(MAKE) -j -C libft
	@$(CC) $(OBJ_SAN) $(L_FLAG) $(l_FLAG) $(SAN_FLAGS) -o $(NAME_SAN)
	$(info created : $(NAME_SAN))

$(NAME_SANB): $(OBJ_SANB)
	@$(MAKE) -j -C libft
	@$(CC) $(OBJ_SANB) $(L_FLAG) $(l_FLAG) $(SAN_FLAGS) -o $(NAME_SANB)
	$(info created : $(NAME_SANB))

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) -c $< -o $@
	$(info created : $@)

$(DIR_BUILD)/debug/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) $(DEBUG_FLAGS) -c $< -o $@
	$(info created : $@)

$(DIR_BUILD)/debugbonus/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) $(DEBUG_FLAGS) -c $< -o $@
	$(info created : $@)

$(DIR_BUILD)/sanitize/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) $(SAN_FLAGS) -c $< -o $@
	$(info created : $@)

-include $(DEPS)

#------------------------------------------------------------------------------#
# specifications                                                               #
#------------------------------------------------------------------------------#

.PHONY: all \
		clean \
		fclean \
		bonus \
		re \
		rebonus \
		run \
		runbonus \
		debug \
		debugbonus \
		valgrind \
		valgrind_p \
		sanitize \
		sanitizebonus \
		gprof \
		makeall \
		makebonus \
		makedebug \
		makedebugb \
		makesanitize \
		makesanitizeb