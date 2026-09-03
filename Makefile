# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dancel <dancel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/31 20:16:51 by dancel            #+#    #+#              #
#    Updated: 2026/08/31 20:47:49 by dancel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME
# ============================

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME      = libft_malloc_$(HOSTTYPE).so
LINKNAME  = libft_malloc.so

# GENERIC
# ============================

CC        = cc
CFLAGS    = -Wall -Wextra -Werror -g3 -fPIC -pthread
INCLUDES  = -I includes -I libft

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

SRC_DIR   = srcs
OBJ_DIR   = objects
SRCS      = $(wildcard $(SRC_DIR)/*.c)
OBJS      = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# TARGET
# ============================

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS) $(LIBFT)
	@ln -sf $(NAME) $(LINKNAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

# TEST
# ============================

TEST_SRC = test.c
TEST_BIN = test_malloc

test: $(NAME)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_SRC) -L. -lft_malloc -Wl,-rpath,. -o $(TEST_BIN)
	./$(TEST_BIN)

# CLEANING
# ============================
clean:
	@$(MAKE) clean -s -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -s -C $(LIBFT_DIR)
	rm -f $(NAME) $(LINKNAME) $(TEST_BIN)


# REBUILD
# ============================
re: fclean all

# GHOST
# ============================
.PHONY: all clean fclean re test

