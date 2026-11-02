from pathlib import Path

def func(arr, arr_len):
    left = 0
    moves = 0
    write_p = 0
    prev_val = None

    while left < arr_len:
        right = left
        while right + 1 < arr_len and arr[right+1] == arr[left]: 
            right += 1

        cur_val = arr[left]
        if ((left == 0) or prev_val > cur_val) and ((right == arr_len - 1) or (arr[right + 1] > cur_val)):
            arr[write_p] = 0
            write_p += 1
            moves += 1
        else:
            for k in range(left, right + 1):
                if write_p != k:
                    arr[write_p] = arr[k]
                    moves += 1

                write_p += 1

        left = right + 1
        prev_val = cur_val

    
    return write_p

def read_file(file):
    array = []
    for line in file:
        for num in line.strip().split():
            if num.isdigit() or num[1:].isdigit():
                array.append(int(num))
            else:
                raise ValueError(f"only digits allowed, got '{num}': '{type(num).__name__}'")

    if not array: raise ValueError("empty input data")
    return (array, len(array))

def print_array(array: list, array_len: int) -> None:
    for i in range(array_len):
        print(array[i], end=" ")
    print()

def main(filename):
    try:
        with open(Path(__file__).resolve().parent / filename, "r") as file: 
            array, array_len = read_file(file)
            print_array(array, array_len)
            array_len = func(array, array_len)
            print_array(array, array_len)

    except (FileNotFoundError, IOError):
        print(f"File {filename} not found!")
        

if __name__ == '__main__':
    main('input19.txt')

