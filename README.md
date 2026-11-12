# tauargus — rounder

The **rounder** module is a thin C++ dispatch layer over the **CRP**
(controlled rounding problem) engine. Its single entry point,
`RounderCtrl::DoRound(...)`, hands the rounding run to the HiGHS-backed CRP
library (`../crp`) and reports progress/results back through callback
interfaces.

It links against `tauargus::crp`. The legacy SWIG JNI wrapper
(`RounderCtrl_wrap`) and the NetBeans/MinGW build files have been removed;
bindings to the new stack are generated with pybind11
(`python/cpp/bind_rounder.cpp` in the top-level repo).

## What it provides

- `RounderCtrl` (`src/RounderCtrl.h`) — the public control object with
  `DoRound(...)`, `SetDoubleConstant`, and `SetProgressListener` /
  `SetCallback` hooks.

## Build

Part of the superbuild in the top-level repo (it links `tauargus::crp`):

```bash
cmake -S native -B native/build \
      -DHighs_DIR=$(brew --prefix)/lib/cmake/Highs
cmake --build native/build
```

Produces `libtauargus_rounder.dylib` (shared).

## License

This fork is distributed under **EUPL-1.2**; see [LICENCE](LICENCE).
Original upstream EUPL 1.1 and copyright notices are retained. The later-version
permission in Article 5 of EUPL 1.1 is explained in [NOTICE.txt](NOTICE.txt).
