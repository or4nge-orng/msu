import doctest


def task(filename='1.txt'):
    """
    Return max_{i>j} (x_i - x_j)
    With O(1) additional memory (not counting file input).
    Reads and parses integers on the fly.

    Parameters:
        filename (str): имя файла с целыми числами, разделёнными пробелами

    Returns:
        int: максимальное значение (x_i - x_j) для i > j
        "Empty file" если файл пуст или содержит <2 чисел
        "Bad file" если встречены нечисловые данные
        "File not found" если файл не существует

    Examples:
    >>> with open('test1.txt', 'w') as f:
    ...     _ = f.write("5 2 8 1")
    >>> task('test1.txt')
    6

    >>> with open('test2.txt', 'w') as f:
    ...     _ = f.write("1 2 3 4")
    >>> task('test2.txt')
    3

    >>> with open('test3.txt', 'w') as f:
    ...     _ = f.write("4 3 \\n2 1")
    >>> task('test3.txt')
    -1

    >>> with open('test4.txt', 'w') as f:
    ...     _ = f.write("")
    >>> task('test4.txt')
    'Empty file'

    >>> with open('test5.txt', 'w') as f:
    ...     _ = f.write("42")
    >>> task('test5.txt')
    'Empty file'

    >>> with open('test6.txt', 'w') as f:
    ...     _ = f.write("10 -5 20 0")
    >>> task('test6.txt')
    25

    >>> with open('test7.txt', 'w') as f:
    ...     _ = f.write("1 a 3")
    >>> task('test7.txt')
    'Bad file'

    >>> task('nonexistent_file.txt')
    'File not found'

    >>> with open('test8.txt', 'w') as f:
    ...     _ = f.write("50    300")
    >>> task('test8.txt')
    250

    >>> with open('test9.txt', 'w') as f:
    ...     _ = f.write("0 0 0 0")
    >>> task('test9.txt')
    0
    """
    try:
        with open(filename, 'r') as f:
            buffer = ""
            min_val = None
            max_diff = float('-inf')
            count = 0

            while True:
                char = f.read(1)
                if not char:  # EOF
                    if buffer == "":
                        break
                    else:
                        # Обрабатываем последнее число
                        try:
                            num = int(buffer)
                        except ValueError:
                            return "Bad file"
                        buffer = ""
                else:
                    if char in ' \n\r\t':
                        if buffer == "":
                            continue  # пропускаем лишние пробелы
                        else:
                            try:
                                num = int(buffer)
                            except ValueError:
                                return "Bad file"
                            buffer = ""
                    else:
                        buffer += char
                        continue  # не обрабатываем, пока не встретим пробел или EOF

                # Если мы здесь, значит, num определено (из пробела или EOF)
                count += 1

                if count == 1:
                    min_val = num
                else:
                    diff = num - min_val
                    if diff > max_diff:
                        max_diff = diff
                    if num < min_val:
                        min_val = num

            # После цикла: если buffer не пуст, но не было пробела
            if buffer != "":
                try:
                    num = int(buffer)
                except ValueError:
                    return "Bad file"
                count += 1
                if count == 1:
                    pass
                else:
                    diff = num - min_val
                    if diff > max_diff:
                        max_diff = diff
                    if num < min_val:
                        min_val = num

            if count < 2:
                return "Empty file"

            return max_diff

    except FileNotFoundError:
        return "File not found"
    except Exception as e:
        return "Bad file"

if __name__ == "__main__":
    doctest.testmod(verbose=True)
