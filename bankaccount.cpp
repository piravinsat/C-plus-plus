#include <mpi.h>
#include <iostream>
#include <string.h>

using namespace std;


void runit( int amount, int num_interactions,
            int balance );
void run_deposit( int amount,int num_interactions);
void run_withdraw( int amount,int num_interactions );
void deposit( int amount );
void withdraw( int amount );
void run_balance(int balance);

main(int argc, char *argv[])
{
  int amount = 100;
  int num_interactions = 10;
  int balance=0;
  
  MPI::Init(argc, argv);
  runit(amount, num_interactions, balance);
  MPI::Finalize();
  exit(1);
} 

void runit( int amount, int num_interactions, 
            int balance){

  int myrank = MPI::COMM_WORLD.Get_rank();
  int npes = MPI::COMM_WORLD.Get_size();

  if ( npes != 3 ){
    cout << "Wrong number of processors " << npes << endl ;
     MPI::Finalize();
     exit(-myrank);}

  if ( myrank == 0 ) run_balance(balance);
  else
    if ( myrank == 1 ) 
      run_withdraw( amount, num_interactions );
    else 
      run_deposit( amount, num_interactions );
}


void run_deposit( int amount,int num_interactions){
  int i;

  for ( i = 0 ; i < num_interactions ; i++){
    deposit(amount);}
}

void deposit( int amount ){
  int i,balance;
  MPI::Status status;
  int lock=1;

  MPI::COMM_WORLD.Send(&lock,1,MPI_INT,0,1);
  MPI::COMM_WORLD.Recv(&balance,1,MPI_INT,0,2,status);

  balance += amount;

  MPI::COMM_WORLD.Send(&balance,1,MPI_INT,0,3);
}

void run_withdraw( int amount,int num_interactions){
  int i,j;
  for ( i = 0 ; i < num_interactions ; i++){
    withdraw(amount);}}

void withdraw( int amount ){
  int i,balance;
  MPI::Status status;
  int lock=1;

  MPI::COMM_WORLD.Send(&lock,1,MPI_INT,0,1);
  MPI::COMM_WORLD.Recv(&balance,1,MPI_INT,0,2,status);

  balance -= amount;

  MPI::COMM_WORLD.Send(&balance,1,MPI_INT,0,3);
}

void run_balance(int balance){
  int wlock,dlock;
  int wread, dread;
  MPI::Request rwithdraw,rdeposit;
  MPI::Status status;
  wread = dread = 1;
  int flag = 0;

  while ( 1 > 0 ){
    flag = 0;

    if ( wread ){
      wread = 0;
      rwithdraw = MPI::COMM_WORLD.Irecv(&wlock,1,MPI_INT,1,1); 
    }

    if ( dread ){
      dread = 0; 
      rdeposit = MPI::COMM_WORLD.Irecv(&dlock,1,MPI_INT,2,1); 
    }

    flag = rwithdraw.Test(status);
    
    if ( flag > 0 ){

      MPI::COMM_WORLD.Send(&balance,1,MPI_INT,1,2);

      MPI::COMM_WORLD.Recv(&balance,1,MPI_INT,1,3,status);

      cout << "Balance= " << balance << endl ;   

      wread = 1; 
    }
    else{  

      flag = rdeposit.Test(status);

      if ( flag > 0 ){

        MPI::COMM_WORLD.Send(&balance,1,MPI_INT,2,2);

        MPI::COMM_WORLD.Recv(&balance,1,MPI_INT,2,3,status);

		cout << "Balance= " << balance << endl ;   

        dread = 1;
      }
    }
  }
}
