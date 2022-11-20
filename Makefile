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
	gcc ./build/http.o ./tests/build/check_http.o -lcurl -lcheck -lsubunit -lpthread -lm -lrt -o ./tests/build/check_http
	cd ./tests/build; ./check_http

CLEAN_TEST_CLIENT:
	rm -rf ./build
	rm -rf ./tests/build