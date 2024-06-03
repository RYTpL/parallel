import numpy as np
import os


def write_matrix(path: str, mt: np.array):
    with open(path, "w") as f:
        for i in mt:
            f.write(" ".join(map(str, i)) + "\n")


def read_matrix(path: str) -> np.array:
    with open(path, "r") as f:
        lines = f.readlines()[1:]
    return np.array([[int(y) for y in x.strip().split(" ")] for x in lines])


if __name__ == "__main__":
    path_cpp = "path/to/executable"
    path_matrix = "path/to/matrix/files"
