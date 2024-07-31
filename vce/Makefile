RUN_CMD_MKDIR  = @echo "  MKDIR " $@;
RUN_CMD_RM     = @echo "  RM    " $@;

RUN_CMD_AR     = @echo "  AR    " $@;
RUN_CMD_CC     = @echo "  CC    " $@;
RUN_CMD_CXX    = @echo "  CXX   " $@;
RUN_CMD_LTLINK = @echo "  LTLINK" $@;
RUN_CMD_RANLIB = @echo "  RANLIB" $@;
RUN_CMD_RC     = @echo "  RC    " $@;
RUN_CMD_GEN    = @echo "  GEN   " $@;

# directories
BIN_DIR = $(TOP)/$(BLD_DIR)/bin
OBJ_DIR = $(TOP)/$(BLD_DIR)/obj
SRC_DIR = $(TOP)/engine
DEP_DIR = $(TOP)/$(BLD_DIR)/dep

# files
BIN = $(BIN_DIR)/libvce.so
SRC = $(wildcard *.c) $(wildcard **/*.c) $(wildcard **/**/*.c) $(wildcard **/**/**/*.c)
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP = $(SRC:%.c=$(DEP_DIR)/%.d)



CFLAGS  += -fpic

#INCLUDE += -I./



# =============================
# -----------------------------
# VC ENGINE
# -----------------------------

all: $(OBJ)

# =============================



# =============================
# -----------------------------
# VC ENGINE
# -----------------------------

$(BIN): $(OBJ)
	$(RUN_CMD_LTLINK) $(LD) -shared -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(RUN_CMD_CC) $(CC) $(INCLUDE) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

#$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
#	$(RUN_CMD_CC) $(CC) $(INCLUDE) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(<:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d) -MT $@ -o $@ -c $<

# =============================

#-include $(DEP)

.PHONY: all
