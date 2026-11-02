from pathlib import Path

def func(array, array_len):
    left, right = 0, array_len - 1
    while left < right:
        while array[left] >= 0 and left < right:
            left += 1

        while array[right] >= 0 and left < right:
            right -= 1

        array[left], array[right] = array[right], array[left]
        left += 1
        right -= 1

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
            func(array, array_len)
            print_array(array, array_len)

    except (FileNotFoundError, IOError):
        print(f"File {filename} not found!")
        

if __name__ == '__main__':
    main('input8.txt')

