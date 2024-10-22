import random

for i in range(10000):
    a = random.randint(0, 2**64 - 1)
    b = random.randint(0, 2**64 - 1)
    m = random.randint(1, 2**64 - 1)
    print(a, b, m)
