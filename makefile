include misc/build.mk


all:
	$(call compile_lib)
	sudo make install
	make clean

install:
	$(call install_headers)
	$(call install_lib)

clean:
	rm $(shell find $(BUILD_DIR) -name '*.o')

test-unit:
	make all && $(call compile,test/unit/*.c,-l cmocka -l tweet -o unit_test.o) && ./unit_test.o

run-dev:
	make all
	$(call compile,dev.c,$(DEPENDENCIES) -l tweet -o dev.o) && ./dev.o && rm dev.o

