CC=clang
OUT=public/atoms-module.wasm

all: clean build

clean:
	rm -f $(OUT)

build:
	$(CC) \
		-nostdlib \
		--target=wasm32 \
		-std=c99 \
		-Wall \
		-g0 \
		-fno-discard-value-names \
		-O3 -flto \
		-Wl,--export-dynamic \
		-Wl,--no-entry \
		-Wl,--lto-O3 \
		-Wl,--initial-memory=$$(( 8 * 65536 )) \
		-o $(OUT) \
		src/main.c

serve: clean build
	cd public
	python3 -m http.server
