# lsp-common-lib

This is a common library for basic C/C++ language definitions used by all
other LSP-related libraries.

It provides:
* Corresponding macros for architecture and platform detection.
* Some set of additional basic types.
* Macros for architecture-dependent assembly code and compilation.
* Error codes and functions to work with them.

## Supported platforms

The build and correct unit test execution has been confirmed for following platforms:
* FreeBSD
* GNU/Linux
* OpenBSD
* Windows 32-bit
* Windows 64-bit

## Requirements

The following packages need to be installed for building:

* gcc >= 4.9
* make >= 4.0

## Building

To build the library, perform the following commands:

```bash
make config # Configure the build
make fetch # Fetch dependencies from Git repository
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

## SAST Tools

* [PVS-Studio](https://pvs-studio.com/en/pvs-studio/?utm_source=website&utm_medium=github&utm_campaign=open_source) - static analyzer for C, C++, C#, and Java code.
