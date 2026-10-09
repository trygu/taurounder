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

τ-ARGUS is © Statistics Netherlands and is distributed under the EUPL v1.1 /
EUPL-1.2. See the top-level repository for the full notice.
