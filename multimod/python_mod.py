with open('input', 'r') as f:
    for line in f:
        tokens = line.split()
        a = int(tokens[0])
        b = int(tokens[1])
        m = int(tokens[2])
        print(f"{a} * {b} mod {m} = {(a * b) % m}")
