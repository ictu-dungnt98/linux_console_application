-include shsecurityfile/Makefile.mk

CXXFLAGS	+= -I./
CXXFLAGS	+= -I./../../common

VPATH	+= ./

OBJ	+= $(OBJ_DIR)/main.o
