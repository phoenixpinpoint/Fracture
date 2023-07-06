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
server: 
	mkdir build
	cd ./src; gcc -D SERVER -c ./webc.c -o ../build/webc.o;

headers:
	mkdir build
	cd ./src/http; gcc -D SERVER -c ./headers.c -o ../../build/headers.o;

request: 
	mkdir build
	cd ./src/http; gcc -D SERVER -c ./headers.c -o ../../build/headers.o; gcc -c ./request.c -o ../../build/request.o

response:
	mkdir build
	cd ./src/http; gcc -D SERVER -c ./headers.c -o ../../build/headers.o; gcc -c ./response.c -o ../../build/response.o;

httpclient:
	mkdir build
	cd ./src/http; gcc -D SERVER -c ./client.c -o ../../build/client.o; gcc -c ./headers.c -o ../../build/headers.o; gcc -c ./response.c -o ../../build/response.o; gcc -c ./request.c -o ../../build/request.o

fs:
	mkdir build
	cd ./src/utils; gcc -D SERVER -c ./fs.c -o ../../build/fs.o;

regex: 
	mkdir build
	cd ./src/utils; gcc -D SERVER -c ./regex.c -o ../../build/regex.o;

debug:
	mkdir build
	cd ./src/http; gcc -g -D SERVER -c ./client.c -o ../../build/http.o; gcc -g -c ./headers.c -o ../../build/headers.o; gcc -g -c ./response.c -o ../../build/response.o; gcc -g -c ./request.c -o ../../build/request.o

client:
	emcc -D CLIENT -s EXPORTED_RUNTIME_METHODS=ccall,cwrap -s LINKABLE=1 -s EXPORT_ALL=1 --embed-file assets ./src/webc.c ./app.c -o app

clean: 
	rm -rf ./build
	rm -rf ./tests/build
	rm -rf ./debugs/build
	rm -rf ./app
	rm -rf ./app.wasm


########################################################### 
# Tests
# 
# Below are the builds for Unit testing.
###########################################################
testserver: server; mkdir ./tests/build
	cd ./tests/build; gcc -c ../request.c
	gcc ./build/webc.o ./tests/build/request.o $(CFLAGS) -o ./tests/build/request
	cd ./tests/build; gcc -c ../headers.c
	gcc ./build/webc.o ./tests/build/headers.o $(CFLAGS) -o ./tests/build/headers
	cd ./tests/build; gcc -D SERVER -c ../client.c
	gcc ./build/webc.o ./tests/build/client.o $(CFLAGS) -o ./tests/build/client
	cd ./tests/build; ./request; ./headers; ./client;

leaktestserver: server; mkdir ./tests/build
	cd ./tests/build; gcc -c ../request.c
	gcc ./build/request.o ./tests/build/request.o $(CFLAGS) -o ./tests/build/request
	cd ./tests/build; gcc -c ../headers.c
	gcc ./build/headers.o ./tests/build/headers.o $(CFLAGS) -o ./tests/build/headers
	cd ./tests/build; gcc -D SERVER -c ../client.c
	gcc ./build/client.o ./build/headers.o ./build/request.o ./build/response.o ./tests/build/client.o $(CFLAGS) -o ./tests/build/client
	cd ./tests/build; valgrind ./request; valgrind ./headers; valgrind ./client;

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

testhttpclient: httpclient; mkdir ./tests/build
	cd ./tests/build; gcc -D SERVER -c ../client.c
	gcc ./build/client.o ./build/headers.o ./build/request.o ./build/response.o ./tests/build/client.o $(CFLAGS) -o ./tests/build/client
	cd ./tests/build; ./client;

leaktesthttpclient: httpclient; mkdir ./tests/build
	cd ./tests/build; gcc -D SERVER -c ../client.c
	gcc ./build/client.o ./build/headers.o ./build/request.o ./build/response.o ./tests/build/client.o $(CFLAGS) -o ./tests/build/client
	cd ./tests/build; valgrind --leak-check=full --suppressions=../../valgrind-ignore.txt ./client;

testfs: fs; mkdir ./tests/build
	cd ./tests/build; gcc -c ../fs.c
	gcc ./build/fs.o ./tests/build/fs.o $(CFLAGS) -o ./tests/build/fs
	cd ./tests/build; ./fs;

testregex: regex; mkdir ./tests/build
	cd ./tests/build; gcc -c ../regex.c
	gcc ./build/regex.o ./tests/build/regex.o $(CFLAGS) -o ./tests/build/regex
	cd ./tests/build; ./regex;

# debugclient: debug; mkdir ./debugs/build
# 	cd ./debugs/build; gcc -D SERVER -g -c ../client.c
# 	gcc ./build/client.o ./build/headers.o ./build/request.o ./build/response.o ./debugs/build/client.o $(CFLAGS) -o ./debugs/build/client
# 	cd ./debugs/build; gdb ./client;

# DEBUG_TEST:
# 	mkdir build
# 	cd ./src/http; gcc -c ./client.c -o ../../build/http.o; gcc -c ./headers.c -o ../../build/headers.o; gcc -c ./response.c -o ../../build/response.o; gcc -c ./request.c -o ../../build/request.o
# 	mkdir ./tests/build
# 	cd ./tests/build; gcc -g -c ../check_http.c
# 	gcc ./build/http.o ./build/headers.o ./build/response.o ./tests/build/check_http.o $(CFLAGS) -o ./tests/build/check_http
# 	cd ./tests/build; gdb ./check_http
