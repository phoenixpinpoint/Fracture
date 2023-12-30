###########################################################
# General Builds
#
# Below are the builds for the library
###########################################################

#Note -Ideps covers all dep except cwalk which expect that specific folder to be included.
all:
	npx tailwindcss -i ./assets/stylesheets/app.css -o ./assets/stylesheets/app-ts.css
	emcc -Ideps -Ideps/cwalk -Isrc -s EXPORTED_RUNTIME_METHODS=ccall,cwrap -s LINKABLE=1 -s EXPORT_ALL=1 -s ASYNCIFY -s DEFAULT_LIBRARY_FUNCS_TO_INCLUDE='$$allocate','$$intArrayFromString' --embed-file assets ./app.c -o ./bin/app.js

clean:
	rm -rf ./app
	rm -rf ./app.wasm
