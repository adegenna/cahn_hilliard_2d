import numpy as np
import sys
import matplotlib.pyplot as plt
from matplotlib import animation

def read_mpi_soln_file( statefile , n ):
    
    c = np.zeros( n )
    count = 0
    with open( statefile ) as f:
        for line in f:
            try:
                c[count] = line
                count += 1
            except:
                pass
    
    return c


def main( ascii_file ):
    
    nx = 128
    ny = 128

    x     = np.arange(nx)
    y     = np.arange(ny)
    xx,yy = np.meshgrid(x,y)
    xx = xx.T; yy = yy.T
    
    c = read_mpi_soln_file( ascii_file , nx*ny )
    c = c.reshape( [nx,ny] , order='C' )
    
    plt.contourf( xx , yy , c , 30 , vmin=-1 , vmax=1 )
    plt.xticks([])
    plt.yticks([])
    plt.gca().set_aspect('equal')
    plt.show()
    

if __name__ == '__main__':

    main( sys.argv[1] )
