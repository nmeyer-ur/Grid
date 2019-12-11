# Grid with SVE support
**Data parallel C++ mathematical object library.**

### Description
This library provides data parallel C++ container classes with
internal memory layout that is transformed to map efficiently to
SIMD architectures. This branch enables support for ARM SVE
architectures such as the Fujitsu A64FX CPU, which features an 512-bit
vector registers. The implementation of Grid uses SVE ACLE intrinsics.

### References

* _SVE-enabling Lattice QCD Codes_, IEEE Cluster Conference 2018 (https://arxiv.org/abs/1901.07294)
* _Lattice QCD on Upcoming ARM Architectures_, Lattice Conference 2018 (Poster)
(https://indico.fnal.gov/event/15949/session/4/contribution/225/material/poster/0.pdf)
* _Lattice QCD on Upcoming ARM Architectures_, Lattice Conference 2018 (Paper) tbd

### SVE compiler support

* armclang 18.4 and 19.1
* Allinea gcc 8.2.0 (auto-vectorization for fixed-size SVE, no intrinsics support yet)
* gcc 8.2.0 (not tested, but expected to work too)

### SVE emulators and simulators

* armie 18.4
* qemu
* gem5 atomic CPU model (ARM)
* gem5 Out-of-Order (O3) CPU model (RIKEN, Japan)

### How to clone

Run
``` bash
git clone https://github.com/nmeyer-ur/Grid.git
cd Grid
./bootstrap.sh
git checkout feature/arm-sve
```

### How to build using intrinsics (armclang only)

Configuration for 512-bit SVE without MPI and without OpenMP
support. To enable OpenMP supply `--enable-openmp` instead of
`--disable-openmp`.

Dynamic linking
```
configure --enable-gen-simd-width=64 --enable-simd=GEN --enable-precision=double \
    --disable-openmp --enable-comms=none CXX=armclang++ \
    CXXFLAGS="-O3 -march=armv8-a+sve -fno-unroll-loops -mllvm \
    -vectorizer-min-trip-count=2 -DGENSVE -D<implementation>"
make
```

Static linking (required for gem5)
```
configure --enable-gen-simd-width=64 --enable-simd=GEN --enable-precision=double \
    --disable-openmp --enable-comms=none CXX=armclang++ \
    CXXFLAGS="-O3 -march=armv8-a+sve -fno-unroll-loops -mllvm \
    -vectorizer-min-trip-count=2 -DGENSVE -D<implementation>" \
    LDFLAGS=-static GRID_LDFLAGS=-static MPI_CXXLDFLAGS=-static
make
```

There are several implementations available at present. They are
enabled by define statements (`-DGENSVE -D<implementation>`)

| `<implementation>`    | Description                            |
| -------------- | -------------------------------------- |
| `SVE_CPLX_LD1` | ld1/st1 load/store scheme, FCMLA instructions for processing complex numbers, 100% SIMD efficiency, not supported by gem5           |
| `SVE_REAL_LD1` | ld1/st1 load/store scheme, real arithmetics for processing complex numbers, 100% SIMD efficiency           |
| `SVE_REAL_LD2` | ld2/st2 load/store scheme, real arithmetics for processing complex numbers, 50% SIMD efficiency for processing complex numbers, 100% SIMD efficiency otherwise          |
| `SVE_CPLX_REF` | load/store scheme using pointers, FCMLA instructions for processing complex numbers, 100% SIMD efficiency, not supported by gem5, has aliasing issues!           |
| `SVE_REAL_REF` | load/store scheme using pointers, real arithmetics for processing complex numbers, 100% SIMD efficiency, has aliasing issues!        |

### Verification

All builds are verified with armie 18.4 without OpenMP.
The `*_REF` implementations fail due to aliasing issues in the
permutation group.

### How to run Grid tests and benchmarks

The following runtime arguments are useful for running Grid binaries in
simulation environments. The arguments avoid excessive runtimes and memory
consumption.
* `--shm N`, sets the size of communication buffers to N bytes,
    e.g. `--shm 1`
* `--threads N`, enables exactly N threads
    (requires build with OpenMP enabled)
* `--grid N.N.N.N`, defines the size of the 4d lattice, e.g.
    `--grid 4.4.4.4` defines an 4^4 lattice  

### How to run binaries in armie 18.4

armie requires the SVE vector length of the simulation environment to be
defines as command-line argument. Example for testing the intrinsics
implementation:
```
armie -msve-vector-bits=512 -- ./tests/Test_simd
```
The binaries check for the SVE vector length at startup and exits
with `EXIT_FAILURE` upon mismatch.

Match
```
Grid with SVE support.
N. Meyer et al., University of Regensburg, Germany. 2019.
Build SVE_REAL_LD1: 512-bit SVE, ld1/st1 real arithmetics.
Want vector length 512 bits, got 512 bits. ok.
```
Mismatch
```
Grid with SVE support.
N. Meyer et al., University of Regensburg, Germany. 2019.
Build SVE_REAL_LD1: 512-bit SVE, ld1/st1 real arithmetics.
Want vector length 512 bits, got 256 bits. prctl() failed. got -8.
```

### gem5 support

Only `SVE_REAL_LD1` and `SVE_REAL_LD2` implementations are supported.
