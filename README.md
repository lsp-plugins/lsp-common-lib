# lsp-common-lib

This is a common library for basic C/C++ language definitions used by all
other LSP-related libraries.

It provides:
* Corresponding macros for architecture and platform detection.
* Some set of additional basic types.
* Macros for architecture-dependent assembly code and compilation.
* Error codes and functions to work with them.

Requirements
======

The following packages need to be installed for building:

* gcc >= 4.9
* make >= 4.0

Building
======

To build the library, perform the following commands:

```bash
make config
make
sudo make install
```

To get more build options, run:

```bash
make help
```

To uninstall library, simply issue:

```bash
make uninstall
```

To clean all binary files, run:

```bash
make clean
```

To clean the whole project tree including configuration files, run:

```bash
make prune
```
