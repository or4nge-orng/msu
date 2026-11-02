from pathlib import Path
from ast import literal_eval

def func(array: list, array_len: int):
    if  not (min(array) == 0 and max(array) + 1 == array_len == len(set(array))):
        raise ValueError("array must be a permutation")

    for i in range(array_len):
        if array[i] < 0: continue

        cur_idx = i
        cur_val = array[i]

        while cur_val >= 0:
            next_idx = cur_val
            next_val = array[next_idx]

            array[next_idx] = -(cur_idx + 1)

            cur_idx = next_idx
            cur_val = next_val

    for i in range(array_len):
        array[i] = -(array[i]+1)

def read_file(file):
    array = []
    try:
        for line in file:
            for num in line.strip().split():
                array.append(int(num))

        if not array: raise ValueError("empty input data")
        return (array, len(array))
    except ValueError:
        raise ValueError(f"only digits allowed, got '{num}'") from None

def print_array(array: list, array_len: int) -> None:
    for i in range(array_len):
        print(array[i], end=" ")
    print()

def main(filename):
    try:
        with open(Path(__file__).resolve().parent / filename, "r") as file: 
            array, array_len = read_file(file)
            print_array(array, array_len)
            func(array, array_len)
            print_array(array, array_len)

    except (FileNotFoundError, IOError):
        print(f"File {filename} not found!")
    except Exception as e:
        print(e)
        

if __name__ == '__main__':
    main('input44.txt')

