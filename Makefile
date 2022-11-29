ifeq ($(OS),Windows_NT)
    CFLAGS += 
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        CFLAGS += -lcurl -lcheck -lsubunit -lpthread -lm -lrt
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            CFLAGS += -lcurl -lcheck -lsubunit -lpthread -lm -lrt
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            CFLAGS += -lcurl -lcheck -lsubunit -lpthread -lm -lrt
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CFLAGS += -lcurl -lcheck -lsubunit -lpthread -lm -lrt
    endif
    ifeq ($(UNAME_S),Darwin)
        CFLAGS += -lcurl -lcheck -lpthread -lm
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CFLAGS += -lcurl -lcheck -lsubunit -lpthread -lm -lrt
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CFLAGS += -lcurl -lcheck  -lpthread -lm
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CFLAGS += -lcurl -lcheck -lsubunit -lpthread -lm -lrt
    endif
endif
########################################################### 
# Tests
# 
# Below are the builds for Unit testing.
###########################################################

###### HTTP Module
# HTTP Module Unit Testing
######

### HTTP Client
# Client Testing
###
TEST_CLIENT:
	mkdir build
	cd ./src/http; gcc -c ./client/client.c -o ../../build/http.o
	mkdir ./tests/build
	cd ./tests/build; gcc -c ../check_http.c
	gcc ./build/http.o ./tests/build/check_http.o $(CFLAGS) -o ./tests/build/check_http
	cd ./tests/build; ./check_http

CLEAN_TEST_CLIENT:
	rm -rf ./build
	rm -rf ./tests/build