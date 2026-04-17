import doctest


def task(str='1.txt'):
    """
    >>> f = open('1.txt', 'w')
    >>> b = f.write('1 0\\n1 0 1 0 0\\n 56 1 0 1 0 1 0 0 ')
    >>> f.close()
    >>> task()
    2
    >>> f = open('1.txt', 'w')
    >>> b = f.write('1 0 1 0 1 0 1 0 0')
    >>> f.close()
    >>> task()
    1
    >>> f = open('1.txt', 'w')
    >>> b = f.write('1 2 3 2 1 0 1 0 1 0 2')
    >>> f.close()
    >>> task()
    0
    >>> f = open('1.txt', 'w')
    >>> b = f.write('1    0\\n   1')
    >>> f.close()
    >>> task('2.txt')
    'File not found'
    >>> f = open('1.txt', 'w')
    >>> b = f.write('1    s\\n   1')
    >>> f.close()
    >>> task()
    'Bad file'
    >>> f = open('1.txt', 'w')
    >>> b = f.write(' \\n')
    >>> f.close()
    >>> task()
    'Empty file'
    """
    try:
        k, s = 0, -1
        with open(str, "r") as f:
            for x in map(int, f.read().split()):
                if s == -1: s = 0
                if x == 1:
                    if s in [0, 2, 4]: s += 1
                    elif s == 6: s = 5
                    else: s = 1
                elif x == 0:
                    if s in [1, 3, 5]: s += 1
                    elif s == 6:
                        k += 1
                        s = 0
                    else: s = 0
                else:
                    s = 0
        if s == -1:
            return "Empty file"
        return k

    except ValueError:
        return "Bad file"
    except FileNotFoundError:
        return "File not found"
        

if __name__ == "__main__":
    doctest.testmod(verbose=True)