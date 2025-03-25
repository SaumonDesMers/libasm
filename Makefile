NAME		= libasm.a
TESTER_NAME = libasm_test

CC			:= clang
CFLAGS		:= -Wall -Wextra -Werror -z noexecstack -g3
AR			:= ar rcs
AS			:= nasm
ASFLAGS		:= -f elf64 -g

SRC_DIR		= src
SRCS		= $(patsubst %, $(SRC_DIR)/%, strlen.s strcpy.s)

INC_DIR 	= include

OBJ_DIR		= obj
OBJS		= $(SRCS:$(SRC_DIR)/%.s=$(OBJ_DIR)/%.o)

DEP_DIR		= dep
DEP			= $(SRC:$(SRC_DIR)/%.cpp=$(DEP_DIR)/%.d)


all: $(NAME)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

-include $(DEP)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
			@mkdir -p $(OBJ_DIR) $(DEP_DIR)
			$(CC) $(CFLAGS) -o $@ -MMD -MF $(DEP_DIR)/$*.d -I $(INC_DIR) -c $<

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.s
			@mkdir -p $(OBJ_DIR) $(DEP_DIR)
			$(AS) $(ASFLAGS) -o $@ -MD -MF $(DEP_DIR)/$*.d $<

$(TESTER_NAME): $(NAME) main.c
			$(CC) $(CFLAGS) -o $(TESTER_NAME) main.c -L. -lasm

test: $(TESTER_NAME)
			./$(TESTER_NAME)

clean:
			$(RM) $(OBJS)

fclean:	clean
			$(RM) $(NAME) $(TESTER_NAME)

re:	fclean
			$(MAKE) all

.PHONY:	all clean fclean re
