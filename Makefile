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
	cd ./tests; gcc -c check_http.c
	gcc ./build/http.o ./tests/check_http.o -lcurl -lcheck -lsubunit -lpthread -lm -lrt -o ./tests/check_http
	./check_http

CLEAN_TEST_CLIENT:
	rm -rf ./build
	cd ./tests; rm -rf ./check_http.o; rm -rf ./check_http