###############################################################################
# author: NinhNN
# date: 6/1/2017
###############################################################################
RPI_SYS_DIR	=
TOOLS_DIR	=
NAME_MODULE	= linux_base
CXX		= g++
CC		= gcc
OBJ_DIR		= build_$(NAME_MODULE)

OPTIMIZE_OPTION	=	-g -O3
WARNNING_OPTION	+=	#-Werror -W -Wno-missing-field-initializers

-include sources/ak/Makefile.mk
-include sources/sys/Makefile.mk
-include sources/app/Makefile.mk
-include sources/common/Makefile.mk
#-include sources/driver/Makefile.mk
#-include sources/networks/Makefile.mk

FLAGS	+= -I/usr/local/include
FLAGS	+= -I/usr/include

# CXX compiler option
FLAGS	+=	$(OPTIMIZE_OPTION)	\
		$(WARNNING_OPTION)	\
		-Wall			\
		-Winline		\
		-pipe			\
		-g			\

# Library paths
LDFLAGS	+= -L/usr/local/lib
LDFLAGS	+= -L/usr/include
LDFLAGS	+= -Wl,-Map=$(OBJ_DIR)/$(NAME_MODULE).map

#Library libs
LDLIBS	+=	-lpthread		\
		-lrt			\
		-lm			\

all: create $(OBJ_DIR)/$(NAME_MODULE)

create:
	@echo mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@echo CXX $<
	@$(CC) -c -o $@ $< $(FLAGS) $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/$(NAME_MODULE): $(OBJ)
	@echo ---------- START LINK PROJECT ----------
	@echo $(CC) -o $@ $^ $(FLAGS)
	@$(CC) -o $@ $^ $(FLAGS) $(LDFLAGS) $(LDLIBS)

.PHONY: copy
copy:
	scp -r ./* root@10.42.0.29:/root/workspace/devs/ak_linux_base

.PHONY: flash
flash:
	@sudo LD_LIBRARY_PATH=/usr/local/lib/ $(OBJ_DIR)/$(NAME_MODULE)

.PHONY: debug
debug:
	sudo gdb $(OBJ_DIR)/$(NAME_MODULE)

.PHONY: install
install:
	cp $(OBJ_DIR)/$(NAME_MODULE) /usr/local/bin

.PHONY: clean
clean:
	@echo rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)
