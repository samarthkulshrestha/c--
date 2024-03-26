main: src/expr.c src/interp.c src/main.c src/scan.c src/tree.c
	cc -o ./target/main -g src/expr.c src/interp.c src/main.c src/scan.c src/tree.c

clean:
	rm -f target/main *.o

test: main
	-(./target/main tmp/inp01; \
		./target/main tmp/inp02; \
		./target/main tmp/inp03; \
		./target/main tmp/inp04; \
		./target/main tmp/inp05)
