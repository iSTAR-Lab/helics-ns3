# helics-ns3

This version of the helics-ns3 module targets **ns-3.48** (CMake build system) and **HELICS 3** (tested with HELICS 3.7).
It uses the HELICS C++ API, which requires HELICS to be built with the C++ shared library (see Prerequisites).

[![Build Status](https://github.com/GMLC-TDC/helics-ns3/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/GMLC-TDC/helics-ns3/actions/workflows/ci.yml)

[helics-ns3](https://github.com/GMLC-TDC/helics-ns3) is an [ns-3](https://www.nsnam.org/) module for coupling network simulations with other simulators using [HELICS](https://www.helics.org/).

### Older versions of HELICS and/or ns-3

For the last supported releases with older versions of HELICS and ns-3, look for the tags starting with `HELICS-v`and match the HELICS version with the build system (waf or cmake). Or look at the [Releases page](https://github.com/GMLC-TDC/helics-ns3/releases) and find the most recent release for your version of HELICS and ns-3 build system.

For HELICS 3 and ns-3 using waf (ns-3.35 or older), `HELICS-v3.x-waf` is the last tagged release.

For HELICS 2 and ns-3 using CMake, `HELICS-v2.x-cmake` is the last tagged release.

For HELICS 2 and ns-3 using waf, `HELICS-v2.x-waf` is the last tagged release.

For HELICS 1 (upgrade **highly** recommended), ns-3 using CMake is not supported; the final tag is `HELICS-v1.3.x`.

## Prerequisites

Install version 3+ of [HELICS](https://github.com/GMLC-TDC/HELICS) built with the C++ shared library (`libhelicscpp`),
which is not part of a default HELICS build or most binary packages. Build HELICS from source with
`-DHELICS_BUILD_CXX_SHARED_LIB=ON`; it must be built with the same compiler (and C++ standard library) as ns-3:

```bash
git clone -b v3.7.0 https://github.com/GMLC-TDC/HELICS.git
cmake -S HELICS -B HELICS/build -DCMAKE_BUILD_TYPE=Release -DHELICS_BUILD_CXX_SHARED_LIB=ON \
      -DCMAKE_INSTALL_PREFIX=<path to install folder you have access to>
cmake --build HELICS/build -j
cmake --install HELICS/build
```

Get a copy of ns-3.48:

```bash
git clone -b ns-3.48 https://gitlab.com/nsnam/ns-3-dev.git
```

## Installation

Clone a copy of this repository into a folder named `helics` in the ns-3 `contrib` directory.

```bash
cd ns-3-dev/
git clone https://github.com/GMLC-TDC/helics-ns3 contrib/helics
```

Configure and build ns-3. HELICS is found automatically if it is installed in a standard location; otherwise point
CMake at the HELICS install prefix with `NS3_WITH_HELICS` (or `HELICS_DIR`/`CMAKE_PREFIX_PATH`). Paths should be absolute.

```bash
./ns3 configure --enable-examples --enable-tests -- -DNS3_WITH_HELICS=/usr/local
./ns3 build
```

The configure output reports `contrib/helics: using HELICS <version> from <path>` when HELICS is found. If HELICS, or
its C++ shared library, is not found, the module is skipped and listed under "Modules that cannot be built".

If the HELICS library is not in a default library search path, add its `lib` (or `lib64`) directory to
`LD_LIBRARY_PATH` (or `DYLD_LIBRARY_PATH` on macOS) when running simulations.

Run the module test suite with:

```bash
./test.py -s helics
```

See [examples/README.md](examples/README.md) for how to run the co-simulation examples.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.  Please see [CONTRIBUTING](./CONTRIBUTING.md) for some additional notes on licensing of new components and modifications.  

## Release
The helics-ns3 repository is distributed under the terms of the [GPL-v2](LICENSE) license as required by NS3 since this library derives some code from that code base.

Individual source files that do not require derivation from NS3 are licensed as BSD style.  Any contributions to non-NS3 derived files ideally should be made with BSD markings in the source file.
At some point in the future if legally allowed or the NS-3 derived components can be removed the repository will be relicensed.  

SPDX-License-Identifier: GPL-v2
