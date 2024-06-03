import numpy as np
import os


def load_matrix_from_file(file_name):
    if os.path.exists(file_name):
        matrix = np.loadtxt(file_name)
        return matrix
    else:
        print(f"Файл {file_name} не найден")
        return None


if __name__ == "__main__":
    list_size = [100, 250, 500, 750, 1000, 1500, 2000, 3000]

    for size in list_size:
        matrix1 = load_matrix_from_file(
            f'main/files/matrix1_2/matrix1_{size}.txt')

        matrix2 = load_matrix_from_file(
            f'main/files/matrix1_2/matrix2_{size}.txt')

        matrix_res = load_matrix_from_file(
            f'main/files/matrix_res/matrix_res_{size}.txt')

        if matrix1 is not None and matrix2 is not None and matrix_res is not None:
            if matrix1.shape[1] == matrix2.shape[0]:
                result = np.dot(matrix1, matrix2)
                with open(file='main\\files\\result_py.txt', mode='a', encoding='utf-8') as file:
                    if np.array_equal(result, matrix_res):
                        file.write(f"Mатрицы {size} - совпадают\n")
                    else:
                        file.write(f"Mатрицы {size} - не совпадают\n")
            else:
                print("Невозможно перемножить матрицы из-за несовпадения размерностей")
