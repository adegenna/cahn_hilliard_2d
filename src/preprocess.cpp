
static char help[] = "Convert endl-delimited ascii file to petsc binary file \n";

#include <petscdm.h>
#include <petscdmda.h>
#include <petscts.h>
#include <petscvec.h>
#include <petscviewer.h>
#include <petscsys.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "utils_ch.h"

int main(int argc,char **argv) {

  // Interface: ./postprocess <petsc_config_file.dat> <parallel_binary_file.bin>
  
  Vec            U;                    /* solution, residual vectors */
  PetscErrorCode ierr;
  DM             da;
  SNES           snes;

  ierr = PetscInitialize( NULL , NULL , argv[1] , help );if (ierr) return ierr;
  
  const std::string solnfile = argv[2];

  AppCtx         user = parse_petsc_options();

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     Create distributed array (DMDA) to manage parallel grid and vectors
  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */  
  DMDACreate2d(PETSC_COMM_WORLD, 
               DM_BOUNDARY_NONE, DM_BOUNDARY_NONE,    // type of boundary nodes
               DMDA_STENCIL_BOX,                // type of stencil
               11,11,                           // global dimns of array
               PETSC_DECIDE,PETSC_DECIDE,       // #procs in each dimn
               1,                               // DOF per node
               2,                               // Stencil width
               NULL,NULL,&da);
  DMSetFromOptions(da);
  DMSetUp(da);
  user.da_c = da;

  /*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     Convert parallel binary --> serial ascii
   - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  DMCreateGlobalVector(da,&U);
  MPI_Comm    comm = PETSC_COMM_WORLD;

  // Get Vec --> C array
  PetscScalar **uarray;
  PetscInt Mx,My;
  DMDAGetInfo(da,PETSC_IGNORE,&Mx,&My,PETSC_IGNORE,PETSC_IGNORE,PETSC_IGNORE,PETSC_IGNORE,PETSC_IGNORE,PETSC_IGNORE,PETSC_IGNORE,PETSC_IGNORE,PETSC_IGNORE,PETSC_IGNORE);
  DMDAVecGetArray(da,U,&uarray);

  // Read original ascii file in serial using std::ifstream
  std::ifstream Uin;
  Uin.open( solnfile );
  for (int j=0; j<My; j++) {
    for (int i=0; i<Mx; i++) {
      Uin >> uarray[j][i];
    }
  }
  Uin.close();
  DMDAVecRestoreArray(da,U,&uarray);
  
  // Rewrite in serial to binary
  PetscViewer viewer_output;
  std::size_t found = solnfile.find_last_of("/\\.");
  const std::string fileoutname = solnfile.substr( 0 , found ) + ".bin";
  PetscViewerCreate( comm , &viewer_output );
  PetscViewerSetType( viewer_output , PETSCVIEWERBINARY );
  PetscViewerFileSetMode( viewer_output , FILE_MODE_WRITE );
  PetscViewerBinaryOpen( comm , fileoutname.c_str() , FILE_MODE_WRITE , &viewer_output );
  VecView( U , viewer_output );
  PetscViewerDestroy( &viewer_output );

  VecDestroy(&U);
  DMDestroy(&da);

  PetscFinalize();
  return ierr;
}
