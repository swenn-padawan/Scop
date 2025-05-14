#-VAR--------------------------------------------------------------------------#

NAME			:=	scop

CC				:=	c++

CFLAGS			:=	-Wall -Werror -Wextra -g

IFLAGS			:=	-I ./includes
	
OBJS_DIR		:=	.build

RM				:=	rm -rf

DIR_UP			=	mkdir -p $(@D)

VERBOSE		?=	0

ifeq ($(VERBOSE), 1)
	CFLAGS += -DVERBOSE
endif

ifeq ($(LAZY), 1)
	CFLAGS		:= -Wall -Wextra -g
endif

ifeq ($(VL), 1)
	CFLAGS		:= -Wall -Wextra
	CFLAGS += -DVERBOSE
endif


#-MANDA------------------------------------------------------------------------#

SRCS_DIR		:=	srcs

SRCS		:=	main.cpp \
					parsing/SCOP_File.cpp \
					parsing/SCOP_parsingUtils.cpp \
					parsing/SCOP_Object.cpp \

SRCS		:=	$(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

#-COMPILATION-------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(OTHERS_FLAGS) -o $(NAME)
	@printf "$(GREEN)$(BOLD)$(ITALIC)■$(RESET)  building	$(GREEN)$(BOLD)$(ITALIC)$(NAME)$(RESET)\n"

$(OBJS_DIR)/%.o: %.cpp
	@$(DIR_UP)
	@printf "$(CYAN)$(BOLD)$(ITALIC)■$(RESET)  compiling	$(GRAY)$(BOLD)$(ITALIC)$^$(RESET)\n"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

clean:
	@$(RM) $(OBJS_DIR)
	@printf "$(RED)$(BOLD)$(ITALIC)■$(RESET)  cleaned	$(RED)$(BOLD)$(ITALIC)$(MLX_DIR)$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
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
