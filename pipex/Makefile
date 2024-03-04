#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stephane <stephane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 19:41:13 by stephane          #+#    #+#              #
#    Updated: 2024/03/03 13:40:25 by stephane         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		:=	pipex
NAME_BONUS	:=	$(NAME)_bonus

# sources ---------------------------------------------------------------------#

DIR_SRC		:=	src
SRC			:=	main.c \
				cmd_path.c

SRC			:=	$(SRC:%=$(DIR_SRC)/%)

# sources bonus ---------------------------------------------------------------#

SRC_BONUS	:=	main.c 

SRC_BONUS	:=	$(SRC_BONUS:%=$(DIR_SRC)/%)

# includes --------------------------------------------------------------------#

DIR_INC		:=	libft/include \
				include
I_FLAG		:=	$(addprefix -I,$(DIR_INC)) -MMD -MP
				
# library ---------------------------------------------------------------------#

L_FLAG		:=	libft

L_FLAG		:=	$(addprefix -L,$(L_FLAG))

l_FLAG		:=	ft

l_FLAG		:=	$(addprefix -l,$(l_FLAG))

# objects ---------------------------------------------------------------------#

DIR_BUILD	:=	.build
OBJ			:=	$(SRC:$(DIR_SRC)/%.c=$(DIR_BUILD)/%.o)
OBJ_SAN		:=	$(SRC:$(DIR_SRC)/%.c=$(DIR_BUILD)/sanitized/%.o)
OBJ_BONUS	:=	$(SRC_BONUS:$(DIR_SRC)/%.c=$(DIR_BUILD)/%.o)

DEPS		:=	$(OBJ:.o=.d) $(OBJ_SAN:.o=.d) $(OBJ_BONUS:.o=.d)

# compilation -----------------------------------------------------------------#

CC			:=	cc
CC_FLAGS	:=	-Wall -Wextra -Werror

# make ------------------------------------------------------------------------#

MAKEFLAGS	+=	--no-print-directory

# run -------------------------------------------------------------------------#

RUNARGS		:=	infile cmd1 cmd2 outfile

#------------------------------------------------------------------------------#
# rules                                                                        #
#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -j -C libft
	@$(CC) $(CC_FLAGS) $(OBJ) $(L_FLAG) $(l_FLAG) -o $(NAME)
	$(info created : $(NAME))

bonusonly: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) 
	@$(MAKE) -j -C libft
	@$(CC) $(CC_FLAGS) $(OBJ_BONUS) $(L_FLAG) $(l_FLAG) -o $(NAME_BONUS)
	$(info created : $(NAME_BONUS))

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) -pg -c $< -o $@
	$(info created : $@)

$(DIR_BUILD)/sanitized/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CC_FLAGS) $(I_FLAG) -fsanitize=address -c $< -o $@
	$(info created : $@)

-include $(DEPS)

clean:
	@$(MAKE) -C libft clean
	@rm -f $(OBJ) $(OBJ_BONUS) $(OBJ_SAN) $(DEPS)

fclean: clean
	@$(MAKE) -C libft fclean
	@rm -f $(NAME) $(NAME_BONUS) $(NAME)_sanitized gmon.out 

re: fclean
	@$(MAKE) -j all

rebonus: fclean
	@$(MAKE) -j bonusonly

bonus:
	@$(MAKE) -j bonusonly

run: $(NAME)
	@- ./$(NAME) $(RUNARGS)

valgrind: $(NAME)
	@$(CC) $(OBJ) $(L_FLAG) $(L_FLAG) $(l_FLAG) -g -o $(NAME)
	$(info valgrind created : $(NAME))
	@- valgrind --leak-check=full --track-origins=yes --track-fds=yes ./$(NAME) $(RUNARGS)

valgrind_p: $(NAME)
	@$(CC) $(OBJ) $(L_FLAG) $(L_FLAG) $(l_FLAG) -g -o $(NAME)
	$(info valgrind created : $(NAME))
	@- valgrind --child-silent-after-fork=yes --leak-check=full --track-origins=yes --track-fds=yes ./$(NAME) $(RUNARGS)
	
sanitizer: $(OBJ_SAN)
	@$(CC) $(OBJ_SAN) $(L_FLAG) $(L_FLAG) $(l_FLAG) -fsanitize=address -o $(NAME)_sanitized
	@- ./$(NAME)_sanitized test_maps/42.fdf

gprof:
	@$(CC) $(OBJ) $(L_FLAG) $(L_FLAG) $(l_FLAG) -pg -o $(NAME)
	@- ./$(NAME) $(RUNARGS)

#------------------------------------------------------------------------------#
# specifications                                                               #
#------------------------------------------------------------------------------#

.PHONY: all clean fclean re run mlx
#.SILENT: