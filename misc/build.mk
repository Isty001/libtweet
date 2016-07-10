ROOT_DIR=$(shell pwd)

WARN=-Wextra -Wall -Wstrict-prototypes -Wunreachable-code
DEPENDENCIES=-lcurl -loauth
CFLAGS=$(WARN) $(DEPENDENCIES) -O2 -std=gnu11 -D _GNU_SOURCE -g

define compile =
	gcc $(CFLAGS) $1 $2
endef

SOURCE_FILES=$(ROOT_DIR)/lib/*.c
BUILD_DIR=$(ROOT_DIR)/build
LIB_FILE=libtweet.so

define compile_lib =
	cd $(BUILD_DIR) && \
	for SOURCE in $(SOURCE_FILES) ; do \
		$(call compile,$$SOURCE,-c -fpic) ; \
	done

	gcc -shared -o $(BUILD_DIR)/$(LIB_FILE) $(BUILD_DIR)/*.o
endef


INSTALLED_LIB_DIR="/lib"

define install_lib =
	mv $(BUILD_DIR)/$(LIB_FILE) $(INSTALLED_LIB_DIR)
endef


INCLUDE_DIR=$(ROOT_DIR)/include
INSTALLED_INCLUDE_DIR=/usr/include/tweet

define install_headers =
	rm -rf $(INSTALLED_INCLUDE_DIR)/*

	mkdir -p $(INSTALLED_INCLUDE_DIR)

	cp $(INCLUDE_DIR)/*.h $(INSTALLED_INCLUDE_DIR)
endef
