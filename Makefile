###########################################################
# General Builds
#
# Below are the builds for the library
###########################################################
all:
	npx tailwindcss -i ./assets/stylesheets/app.css -o ./assets/stylesheets/app-ts.css
	emcc -D CLIENT -s EXPORTED_RUNTIME_METHODS=ccall,cwrap -s LINKABLE=1 -s EXPORT_ALL=1 -s ASYNCIFY -s DEFAULT_LIBRARY_FUNCS_TO_INCLUDE='$$allocate','$$intArrayFromString' --embed-file assets ./src/webc.c ./app.c -o app

clean:
	rm -rf ./app
	rm -rf ./app.wasm
