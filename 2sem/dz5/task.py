import doctest


def task(str='1.txt'):
    """
    >>> f = open('1.txt', 'w')
    >>> b = f.write('1\\n2')
    >>> f.close()
    >>> task()
    24
    >>> f = open('1.txt', 'w')
    >>> b = f.write('1\\n2\\n3')
    >>> f.close()
    >>> task()
    120
    >>> f = open('1.txt', 'w')
    >>> b = f.write('5')
    >>> f.close()
    >>> task()
    50
    >>> f = open('1.txt', 'w')
    >>> b = f.write('-1\\n1')
    >>> f.close()
    >>> task()
    3
    >>> f = open('1.txt', 'w')
    >>> b = f.write('1    0\\n   1')
    >>> f.close()
    >>> task()
    12
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
        P, T, s, j = 0, 0, 0, 0
        with open(str, "r") as f:
            
            for line in f:
                
                if not line.strip():
                    continue

                for x in line.split():
                    xj = int(x)
                    j += 1
                    
                    s += xj * T + xj * P * j
                    s += (j + j) * xj * xj

                    P += xj
                    T += xj * j
        if j == 0: return "Empty file"
        return s
    except ValueError:
        return "Bad file"
    except FileNotFoundError:
        return "File not found"
        

if __name__ == "__main__":
    doctest.testmod()