# Introduction

## Concentration dynamics

The main field that evolves is relative concentration of the A phase at the mesoscale of a block copolymer, which occurs through a modified 2D Cahn Hilliard equation:

<img src="https://github.com/adegenna/cahn_hilliard_2d/blob/master/figs/cheqn.gif">

Domain: 2D rectangular

Boundary Conditions: Neumann, Dirichlet

## Polymer properties

The coefficients of the CH equation are implemented as a function of polymer properties (see, e.g., `Choksi & Ren, 2003`). Some of these values have default values based on ``reasonable'' experimental ranges; others (such as macroscopic mass concentration, `m`) are operating conditions that should be user-specified.

<img src="https://github.com/adegenna/cahn_hilliard_2d/blob/master/figs/eps2_thermal.gif">

<img src="https://github.com/adegenna/cahn_hilliard_2d/blob/master/figs/sigma_thermal.gif">

## Thermal dependence

Temperature is usually specified in experiment as a control, and Flory-Huggins is inversely proportional to it. Thus, in this code, the user specifies temperature as a field over the entire spatial domain, and Flory-Huggins is calculated from that:

<img src="https://github.com/adegenna/cahn_hilliard_2d/blob/master/figs/chi_thermal.gif">

## Thermal dynamics

If desired, temperature can be evolved as a spatial field through a thermal diffusion equation that is one-way coupled to the Cahn-Hilliard dynamics:

<img src="https://github.com/adegenna/cahn_hilliard_2d/blob/master/figs/thermal_eqn.gif">

Boundary conditions: Dirichlet , Neumann

Alternatively, the user may desire to simply investigate the effects of a time-dependent temperature profile (without any thermal dynamics). In this case, it is possible to simply update the thermal field at discrete incremements of time. See `examples/ex4/` for an example case that does this using a time-dependent thermal field that is parameterized as a Gaussian distribution. 

## Numerical method

Spatial discretization is uniform finite difference. Temporal evolution may be either explicit or implicit. Default options for explicit/implicit timestepping are handled through the `-temporal_scheme` flag in the user-input file (see the examples for demos). The user may alternatively specify timestepping options (e.g., linear solver tolerances for implicit) directly through PETSc input flags. Consult the PETSc documentation if you wish to do that. 

# Building

Building is done through `cmake`, using the included `CMakeLists.txt`: 

```shell
cd [/PATH/TO]/cahn_hilliard_2d/cpp
mkdir build/
cd build/
cmake ../
make
```

This should download and locally install several important dependencies. The two most important are PETSc and openmpi. Regarding the latter, I have set things up so that PETSc downloads, installs, and compiles against a local copy of openmpi, to prevent problems that might occur if conflicting MPI libraries are used at compile/runtime.

# Examples

Example cases are provided in `examples/`. I recommend starting there and modifying these as needed.

# Pre/postprocessing

The main PETSc solver interfaces by reading/writing binary data files. Obviously most users would like to read/write data with e.g. Python. To assist with this, two executables are built at compile time that convert ascii --> binary and vice versa. See the examples for illustrations of how to use these with Python.