NAME = bsq

### SRCS #######################################################################

PATH_SRCS = srcs/

SRCS += bsq.c
SRCS += load_map.c
SRCS += fill_lines.c
SRCS += find_solution.c
SRCS += ft_printf.c
SRCS += memory.c
SRCS += parse_options.c
SRCS += print_map.c
SRCS += read_map.c
SRCS += string.c
SRCS += string2.c
SRCS += strnum.c
SRCS += strnum2.c
#SRCS += find_solution.backtrack.c
#SRCS += test_map.c

vpath %.c $(PATH_SRCS)

### OBJS #######################################################################

PATH_OBJS = objs/

OBJS = $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

### INCLUDES ###################################################################

INCLUDES_BSQ = includes/

HEADER += -I $(INCLUDES_BSQ)

### COMPILATION ################################################################

CC = cc
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror

ifeq ($(debug), true)
	CFLAGS += -fsanitize=address,undefined -g3
endif
ifeq ($(debugger), true)
	CFLAGS += -g3
endif

### RULE ######################################################################

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(PATH_OBJS)/%.o: %.c
		mkdir -p $(PATH_OBJS)
		$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

clean:
	$(RM) -r $(PATH_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re
