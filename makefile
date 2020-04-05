build:
	cd src;\
	make build
run:
	cd src;\
	make run
save: clean
	cd src;\
	make save
clean:
	rm *.out *.so;\
	cd src;\
	make clean