#ifndef __INITIAL_CONDITIONS_H__
#define __INITIAL_CONDITIONS_H__

#include "utils_ch.h"

PetscErrorCode FormInitialSolution( Vec U , void *ptr );

PetscErrorCode FormInitialSolution_mmstest(Vec U , void *ptr);


#endif
