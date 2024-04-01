import os
import subprocess
import filecmp
import re
from enum import Enum
from decimal import Decimal


class Mode(Enum):
    exe = 1
    txt = 2


class Output(Enum):
    none = 0
    TF = 1
    long = 2


# TODO: modify test configurations
class Config:
    def __init__(self, mode=Mode.exe, output=Output.TF, test_file_suffix='.as', test_output_suffix='',
                 example_file_suffix='.txt', pre_execute_commands=[], exe_compile_command='', exe_run_command='',
                 exe_name='assembler', example_compile_command='', example_run_command='', example_name=''):
        self.mode = Mode.exe
        self.output = Output.TF
        self.test_file_suffix = '.as'
        self.test_output_suffix = '.txt'
        self.example_file_suffix = '.txt'
        self.pre_execute_commands = []
        self.exe_compile_command = 'gcc -std=c99 -Wall -Werror -o3 assembler.c -o assembler -lm'
        self.exe_name = ''
        self.example_compile_command = ''
        self.example_name = ''


def compare_files(f1, f2):
    a = open(f1, 'r')
    b = open(f2, 'r')
    a_contents = Decimal(a.readlines()[0])
    b_contents = Decimal(b.readlines()[0])
    if 0.01 >= a_contents - b_contents >= -0.01:
        result = "Pass"
    else:
        result = "False"
    print(f" {result:<8} {a_contents:<15}  {b_contents:<15}")


if __name__ == "__main__":
    tests = ["c", "d", "e", "f"]
    os.system("make clean")
    os.system("make all")

    print("\ntesting OPTTSP mode:")
    print("               My Ans           Correct   ")
    os.system("time valgrind --leak-check=full -s ./zoo_valgrind -m OPTTSP < spec-test.txt > spec-out-test-OPTTSP.txt")
    ans_file = "spec-out-test-OPTTSP.txt"
    correct_file = "spec-test-OPTTSP-out.txt"
    print("spec:", end='')
    compare_files(ans_file, correct_file)

    os.system("time ./zoo -m OPTTSP < test-10-OPTTSP.txt > out-10-OPTTSP.txt")
    ans_file = "out-10-OPTTSP.txt"
    correct_file = "test-10-OPTTSP.correct"
    print("  10:", end='')
    compare_files(ans_file, correct_file)

    for t in tests:
        # if t == "e" or t == "f":
            # print("at " + t)
            # print("./zoo -m OPTTSP < sample-" + t + ".txt > sample-out-" + t + "-OPTTSP.txt")
        os.system("time ./zoo -m OPTTSP < sample-" + t + ".txt > sample-out-" + t + "-OPTTSP.txt")
        ans_file = "sample-out-" + t + "-OPTTSP.txt"
        correct_file = "sample-" + t + "-OPTTSP-out.txt"
        print(f"{t:>4}:", end='')
        compare_files(ans_file, correct_file)
# ./zoo -m OPTTSP < sample-c.txt > sample-out-c-OPTTSP.txt

