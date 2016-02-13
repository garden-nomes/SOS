import matplotlib.pyplot as plt
from math import *

def log2(x): return log(x, 2)

functions = (
        (lambda x: x * log2(x), "NlogN", "-"),
        (lambda x: x**(1+(1/sqrt(log2(x)))) if x != 1 and x != 0 else 0, "N^(1 + 1/sqrt(logN))", "-")
)

x = [i / 10.0 for i in range(10, 500)]

for f, l, o in functions:
    plt.plot(x, [f(xx) if f(xx) < 500 else 500 for xx in x], o, label=l)

plt.legend(loc='upper left')
plt.show()
