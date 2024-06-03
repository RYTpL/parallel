#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mpi.h>
#include <fstream>

using namespace std;

void read_matrix(const char *path, vector<int> &matrix, int N)
{
    ifstream fin(path);
    if (fin.is_open())
    {
        for (int i = 0; i < N * N; ++i)
        {
            fin >> matrix[i];
        }
        fin.close();
    }
    else
    {
        cerr << "Error opening file: " << path << endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
}

void write_matrix(const char *path, const vector<int> &matrix, int N)
{
    ofstream fout(path);
    if (fout.is_open())
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                fout << matrix[i * N + j] << " ";
            }
            fout << "\n";
        }
        fout.close();
    }
    else
    {
        cerr << "Error opening file: " << path << endl;
    }
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if (argc < 6)
    {
        if (rank == 0)
        {
            cerr << "Usage: " << argv[0] << " <matrix1> <matrix2> <result> <N> <stats>" << endl;
        }
        MPI_Finalize();
        return -1;
    }

    const char *path_1 = argv[1];
    const char *path_2 = argv[2];
    const char *res = argv[3];
    int N = atoi(argv[4]);
    const char *stats = argv[5];

    int rows = N / numprocs;
    vector<int> matrixA(N * N), matrixB(N * N), matrixC(N * N), buffer(rows * N), result(N * N);

    double start, stop;
    if (rank == 0)
    {
        start = MPI_Wtime();
        read_matrix(path_1, matrixA, N);
        read_matrix(path_2, matrixB, N);
    }

    MPI_Bcast(matrixB.data(), N * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(matrixA.data(), rows * N, MPI_INT, buffer.data(), rows * N, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            matrixC[i * N + j] = 0;
            for (int k = 0; k < N; ++k)
            {
                matrixC[i * N + j] += buffer[i * N + k] * matrixB[k * N + j];
            }
        }
    }

    MPI_Gather(matrixC.data(), rows * N, MPI_INT, result.data(), rows * N, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        if (N % numprocs != 0)
        {
            for (int i = numprocs * rows; i < N; ++i)
            {
                for (int j = 0; j < N; ++j)
                {
                    result[i * N + j] = 0;
                    for (int k = 0; k < N; ++k)
                    {
                        result[i * N + j] += matrixA[i * N + k] * matrixB[k * N + j];
                    }
                }
            }
        }

        write_matrix(res, result, N);

        stop = MPI_Wtime();
        cout << "Execution time: " << stop - start << " seconds" << endl;
    }

    MPI_Finalize();
    return 0;
}
