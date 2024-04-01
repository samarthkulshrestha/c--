main: src/cg.c src/expr.c src/gen.c src/interp.c src/main.c src/scan.c src/tree.c
	cc -o ./target/main -g src/cg.c src/expr.c src/gen.c src/interp.c src/main.c src/scan.c src/tree.c

clean:
	rm -f target/main *.o

test: main
	./target/main tmp/inp01
	cc -o out out.s
	./out
	./target/main tmp/inp02
	cc -o out out.s
	./out
