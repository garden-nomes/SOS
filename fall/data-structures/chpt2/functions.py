import matplotlib.pyplot as plt
from math import *

def log2(x): return log(x, 2)

functions = (
        (lambda x: x, "x", "-"),
        (lambda x: sqrt(x), "sqrt(x)", "--"),
        (lambda x: x**1.5, "x^1.5", "-."),
        (lambda x: x**2, "x^2", ":"),
        (lambda x: x * log2(x), "log(x)", "."),
        (lambda x: x * log2(log2(x)) if x > 1 else 0, "x*log(log(x))", ","),
        (lambda x: x * log2(x)**2, "log(x)^2", "o"),
        (lambda x: x * log2(x**2), "log(x^2)", "v"),
        (lambda x: 2/x, "2/x", "^"),
        (lambda x: 2**x, "2^x", "<"),
        (lambda x: 2**(x/2), "2^(x/2)", ">"),
        (lambda x: x**2 * log2(x), "x^2*log(x)", "1"),
        (lambda x: x**3, "x^3", "2")
)

x = [i / 10.0 for i in range(10, 500)]

for f, l, o in functions:
    plt.plot(x, [f(xx) if f(xx) < 500 else 500 for xx in x], o, label=l)

plt.legend(loc='upper left')
plt.show()
