#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void writeMatrixToFile(string filename, const vector<vector<int>> &matrix)
{

    ofstream file("files/matrix1_2/" + filename);

    if (file.is_open())
    {
        for (const auto &row : matrix)
        {
            for (const int &element : row)
            {
                file << element << " ";
            }
            file << endl;
        }

        file.close();
        cout << "Matrix has been written to file: " << filename << endl;
    }
    else
    {
        cerr << "Unable to open file: " << filename << endl;
    }
}

void createRandMatrix(string file_name, int size)
{
    vector<vector<int>> matrix(size, vector<int>(size));

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            matrix[i][j] = rand() % 500;
        }
    }
    writeMatrixToFile(file_name, matrix);
}

void read_matrix(vector<vector<int>> &matrix, int size, string filename)
{
    ifstream data;
    data.open("files/matrix1_2/" + filename);

    if (data.is_open())
    {
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix.size(); j++)
            {
                data >> matrix[i][j];
            }
        }
    }
    data.close();
}

void mulMatrix(const vector<vector<int>> &matrix_1, const vector<vector<int>> &matrix_2, vector<vector<int>> &matrix_result)
{
    for (int i = 0; i < matrix_result.size(); i++)
    {
        for (int j = 0; j < matrix_result[i].size(); j++)
        {
            matrix_result[i][j] = 0;
            for (int k = 0; k < matrix_2.size(); k++)
            {
                matrix_result[i][j] += matrix_1[i][k] * matrix_2[k][j];
            }
        }
    }
}

void writeStat(string str, vector<vector<int>> &matrix_result, int size, clock_t end, clock_t start)
{
    ofstream data(str);
    ofstream result("files/result.txt", ios::app);

    for (int i = 0; i < matrix_result.size(); i++)
    {
        for (int j = 0; j < matrix_result[i].size(); j++)
        {
            data << " " << matrix_result[i][j];
        }
        data << endl;
    }
    result << "Size: " << size << " TIme: " << (double(end - start)) / (double(CLOCKS_PER_SEC)) << endl;

    data.close();
    result.close();
}

int main()
{
    std::ofstream file("files/result.txt", std::ios::out | std::ios::trunc);
    std::initializer_list<int> SIZE = {100, 250, 500, 750, 1000, 1500, 2000, 3000};
    int index = 1;

    for (const auto &size : SIZE)
    {
        std::vector<std::vector<int>> matrix_1(size, std::vector<int>(size));
        std::vector<std::vector<int>> matrix_2(size, std::vector<int>(size));
        std::vector<std::vector<int>> matrix_res(size, std::vector<int>(size));

        createRandMatrix("matrix1_" + std::to_string(size) + ".txt", size);
        createRandMatrix("matrix2_" + std::to_string(size) + ".txt", size);

        read_matrix(matrix_1, size, "matrix1_" + std::to_string(size) + ".txt");
        read_matrix(matrix_2, size, "matrix2_" + std::to_string(size) + ".txt");

        clock_t start, end;
        start = clock();
        mulMatrix(matrix_1, matrix_2, matrix_res);
        end = clock();

        writeStat("files/matrix_res/matrix_res_" + std::to_string(size) + ".txt", matrix_res, size, end, start);

        index++;
    }
    return 0;
}