#include <mpi.h>
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]){
  
  char name[50]; 
  char *allnames; 

  MPI::Status status;
  MPI::Init(argc,argv);

  int rank = MPI::COMM_WORLD.Get_rank();
  int size = MPI::COMM_WORLD.Get_size();

  /*
   *  Set up array for scattering 
   */

  allnames = (char *) malloc(sizeof(char) * 50 * size );
  strcpy(name,"Spartacus");

  if ( rank == 0 ){
    strcpy(name, "Spartacus (Kirk Douglas)");
    for ( int i = 0 ; i < size; i++ )
      strcpy(&(allnames[i*50]),"Spartacus");    
  }
  else
    strcpy(name,"Antoninus (Tony Curtis)");

  cout << rank << " is really " << name << endl ;

  MPI::COMM_WORLD.Scatter((void *)allnames, 50,
	      MPI_CHAR,
              (void *)name, 50, 
              MPI_CHAR,0);

  cout << rank << " I am " << name << endl ;

  MPI::Finalize();
  return 0;
}
