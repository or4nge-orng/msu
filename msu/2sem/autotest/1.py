codomain = map(int, input().split())

def f(x):
    return x**5 + 1

print({f(x) for x in codomain})