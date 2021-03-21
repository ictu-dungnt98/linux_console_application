#-include sources/app/mqtt/Makefile.mk
-include sources/app/interfaces/Makefile.mk

FLAGS	+= -I./sources/app

VPATH += sources/app

OBJ += $(OBJ_DIR)/app.o
OBJ += $(OBJ_DIR)/shell.o

OBJ += $(OBJ_DIR)/task_list.o
OBJ += $(OBJ_DIR)/task_console.o
OBJ += $(OBJ_DIR)/task_debug.o
