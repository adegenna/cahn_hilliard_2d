
export build_dir="../../build/"
export mpiexec_petsc=${build_dir}"external/petsc/linux-gnu-c-debug/bin/mpiexec"

### RUN THE ACTUAL CH SOLVER

export petsc_inputfile="./petscrc.dat"
export petsc_solver=${build_dir}"ch2d"

echo "PETSc inputfile =" $petsc_inputfile
echo "PETSc solver =" $petsc_solver

# Run solver
$mpiexec_petsc -np 6 $petsc_solver $petsc_inputfile
