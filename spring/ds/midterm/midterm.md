DS Spring 2016 Midterm

Noah Weiner

## Problem 1
```Python
def sort5(a, b, c, d, e):
    # sort sublists [a, b] and [c, d, e]
    if d < c:
        swap(d, c)
    if e < d:
        swap(e, d)
    if d < c:
        swap(d, c)
    if b < a:
        swap(b, a)

    # merge lists
    if a < c:
        if b < c:
            return [a, b, c, d, e]
        else:
            if b < d:
                return [a, c, b, d, e]
            else:
                if b < e:
                    return [a, c, d, b ,e]
                else:
                    return [a, c, d, e, b]
    else:
        if a < d:
            if b < d:
                return [c, a, b, d, e]
            else:
                if b < e:
                    return [c, a, d, b, e]
                else:
                    return [c, a, d, e, b]
        else:
            if a < e:
                return [c, d, e, a, b]
            else:
                if b < e:
                    return [c, d, a, b, e]
                else:
                    return [c, d, a, e, b]
```

## Problem 2
```C++
int DisjSets::find(int x) {
    for (; s[x] != -1; x = s[x])
        if (s[s[x]] != -1)
            s[x] = s[s[x]];

    return x;
}
```

## Problem 3

```
From A to   |   Path
---------------------------------
        B   |   A-->B
        C   |   A-->C
        D   |   A-->C-->D
        E   |   A-->B-->G-->E
        F   |   A-->B-->G-->E-->F
        G   |   A-->B-->G

```

## Problem 4

Finding the path from A to D:
```
       (D)
   3  /   \  3
    /  -5   \
 (B)---------(C)
    \       /
   1  \   /  3
       (A)
```

Dijkstra would produce `A->B->D`, when the shortest path is actually `A->C->B->D`.


## Problem 5

### Prim's

Interval trees:
```
1. (1)-(3)
2. (1)-(3)-(6)
3. (1)-(3)-(6)-(4)
```
Final:
```
(1)-(3)-(6)-(4)
      '-(2)-(5)
```

### Kruskal's

Interval trees:
```
1. (1)-(3)  (6)-(4)  (2)-(5)
2. (1)-(3)-(6)-(4)  (2)-(5)
```
Final:
```
(1)-(3)-(6)-(4)
      '-(2)-(5)
```