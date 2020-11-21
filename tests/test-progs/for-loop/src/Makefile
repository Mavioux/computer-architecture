all: for_loop64-static for_loop32-static

for_loop64-static: for_loop.c dockcross-arm64
	./dockcross-arm64 bash -c '$$CC for_loop.c -o for_loop64-static -static'

for_loop32-static: for_loop.c dockcross-armv7
	./dockcross-armv7 bash -c '$$CC for_loop.c -o for_loop2-static -static'

dockcross-arm64:
	docker run --rm dockcross/linux-arm64 > ./dockcross-arm64
	chmod +x ./dockcross-arm64

dockcross-armv7:
	docker run --rm dockcross/linux-armv7 > ./dockcross-armv7
	chmod +x ./dockcross-armv7

clean:
	rm -f dockcross* for_loop64-static for_loop32-static
