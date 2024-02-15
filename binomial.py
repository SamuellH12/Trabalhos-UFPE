
print(  "(N escolhe X) * p^x * q^(n-x) " )


def fat(x):
    f = 1
    for i in range(1, x+1):
        f *= i
    return f

def escolhe(n, x):
    return fat(n) / (fat(x) * fat(n - x))


x = int(input("X = "))
n = int(input("N = "))
p = float(input("P = "))
q = 1 - p

while x > 0:
    print("ans =", escolhe(n, x) * (p**x) * (q**(n-x)))
    x = int(input("X = "))
