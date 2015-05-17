#include <mpi.h>
#include <stdlib.h>
#include <time.h>

main(int argc, char *argv[])
{
  int npes, myrank, yourrank;
  int a;
  int b;
  int sum = 0;
  int tag = 0;
  int flag = 0;
  int i=10000;
  double r;
  time_t start,end,diff;

  MPI_Status status;
  MPI_Request request;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &npes);

  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

  srand(i+(myrank*1000));

  a = myrank;

  while ( tag < 2 ){
    MPI_Send( &a, 1, MPI_INT, (myrank + 1) % npes, tag, MPI_COMM_WORLD );
    
    diff = (time_t)0;

    time(&start);

    if ( myrank % 2 == 0 ) 
      r = 0.0;
    else
      r = 1.0;
    
    while ( diff < 10 * r ){
      time(&end);
      diff = difftime(end,start);
    }

    MPI_Irecv( &b, 1, MPI_INT, (myrank - 1 + npes) % npes, 
	       tag, MPI_COMM_WORLD, &request );
	       
    tag++;

    while ( flag == 0 ){
      MPI_Test( &request, &flag, &status );
      sum++;
    }

    printf("I am %d and counted to %d waiting for round %d\n",
	   myrank,sum,tag);
    flag = 0;
  }

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();

}
