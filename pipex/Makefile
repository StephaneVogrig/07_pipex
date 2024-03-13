# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 19:41:13 by stephane          #+#    #+#              #
#    Updated: 2024/03/13 17:21:34 by svogrig          ###   ########.fr        #
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
				exec_cmd.c \
				error.c \
				process.c \
				pipe.c \
				redirection.c \
				str.c \
				token.c

SRC			:=	$(SRC:%=$(DIR_SRC)/%)

# sources bonus ---------------------------------------------------------------#

SRC_BONUS	:=	main.c \
				cmd_path.c \
				exec_cmd.c \
				error.c \
				process.c \
				pipe.c \
				redirection.c \
				str.c \
				token.c

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

DEBUG_FLAGS	:=	-g
VAL_FLAGS	:=	--leak-check=full --track-origins=yes --track-fds=yes
VAL_FLAGS	:=	$(VAL_FLAGS) --show-leak-kinds=all

SAN_FLAGS	:=	-fsanitize=address -g

# make ------------------------------------------------------------------------#

MAKEFLAGS	+=	--no-print-directory

# run -------------------------------------------------------------------------#

RUNARGS		:=	in cat ls out

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
	@- ./$(NAME) $(RUNARGS)

runbonus: bonus
	@- ./$(NAME_BONUS) $(RUNARGS)

debug:
	@$(MAKE) -j makedebug

debugbonus:
	@$(MAKE) -j makedebug

valgrind: debug
	@- valgrind --trace-children=yes $(VAL_FLAGS) ./$(NAME_DEBUG) $(RUNARGS)

valgrind_p: debug
	@- valgrind --child-silent-after-fork=yes $(VAL_FLAGS) ./$(NAME_DEBUG) $(RUNARGS)

sanitize:
	@$(MAKE) -j makesanitize
	@- ./$(NAME_SAN) $(RUNARGS)

sanitizebonus:
	@$(MAKE) -j makesanitizeb
	@- ./$(NAME_SANB) $(RUNARGS)

gprof:
	@$(CC) $(OBJ) $(L_FLAG) $(L_FLAG) $(l_FLAG) -pg -o $(NAME)
	@- ./$(NAME) $(RUNARGS)

makeall:		$(NAME)
makebonus:		$(NAME_BONUS)
makedebug:		$(NAME_DEBUG)
makedebugb:		$(NAME_DEBUGB)
makesanitize:	$(NAME_SAN)
makesanitizeb:	$(NAME_SANB)

$(NAME): $(OBJ) $(LIB_FT)
	@$(CC) $(CC_FLAGS) $(OBJ) $(L_FLAG) $(l_FLAG) -o $(NAME)
	$(info created : $(NAME))

$(NAME_BONUS): $(OBJ_BONUS) $(LIB_FT)
	@$(CC) $(CC_FLAGS) $(OBJ_BONUS) $(L_FLAG) $(l_FLAG) -o $(NAME_BONUS)
	$(info created : $(NAME_BONUS))

$(NAME_DEBUG): $(OBJ_DEBUG) $(LIB_MLX) $(LIB_FT)
	@$(CC) $(CC_FLAGS) $(OBJ_DEBUG) $(L_FLAG) $(l_FLAG) -g -o $(NAME_DEBUG)
	$(info created : $(NAME_DEBUG))

$(NAME_DEBUGB): $(OBJ_DEBUGB) $(LIB_MLX) $(LIB_FT)
	@$(CC) $(CC_FLAGS) $(OBJ_DEBUGB) $(L_FLAG) $(l_FLAG) -g -o $(NAME_DEBUGB)
	$(info created : $(NAME_DEBUGB))

$(NAME_SAN): $(OBJ_SAN) $(LIB_MLX) $(LIB_FT)
	@$(CC) $(OBJ_SAN) $(L_FLAG) $(l_FLAG) $(SAN_FLAGS) -o $(NAME_SAN)
	$(info created : $(NAME_SAN))

$(NAME_SANB): $(OBJ_SANB) $(LIB_MLX) $(LIB_FT)
	@$(CC) $(OBJ_SANB) $(L_FLAG) $(l_FLAG) $(SAN_FLAGS) -o $(NAME_SANB)
	$(info created : $(NAME_SANB))

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) -pg -c $< -o $@
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

$(LIB_FT):
	@$(MAKE) -j -C libft

-include $(DEPS)

#------------------------------------------------------------------------------#
# specifications                                                               #
#------------------------------------------------------------------------------#

.PHONY: all clean fclean re run mlx
#.SILENT: