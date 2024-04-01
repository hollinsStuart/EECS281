import os
import subprocess
import filecmp
import re
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


def compare_files(f1, f2):
    a = open(f1, 'r')
    b = open(f2, 'r')
    a_contents = a.readlines()
    b_contents = b.readlines()
    if b_contents[0] in a_contents:
        return True
    else:
        return False


if __name__ == "__main__":
    tests = ["ab", "c", "d", "e", "f"]
    results = []
    os.system("make clean")
    os.system("make all")
    print("spec:")
    os.system("valgrind --leak-check=full -s ./zoo_valgrind -m MST < spec-test.txt > spec-out-test-MST.txt")
    print("ab:")
    os.system("./zoo -m MST < sample-ab.txt > sample-out-ab-MST.txt")
    print("c:")
    os.system("valgrind --leak-check=full -s ./zoo_valgrind -m MST < sample-c.txt > sample-out-c-MST.txt")
    os.system(" ./zoo_debug -m MST < sample-d.txt > sample-out-d-MST.txt")
    os.system(" ./zoo_debug -m MST < sample-e.txt > sample-out-e-MST.txt")
    os.system(" ./zoo_debug -m MST < sample-f.txt > sample-out-f-MST.txt")
    print("\ntesting MST mode:")
    ans_file = "spec-out-test-MST.txt"
    correct_file = "spec-test-MST-out.txt"
    results.append([compare_files(ans_file, correct_file), "spec"])

    for t in tests:
        print("./zoo -m MST < sample-" + t + ".txt > sample-out-" + t + "-MST.txt")
        os.system("./zoo -m MST < sample-" + t + ".txt > sample-out-" + t + "-MST.txt")
        ans_file = "sample-out-" + t + "-MST.txt"
        correct_file = "sample-" + t + "-MST-out.txt"
        results.append([compare_files(ans_file, correct_file), t])

    print("\n------results------")
    for r in results:
        print(f"    {r[1]:<5} {str(r[0]):>5}")
