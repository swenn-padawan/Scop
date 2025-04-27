#-VAR--------------------------------------------------------------------------#

NAME			:=	scop

CC				:=	cc

CFLAGS			:=	-Wall -Werror -Wextra -g

OTHERS_FLAGS	:=    -lSDL2 -lm

IFLAGS			:=	-I ./includes -I ./libs/MacroLibX/includes -I ./libs/Libft/include

LIBFT_PATH		:=	libs/Libft

MACRO_PATH		:=	libs/MacroLibX
	
OBJS_DIR		:=	.build

RM				:=	rm -rf

DIR_UP			=	mkdir -p $(@D)

#-MANDA------------------------------------------------------------------------#

SRCS_DIR		:=	srcs

SRCS_MANDA		:=	parsing/get_obj.c \

SRCS_MANDA		:=	$(addprefix $(SRCS_DIR)/, $(SRCS_MANDA))

OBJS_MANDA		:=	$(addprefix $(OBJS_DIR)/, $(SRCS_MANDA:.c=.o))

#-BONUS------------------------------------------------------------------------#

#we will see later...



#-COMPILATION-------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(MACRO_PATH)/libmlx.so $(LIBFT_PATH)/libft.a $(OBJS_MANDA)
	@$(CC) $(CFLAGS) $(OBJS_MANDA) $(LIBFT_PATH)/libft.a $(MACRO_PATH)/libmlx.so $(OTHERS_FLAGS) -o $(NAME)
	@printf "$(GREEN)$(BOLD)$(ITALIC)■$(RESET)  building	$(GREEN)$(BOLD)$(ITALIC)$(NAME)$(RESET)\n"

$(MACRO_PATH)/libmlx.so:
	@make -C $(MACRO_PATH) -s -j

$(LIBFT_PATH)/libft.a:
	@make -C $(LIBFT_PATH) -s

#bonus:
#$(NAME_BONUS): $(MACRO_PATH)/libmlx.so $(LIBFT_PATH)/libft.a $(OBJS_MANDA) $(OBJS_BONUS)
#	@$(CC) $(CFLAGS) $^ $(OTHERS_FLAGS) $(NAME_BONUS)

$(OBJS_DIR)/%.o: %.c
	@$(DIR_UP)
	@printf "$(CYAN)$(BOLD)$(ITALIC)■$(RESET)  compiling	$(GRAY)$(BOLD)$(ITALIC)$^$(RESET)\n"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

clean:
	@$(RM) $(OBJS_DIR)
	@make clean -C $(LIBFT_PATH) -s
	@make clean -C $(MACRO_PATH) -s
	@printf "$(RED)$(BOLD)$(ITALIC)■$(RESET)  cleaned	$(RED)$(BOLD)$(ITALIC)$(MLX_DIR)$(RESET)\n"

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@make fclean -C $(LIBFT_PATH) -s
	@make fclean -C $(MACRO_PATH) -s
	@printf "$(RED)$(BOLD)$(ITALIC)■$(RESET)  cleaned	$(RED)$(BOLD)$(ITALIC)$ $(NAME) $(RESET)\n"

remake: clean all

re: fclean all

#-COLORS-----------------------------------------------------------------------#

BLACK		=	\033[30m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
MAGENTA		=	\033[35m
CYAN		=	\033[36m
WHITE		=	\033[37m
GRAY		=	\033[90m

BOLD		=	\033[1m
ITALIC		=	\033[3m

RESET		=	\033[0m
LINE_CLR	=	\33[2K\r

#------------------------------------------------------------------------------#
