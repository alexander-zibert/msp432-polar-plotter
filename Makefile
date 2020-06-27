.PHONY: test upload msp432 clean

upload:
	make -f Makefile-arm upload

msp432:
	make -f Makefile-arm

test:
	make -f Makefile-test test

clean:
	@echo "Cleaning files ..."
	@make -f Makefile-arm clean
	@make -f Makefile-test clean
