AR = ar
CC = gcc

BUILD_DIR = build
BUILD_STATIC_DIR = $(BUILD_DIR)/static
BUILD_SHARED_DIR = $(BUILD_DIR)/shared

LIB_NAME = unity
INSTALL_DIR = /usr/local
STATIC_LIB = lib$(LIB_NAME).a
SHARED_LIB = lib$(LIB_NAME).so
LIBRARY_DIR = $(INSTALL_DIR)/lib
INCLUDE_DIR = $(INSTALL_DIR)/include

OBJECTS = $(wildcard *.c)
OBJECTS := $(OBJECTS:.c=.o)
STATIC_OBJS = $(addprefix $(BUILD_STATIC_DIR)/, $(OBJECTS))
SHARED_OBJS = $(addprefix $(BUILD_SHARED_DIR)/, $(OBJECTS))

build: .mkdirs $(BUILD_DIR)/$(SHARED_LIB) $(BUILD_DIR)/$(STATIC_LIB)

$(BUILD_DIR)/$(STATIC_LIB): $(STATIC_OBJS)
	$(AR) -crv $@ $+
	@echo ""

$(BUILD_DIR)/$(SHARED_LIB): $(SHARED_OBJS)
	$(CC) -shared $+ -o $@
	@echo ""

$(BUILD_STATIC_DIR)/%.o: %.c
	$(CC) -MMD -c $< -o $@

$(BUILD_SHARED_DIR)/%.o: %.c
	$(CC) -MMD -c -fPIC $< -o $@

-include $(wildcard $(BUILD_DIR)/*/*.d)

.mkdirs:
	@sudo mkdir -p $(INCLUDE_DIR) $(LIBRARY_DIR)
	@mkdir -p $(BUILD_DIR) $(BUILD_SHARED_DIR) $(BUILD_STATIC_DIR)

clean:
	@rm -rf $(BUILD_DIR)

install: build
	@echo "=============== Install $(LIB_NAME) ==============="
	sudo cp $(LIB_NAME)*.h $(INCLUDE_DIR)
	sudo cp $(BUILD_DIR)/$(STATIC_LIB) $(LIBRARY_DIR)
	sudo cp $(BUILD_DIR)/$(SHARED_LIB) $(LIBRARY_DIR)
	@echo ""

uninstall:
	@echo "=============== Uninstall $(LIB_NAME) ==============="
	sudo rm -f $(LIBRARY_DIR)/$(STATIC_LIB) 
	sudo rm -f $(LIBRARY_DIR)/$(SHARED_LIB)
	sudo rm -f $(INCLUDE_DIR)/$(LIB_NAME)*.h
	@echo ""

.PHONY: .mkdirs build clean install uninstall
