build:
	cd src;\
	make build
test:
	cd src;\
	make run
save: clean
	cd src;\
	make save
clean:
	rm *.out *.so;\
	cd src;\
	make clean