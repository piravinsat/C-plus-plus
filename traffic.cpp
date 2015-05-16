#include "IDM.h"
#include <mpi.h>
#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

int main(int argc, char *argv[]) {

  MPI::Init(argc, argv);
  int myrank  = MPI::COMM_WORLD.Get_rank();
  int npes = MPI::COMM_WORLD.Get_size();

  int currentSec = 0, cars = npes;
  float v[cars]; //New Speed
  float u[cars]; //Old Speed
  float a[cars]; //Acceleration
  float s[cars]; //Total distance
  float d = 0; //Separation
  int trackLength = 0; //Track length
  int carLength = 5; //Car length in metres
  int totalSec = 100; //Loop for 100 iterations

  //Ask user for initial speed and separation
  float initSpeed = 0;

 if (myrank == 0) {
  cout << "Enter the initial speed for the cars ";
  cin >> initSpeed;

  cout << "Enter the initial separation between cars ";
  cin >> d;

} 

  MPI::COMM_WORLD.Bcast(&initSpeed, 1,
    MPI_FLOAT, 0);
  MPI::COMM_WORLD.Bcast(&d, 1,
    MPI_FLOAT, 0);

  for (int i = 0; i < cars; i++){
    u[i] = initSpeed;
    }

  //Initialise first car s0 to be 0 then each car si
  for (int j=1; j < cars; j++){
    s[j] = (carLength + d)*j;
  }
  
  //Calculate track length
  trackLength = s[cars-1] + carLength + d;
  
  //Loop each second
  while (currentSec < totalSec) {
    
    v[myrank] = u[myrank] + 1.0*a[myrank];
    s[myrank] = s[myrank] + u[myrank]*1.0 + (0.5*a[myrank]*pow(1.0, 2));
    
    if (s[myrank] > trackLength) {
      s[myrank] = s[myrank] - trackLength;
    }
    
    //Send the updated distance travelled and speed to PE i-1
    MPI::COMM_WORLD.Send(&s[myrank], 1, MPI_FLOAT, (myrank - 1 + npes) % npes, 0);
    MPI::COMM_WORLD.Send(&v[myrank], 1, MPI_FLOAT, (myrank - 1 + npes) % npes, 0);

    //Recieve the updated distance travelled and speed of car i+1 from PE i+1
    MPI::Status status;
    MPI::COMM_WORLD.Recv(&s[(myrank+1) % npes], 1, MPI_FLOAT, (myrank + 1) % npes, 0, status);
    MPI::COMM_WORLD.Recv(&v[(myrank+1) % npes], 1, MPI_FLOAT, (myrank + 1) % npes, 0, status);
    
    //Compute separation d between car directly in front
    d = s[myrank+1] - s[myrank] - carLength;

    //Calculate acceleration
    a[myrank] = IDM(v[myrank+1],v[myrank],d);

    u[myrank] = v[myrank];

    //Compute and print out the average speed of all of the cars
    MPI::COMM_WORLD.Gather(&u[myrank], 1, MPI_FLOAT, &u[myrank], 1, MPI_FLOAT, 0);

    int sum = 0;
    for (int k=0; k<cars; k++) {
      sum += u[cars];
    }

    int avgSpeed = sum/cars;
    cout << "The average speed of all cars is " << avgSpeed;

    currentSec++;
  }

  MPI::Finalize();
  
  return 0;
}
