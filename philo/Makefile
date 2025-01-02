NAME    = philo
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iinclude

SRCDIR  = src
OBJDIR  = obj

SRC     = philo.c \
          init/init_forks.c \
          init/init_param.c \
          init/init_philosopher.c \
          routines/routine_eat.c \
          routines/routine_fork.c \
          routines/routine_handler.c \
          routines/routine_sleep.c \
          routines/routine_think.c \
          monitor/monitor_handler.c \
          monitor/monitor_check.c \
          monitor/monitor_join_thread.c \
          utils/utils_clean.c \
          utils/utils_print.c \
          utils/utils_time.c \
          utils/utils_debug.c \
          utils/utils_mutex_count_eat.c \
          utils/utils_mutex_last_meal.c \
          utils/utils_mutex_state_end.c \
          lib/ft_atoll.c \
          lib/ft_strlen.c \
          lib/garbage_collector.c \
          lib/is_int.c

# Convert each .c file in SRC to a corresponding .o file in OBJDIR
OBJ     = $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Compile each .c into .o inside OBJDIR
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
