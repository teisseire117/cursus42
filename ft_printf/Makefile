NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

RM = rm -f

CP = cp

SRCS =	flag_add_padding.c \
	flag_add_flag_characters_options.c \
	flag_add_precision.c \
	flag_convert.c \
	flag_parser.c \
	ft_printf.c

LFT = libft.a

LFT_DIR = ./libft

SRCS_DIR = ./

INCLUDES = ./

GNL_INCLUDES = get_next_line/

OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS) $(LFT)
	$(CP) $(LFT_DIR)/$(LFT) $(NAME)
	$(AR) $(NAME) $(OBJS)

$(LFT):
	make -C $(LFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -I$(LFT_DIR) -c $< -o $@

clean:
	make $@ -C $(LFT_DIR)
	$(RM) $(OBJS) 

fclean: clean
	make $@ -C $(LFT_DIR)
	$(RM) $(NAME)

re: clean all

.PHONY: bonus all clean fclean re $(LFT)
