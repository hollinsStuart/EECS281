import os
import filecmp

if __name__ == "__main__":
    # compile your program
    os.system("gcc -std=c++17 -Wall -Werror -o3 hash hash.cpp")
    os.system("./hash")