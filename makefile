TARGET = main

# DIRECTORIES OPTIONS
SRCS_DIR = srcs
INCS_DIR = includes
OBJS_DIR = objs
BIN_DIR  = bin

# COMPILER OPTIONS  
CC          = gcc
FLAGS       = -Wall -Wextra -Werror -g -I$(INCS_DIR)
LINK        =  

# COMPILATION
INCLUDES = $(wildcard $(INCS_DIR)/*.h)
SOURCES  = main.c
OBJS     = $(addprefix $(OBJS_DIR)/,$(SOURCES:.c=.o))

# RUN
ARGS = "img/img(15x15).jpeg"

# FONT
MAGENTA  = \e[35m
CYAN     = \e[36m
WHITE    = \e[37m
YELLOW   = \e[33m
RED      = \e[31m
GREEN    = \e[32m

BOLD     = \e[1m
RST      = \e[0m
CLEAR    = \e[2J
CUR_HOME = \e[H


all: $(BIN_DIR)/$(TARGET)


$(BIN_DIR)/$(TARGET): $(OBJS) | mkdir_bin
	@echo "\n$(RED)--SOURCES FILE FOUND : $(RST)$(BOLD)$(SOURCES)$(RST)"
	@echo "$(YELLOW)--OBJECTS FILE FOUND : $(RST)$(BOLD)$(OBJS)$(RST)"
	@echo "\n$(CYAN)~LINKING $(RST)$(BOLD)$<$(RST)$(CYAN) TO EXECUTABLE TARGET $(RST)$(BOLD)$@$(RST)"
	@$(CC) $^ -o $@ $(FLAGS) $(LINK)
	@echo "$(GREEN)-> FINISHED!$(RST)"


$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES) | mkdir_obj
	@echo "$(MAGENTA)~COMPILING $(RST)$(BOLD)$<$(RST)$(MAGENTA) TO $(RST)$(BOLD)$@$(RST)"
	@$(CC) -c $< -o $@ $(FLAGS)


$(OBJS_DIR)/$(TARGET).o: $(TARGET).c $(INCLUDES) | mkdir_obj
	@echo "$(MAGENTA)~COMPILING $(WHITE)$(BOLD)$<$(RST)$(MAGENTA) TO $(RST)$(BOLD)$@$(RST)"
	@$(CC) -c $< -o $@ $(FLAGS)


run: all
	@echo "$(CLEAR)$(CUR_HOME)\r"
	@./$(BIN_DIR)/$(TARGET) $(ARGS)


mkdir_obj: 
	@mkdir -p $(OBJS_DIR)

mkdir_bin: 
	@mkdir -p $(BIN_DIR)

clean:
	@echo "$(CLEAR)$(CUR_HOME)$(RED)$(BOLD)~CLEANING DIRECTORY... $(RST)"
	@rm -rf $(OBJS_DIR)
	@rm -rf $(BIN_DIR)/$(TARGET)
	@echo "$(GREEN)-> FINISHED!$(RST)"


.PHONY: all clean run mkdir_obj mkdir_bin