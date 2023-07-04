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
# General Builds
# 
# Below are the builds for the library
###########################################################
all: 
	mkdir build
	cd ./src/http; gcc -c ./client/client.c -o ../../build/http.o; gcc -c ./utils/headers.c -o ../../build/headers.o; gcc -c ./utils/response.c -o ../../build/response.o; gcc -c ./utils/request.c -o ../../build/request.o

headers:
	mkdir build
	cd ./src/http; gcc -c ./utils/headers.c -o ../../build/headers.o;

request: 
	mkdir build
	cd ./src/http; gcc -c ./utils/headers.c -o ../../build/headers.o; gcc -c ./utils/request.c -o ../../build/request.o

response:
	mkdir build
	cd ./src/http; gcc -c ./utils/headers.c -o ../../build/headers.o; gcc -c ./utils/response.c -o ../../build/response.o;

client:
	mkdir build
	cd ./src/http; gcc -c ./client/client.c -o ../../build/http.o; gcc -c ./utils/headers.c -o ../../build/headers.o; gcc -c ./utils/response.c -o ../../build/response.o; gcc -c ./utils/request.c -o ../../build/request.o

debug:
	mkdir build
	cd ./src/http; gcc -g -c ./client/client.c -o ../../build/http.o; gcc -g -c ./utils/headers.c -o ../../build/headers.o; gcc -g -c ./utils/response.c -o ../../build/response.o; gcc -g -c ./utils/request.c -o ../../build/request.o

clean: 
	rm -rf ./build
	rm -rf ./tests/build
	rm -rf ./debugs/build


########################################################### 
# Tests
# 
# Below are the builds for Unit testing.
###########################################################
test: all; mkdir ./tests/build
	cd ./tests/build; gcc -c ../request.c
	gcc ./build/request.o ./tests/build/request.o $(CFLAGS) -o ./tests/build/request
	cd ./tests/build; gcc -c ../headers.c
	gcc ./build/headers.o ./tests/build/headers.o $(CFLAGS) -o ./tests/build/headers
	cd ./tests/build; gcc -c ../http.c
	gcc ./build/http.o ./build/headers.o ./build/request.o ./build/response.o ./tests/build/http.o $(CFLAGS) -o ./tests/build/http
	cd ./tests/build; ./request; ./headers; ./http;

leaktest: all; mkdir ./tests/build
	cd ./tests/build; gcc -c ../request.c
	gcc ./build/request.o ./tests/build/request.o $(CFLAGS) -o ./tests/build/request
	cd ./tests/build; gcc -c ../headers.c
	gcc ./build/headers.o ./tests/build/headers.o $(CFLAGS) -o ./tests/build/headers
	cd ./tests/build; gcc -c ../http.c
	gcc ./build/http.o ./build/headers.o ./build/request.o ./build/response.o ./tests/build/http.o $(CFLAGS) -o ./tests/build/http
	cd ./tests/build; valgrind ./request; valgrind ./headers; valgrind ./http;

testrequest: request; mkdir ./tests/build
	cd ./tests/build; gcc -c ../request.c
	gcc ./build/request.o ./tests/build/request.o $(CFLAGS) -o ./tests/build/request
	cd ./tests/build; ./request;

leaktestrequest: request; mkdir ./tests/build
	cd ./tests/build; gcc -c ../request.c
	gcc ./build/request.o ./tests/build/request.o $(CFLAGS) -o ./tests/build/request
	cd ./tests/build; valgrind ./request;

testresponse: response; mkdir ./tests/build
	cd ./tests/build; gcc -c ../response.c
	gcc ./build/response.o ./tests/build/response.o $(CFLAGS) -o ./tests/build/response
	cd ./tests/build; ./response;

leaktestresponse: response; mkdir ./tests/build
	cd ./tests/build; gcc -c ../response.c
	gcc ./build/response.o ./tests/build/response.o $(CFLAGS) -o ./tests/build/response
	cd ./tests/build; valgrind ./response;

testheaders: headers; mkdir ./tests/build
	cd ./tests/build; gcc -c ../headers.c
	gcc ./build/headers.o ./tests/build/headers.o $(CFLAGS) -o ./tests/build/headers
	cd ./tests/build; ./headers;

leaktestheaders: headers; mkdir ./tests/build
	cd ./tests/build; gcc -c ../headers.c
	gcc ./build/headers.o ./tests/build/headers.o $(CFLAGS) -o ./tests/build/headers
	cd ./tests/build; valgrind ./headers;

testclient: client; mkdir ./tests/build
	cd ./tests/build; gcc -c ../client.c
	gcc ./build/client.o ./build/headers.o ./build/request.o ./build/response.o ./tests/build/http.o $(CFLAGS) -o ./tests/build/client
	cd ./tests/build; ./client;

leaktestclient: client; mkdir ./tests/build
	cd ./tests/build; gcc -c ../client.c
	gcc ./build/client.o ./build/headers.o ./build/request.o ./build/response.o ./tests/build/http.o $(CFLAGS) -o ./tests/build/client
	cd ./tests/build; valgrind ./client;

debugclient: debug; mkdir ./debugs/build
	cd ./debugs/build; gcc -g -c ../client.c
	gcc ./build/client.o ./build/headers.o ./build/request.o ./build/response.o ./debugs/build/http.o $(CFLAGS) -o ./debugs/build/client
	cd ./debugs/build; gdb ./client;




DEBUG_TEST:
	mkdir build
	cd ./src/http; gcc -c ./client/client.c -o ../../build/http.o; gcc -c ./utils/headers.c -o ../../build/headers.o; gcc -c ./utils/response.c -o ../../build/response.o; gcc -c ./utils/request.c -o ../../build/request.o
	mkdir ./tests/build
	cd ./tests/build; gcc -g -c ../check_http.c
	gcc ./build/http.o ./build/headers.o ./build/response.o ./tests/build/check_http.o $(CFLAGS) -o ./tests/build/check_http
	cd ./tests/build; gdb ./check_http



