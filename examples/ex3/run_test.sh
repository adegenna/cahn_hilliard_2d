### MAKE INITIAL DATA FILES USING PYTHON SCRIPT
python make_input_data_files_test3.py


### RUN THE ACTUAL CH SOLVER
export build_dir="../../build/"

export petsc_inputfile="./petscrc.dat"
export mpiexec_petsc="/usr/bin/mpiexec"
export petsc_solver=${build_dir}"ch2d"

echo "PETSc inputfile =" $petsc_inputfile
echo "PETSc solver =" $petsc_solver

# Run solver
$mpiexec_petsc -np 6 $petsc_solver $petsc_inputfile
