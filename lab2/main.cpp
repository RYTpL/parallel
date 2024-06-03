#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void writeMatrixToFile(string filename, const vector<vector<int>> &matrix)
{
    ofstream file("C:/PYTHON/laba_pp/matrix/matrix_1_2/" + filename);

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
    data.open("C:/PYTHON/laba_pp/matrix/matrix_1_2/" + filename);

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

void mulMatrix(const vector<vector<int>> &matrix_1, const vector<vector<int>> &matrix_2, vector<vector<int>> &matrix_3)
{
    for (int i = 0; i < matrix_3.size(); i++)
    {
        for (int j = 0; j < matrix_3[i].size(); j++)
        {
            matrix_3[i][j] = 0;
            for (int k = 0; k < matrix_2.size(); k++)
            {
                matrix_3[i][j] += matrix_1[i][k] * matrix_2[k][j];
            }
        }
    }
}

void writeResult(string str, vector<vector<int>> &matrix_3, int size, clock_t end, clock_t start, int i)
{
    ofstream data(str);
    ofstream result("C:/PYTHON/laba_pp/file/result.txt", ios::app);

    for (int i = 0; i < matrix_3.size(); i++)
    {
        for (int j = 0; j < matrix_3[i].size(); j++)
        {
            data << " " << matrix_3[i][j];
        }
        data << endl;
    }
    cout << "Matrix has been created:" << str << endl;
    result << "Size: " << size << " №: " << i << " Time: " << (double(end - start)) / (double(CLOCKS_PER_SEC)) << endl;

    data.close();
    result.close();
}

std::vector<std::vector<int>> createMatrix(int size)
{
    return std::vector<std::vector<int>>(size, std::vector<int>(size));
}

int main()
{
    std::vector<int> sizes = {500, 2000, 4500, 8000, 12500, 18000, 24500};

    for (int size : sizes)
        for (int i = 1; i < 4; i++)
        {
            std::vector<std::vector<int>> matrix_1 = createMatrix(size);
            std::vector<std::vector<int>> matrix_2 = createMatrix(size);
            std::vector<std::vector<int>> matrix_3 = createMatrix(size);

            createRandMatrix("m_1_" + std::to_string(size) + "_" + std::to_string(i) + ".txt", size);
            createRandMatrix("m_2_" + std::to_string(size) + "_" + std::to_string(i) + ".txt", size);

            read_matrix(matrix_1, size, "m_1_" + std::to_string(size) + "_" + std::to_string(i) + ".txt");
            read_matrix(matrix_2, size, "m_2_" + std::to_string(size) + "_" + std::to_string(i) + ".txt");

            clock_t start, end;

            if (!matrix_1.empty() && !matrix_2.empty())
            {
                start = clock();
                mulMatrix(matrix_1, matrix_2, matrix_3);
                end = clock();
            }

            writeResult("C:/PYTHON/laba_pp/matrix/matrix_3/m_" + std::to_string(size) + "_" + std::to_string(i + 1) + ".txt", matrix_3, size, end, start, i);
        }
    return 0;
}
