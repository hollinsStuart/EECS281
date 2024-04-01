import random

if __name__ == "__main__":
    for i in range(1, 4):
        name = 'test-' + str(i) + '-MST.txt'
        f = open(name, "w")
        f.write("10\n")
        f.write(str(random.randint(-2147483648, 2147483647)))
        f.write(' 0\n')
        for j in range(9):
            f.write(str(random.randint(-2147483648, 2147483647)))
            f.write(" ")
            f.write(str(random.randint(-2147483648, 2147483647)))
            f.write("\n")

    for i in range(4, 8):
        name = 'test-' + str(i) + '-FASTTSP.txt'
        f = open(name, "w")
        f.write("10\n")
        f.write(str(random.randint(-2147483648, 2147483647)))
        f.write(" 0\n")
        for j in range(9):
            f.write(str(random.randint(-2147483648, 2147483647)))
            f.write(" ")
            f.write(str(random.randint(-2147483648, 2147483647)))
            f.write("\n")

    for i in range(8, 11):
        name = 'test-' + str(i) + '-OPTTSP.txt'
        f = open(name, "w")
        f.write("10\n")
        f.write(str(random.randint(-2147483648, 2147483647)))
        f.write(" 0\n")
        for j in range(9):
            f.write(str(random.randint(-2147483648, 2147483647)))
            f.write(" ")
            f.write(str(random.randint(-2147483648, 2147483647)))
            f.write("\n")