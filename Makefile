.PHONY: test upload msp432 clean

upload:
	make -f Makefile-arm.mk upload

msp432:
	make -f Makefile-arm.mk

test:
	make -f Makefile-test.mk test

clean:
	@echo "Cleaning files ..."
	@make -f Makefile-arm.mk clean
	@make -f Makefile-test.mk clean
