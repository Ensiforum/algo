from functools import cache  # only in python 3.8 and above


# time complexity O(2^n)
def naive_fib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return naive_fib(n - 1) + naive_fib(n - 2)


# time complexity O(n)
@cache
def cached_fib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return cached_fib(n - 1) + cached_fib(n - 2)


cache = {0: 0, 1: 1}
def old_cached_fib(n):
    # if n not in cache:
    #    cache[n] = old_cached_fib(n - 1) + old_cached_fib(n - 2)
    # return cache[n]
    return cache.setdefault(n, formula_fib(n-1) + formula_fib(n-2))
    

# time complexity still O(n), but no need to store cache and loop works faster than recursion
def loop_fib(n):
    a, b = 0, 1
    for i in range(n):
        a, b = b, a + b
    return a


# time complexity O(1) using Binet formula
def formula_fib(n):
    golden_ratio = (1 + 5 ** 0.5) / 2
    return int((golden_ratio ** n - (-golden_ratio) ** (-n)) / 5 ** 0.5)
