all:
	@make -sC build
.PHONY: all

clean:
	@make clean -sC build
.PHONY: clean

run: $(all)
	@./build/demo
.PHONY: run
