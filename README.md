# MSP432 Polar-Plotter

## Dependencies

This project depends on [YAHAL](https://git.fh-aachen.de/Terstegge/YAHAL) and [[Boost].SML](https://boost-experimental.github.io/sml/).
SML is versioned with the code.
YAHAL has to be deployed seperately and is by default expected under `vendor/YAHAL`.
However, this can be configured with the variable `YAHAL_DIR` in the `Makefile`.
The Polar-Plotter also needs the `arm-none-eabi` toolchain to compile the source code.
Additionally, the DSLITE tool is required to upload the binary to the MSP432.
DSLITE is part of [TI's Code Composer Studio](https://software-dl.ti.com/ccs/esd/documents/ccs_downloads.html) (CCS).
After installing CCS, you can change the DSLITE variable in the `Makefile` to the installation location.

> NOTE: You do not need to use CCS as IDE, only the DSLITE tool is needed.

## Compilation

The project can be compiled by running:

```
make msp432
```

The project can be uploaded to the MSP432 by running:

```
make upload
```

The unit tests can be executed with:

```
make test
```

The build and test files can be cleaned up by running:

```
make clean
```
