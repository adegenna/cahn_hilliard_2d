
export build_dir="../../build/"
export mpiexec_petsc=${build_dir}"external/petsc/linux-gnu-c-debug/bin/mpiexec"

### RUN THE ACTUAL CH SOLVER

export petsc_inputfile="./petscrc.dat"
export petsc_solver=${build_dir}"mmstest_ch2d"

echo "PETSc inputfile =" $petsc_inputfile
echo "PETSc solver =" $petsc_solver

# Run solver

$mpiexec_petsc -np 4 $petsc_solver $petsc_inputfile

#$mpiexec_petsc -np 4 valgrind --tool=memcheck -q --num-callers=20 --log-file=valgrind.log.%p $petsc_solver $petsc_inputfile
#valgrind --tool=memcheck -q --num-callers=20 --log-file=valgrind.log.%p $petsc_solver $petsc_inputfile
#$petsc_solver $petsc_inputfile
