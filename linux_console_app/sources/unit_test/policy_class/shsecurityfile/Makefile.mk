CXXFLAGS	+= -I./shsecurityfile
CXXFLAGS	+= -I./shsecurityfile/AES
CXXFLAGS	+= -I./shsecurityfile/Crypt
CXXFLAGS	+= -I./shsecurityfile/DB

VPATH += shsecurityfile
VPATH += shsecurityfile/AES
VPATH += shsecurityfile/Crypt
VPATH += shsecurityfile/DB

OBJ += $(OBJ_DIR)/AES.o
OBJ += $(OBJ_DIR)/SHCrypt.o
OBJ += $(OBJ_DIR)/DB.o
OBJ += $(OBJ_DIR)/SHSecurityFile.o
