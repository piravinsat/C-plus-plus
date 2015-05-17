#include <mpi.h>
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]){

  char names[3][50]; 
  char newname[50]; 
  char newname2[50]; 
  
  MPI::Status status;

  MPI::Init(argc,argv);

  int rank = MPI::COMM_WORLD.Get_rank();
  int size = MPI::COMM_WORLD.Get_size();

  strcpy(names[0],"Huey");
  strcpy(names[1],"Duey");
  strcpy(names[2],"Luey");
  
  char *myname = names[rank];

  /* 
   * We now make use of the Sendrecv library
	   */
   
  MPI::COMM_WORLD.Sendrecv( (void *)myname, 50, MPI_CHAR, (rank + 1) % size, 0, 
                (void *)newname,50, MPI_CHAR, (rank - 1 + size) % size, 0, 
                status);

  cout << "I am " << myname <<" You are " << newname << endl ;

  MPI::COMM_WORLD.Barrier();    

  MPI::COMM_WORLD.Sendrecv( (void *)newname, 50, MPI_CHAR, (rank + 1) % size, 0, 
                (void *)newname2, 50, MPI_CHAR, (rank - 1 + size) % size, 0, 
                status);

  cout << "I am " << myname <<" You are " << newname2 << endl ;

  MPI::Finalize();
  return 0;
}
