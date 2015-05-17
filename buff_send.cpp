#include <mpi.h>
#include <iostream>
#include <string.h>

using namespace std;



main(int argc, char *argv[])
{

  int yourrank;
  
  MPI::Status status;

  MPI::Init(argc, argv);
  int npes = MPI::COMM_WORLD.Get_size();

  int myrank = MPI::COMM_WORLD.Get_rank();

  MPI::COMM_WORLD.Send(  &myrank, 1, MPI_INT, (myrank + 1) % npes, 0);
  MPI::COMM_WORLD.Recv( &yourrank, 1, MPI::INT,  (myrank - 1 + npes) % npes, 0, status);

  cout << "I am " << myrank << " you are " << yourrank << " there are " << npes << " PE's " << endl;

  MPI::Finalize();

}
