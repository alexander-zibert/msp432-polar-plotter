# MSP432 Polar-Plotter

## Dependencies

This project depends on [YAHAL](https://git.fh-aachen.de/Terstegge/YAHAL) and [[Boost].SML](https://boost-experimental.github.io/sml/).
SML is versioned with the code.
YAHAL has to be deployed seperately and is by default expected under `vendor/YAHAL`.
However, this can be configured with the variable `YAHAL_DIR` in the `Makefile`.
The Polar-Plotter also needs the `arm-none-eabi` toolchain to compile the source code.
Additionally, the `DSLITE` tool is required, which is part of TI's Code Composer Studio.

## Compilation

The project can be compiled by running:

```
make
```

The project can be uploaded to the MSP432 by running:

```
make upload
```
