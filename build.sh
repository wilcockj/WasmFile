emcc -o demo.html \
	demo.c --shell-file html_template/shell_minimal.html \
	-s NO_EXIT_RUNTIME=1 \
	-s "EXPORTED_RUNTIME_METHODS=['ccall','cwrap']"
