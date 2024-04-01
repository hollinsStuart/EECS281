import os
import subprocess
import filecmp
import re
from decimal import Decimal
from enum import Enum


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


def compare_files(f1, f2, *f3):
    a = open(f1, 'r')
    b = open(f2, 'r')
    a_contents = a.readlines()
    b_contents = b.readlines()
    # try:
    #     with open(f3) as f_obj:
    #         contents = f_obj.read()
    # except FileNotFoundError:
    #     msg = "Sorry, the file "+ f3 + "does not exist."
    #     print(msg) # Sorry, the file John.txt does not exist.
    if Decimal(b_contents[0]) >= Decimal(a_contents[0]):
        result = 'Pass'
    else:
        result = 'Fail'
    print(f" {result}  {Decimal(a_contents[0]):<14}  {Decimal(b_contents[0]):<10}", end='')


if __name__ == "__main__":
    tests = ["ab", "c", "d", "e", "f"]
    results = []
    os.system("make clean")
    os.system("make all")
    # print("spec:")
    os.system("valgrind --leak-check=full -s ./zoo_valgrind -m FASTTSP < spec-test.txt > spec-out-test-FASTTSP.txt")
    # print("ab:")
    # os.system("./zoo -m FASTTSP < sample-ab.txt > sample-out-ab-FASTTSP.txt")
    # print("c:")
    # os.system("valgrind --leak-check=full -s ./zoo_valgrind -m FASTTSP < sample-c.txt > sample-out-c-FASTTSP.txt")
    # os.system(" ./zoo_debug -m FASTTSP < sample-d.txt > sample-out-d-FASTTSP.txt")
    # os.system(" ./zoo_debug -m FASTTSP < sample-e.txt > sample-out-e-FASTTSP.txt")
    # os.system(" ./zoo_debug -m FASTTSP < sample-f.txt > sample-out-f-FASTTSP.txt")
    print("\ntesting FASTTSP mode:")
    print("            My Ans      Correct       Optimal")
    ans_file = "spec-out-test-FASTTSP.txt"
    correct_file = "spec-test-FASTTSP-out.txt"
    print("spec:", end='')
    compare_files(ans_file, correct_file)
    opt_file = "spec-test-OPTTSP-out.txt"
    f = open(opt_file, 'r')
    print(f"    {f.readlines()[0]}", end='')

    for t in tests:
        # if t == "ab":
        #     continue
        # print("./zoo -m FASTTSP < sample-" + t + ".txt > sample-out-" + t + "-FASTTSP.txt")
        os.system("./zoo -m FASTTSP < sample-" + t + ".txt > sample-out-" + t + "-FASTTSP.txt")
        ans_file = "sample-out-" + t + "-FASTTSP.txt"
        correct_file = "sample-" + t + "-FASTTSP-out.txt"
        opt_file = "sample-" + t + "-OPTTSP-out.txt"
        print(f"{t:>4}:", end='')
        compare_files(ans_file, correct_file)
        if t == "ab":
            print("")
            continue
        f = open(opt_file, 'r')
        print(f"    {f.readlines()[0]}", end='')
