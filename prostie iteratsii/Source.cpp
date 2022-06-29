#include <mpi.h>
#include <iostream>
#include <cmath>

using namespace std;

double eps = 0.001;
static const int n = 4;
double masA[n][n] = { { 0.05, -0.06, -0.12, 0.14 },
                      { 0.04, -0.12, 0.68, 0.11 },
                      { 0.34, 0.08, -0.06, 0.44 },
                      { 0.11, 0.12, -0.03, -0.8 } };

double masB[n] = { -2.17, 1.4, -2.1, -0.8 };




int main() {
    MPI_Init(NULL, NULL);
    double starttime, endtime;
    starttime = MPI_Wtime();

    int rank, size;
   
    //MPI_Status status;
    //MPI_Request request;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double rbufA[10000];
    double rbuf[10000];
    double rbufB[10000];
    double temp = 0.0;
    double temp1[3] = { 0.0,0.0,0.0 };
    double x[n], x0[n], E[n], max[n] = { 0.0,0.0,0.0,0.0 };
    bool enough = true;


    for (int i = 0; i < n; i++) {
        x0[i] = masB[i];
    }
    int counter = 0, counter1=0;
    if (rank == 0) {
        MPI_Bcast(masA, n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Scatter(masB, n, MPI_DOUBLE, rbufA, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
 
    for (size_t i = 0; i < 10000; i++)
    {


        x[rank] = 0.0;
        for (int j = 0; j < n; j++) {
            x[rank] += masA[rank][j] * x0[j];
        }


        x[rank] += masB[rank];
        E[rank] = fabs(x[rank] - x0[rank]);
        max[rank] = 0.0;


        if (max[rank] < E[rank]) {
            max[rank] = E[rank];
        }
        x0[rank] = x[rank];

        counter++;
        MPI_Gather(&max[0], 4, MPI_DOUBLE, rbufB, 4, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        if (rank == 0)
        {
            for (int i = 0; i < 4; i++) {
                if (max[i] > eps)
                {

                }
                else
                {
                    counter1++;

                }

            }
            if (counter1 == 4)
            {
                break;
            }

        }
    }

    MPI_Gather(&x[0], 4, MPI_DOUBLE, rbuf, 4, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        cout << endl << "Kol iter: " << counter << endl << endl;
        for (size_t i = 0; i < n; i++)
        {
            cout << "x" << i + 1 << "=" << x[i] << " " << endl;
        }
        
    }

    

    endtime = MPI_Wtime();
    printf("vipolnenie zanyalo %f seconds\n", endtime - starttime);
    MPI_Finalize();
    return 1;
}