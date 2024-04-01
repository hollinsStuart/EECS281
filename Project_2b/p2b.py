import os
import subprocess
import filecmp
import re
from enum import Enum
import threading
import time


class Mode(Enum):
    exe = 1
    txt = 2
    none = 3


class Output(Enum):
    none = 0
    TF = 1
    long = 2


class Config:
    def __init__(
        self,
        mode=Mode.exe,
        output=Output.TF,
        test_file_suffix=".as",
        test_output_suffix="",
        example_file_suffix=".txt",
        pre_execute_commands=[],
        exe_compile_command="",
        exe_run_command="",
        exe_name="assembler",
        example_compile_command="",
        example_run_command="",
        example_name="",
    ):
        self.mode = Mode.exe
        self.output = Output.TF
        self.test_file_suffix = ".txt"
        self.test_output_suffix = ".ans"
        self.example_file_suffix = ".correct"
        self.pre_execute_commands = []
        self.exe_compile_command = "make all"
        self.exe_name = ""
        self.example_compile_command = ""
        self.example_name = ""


if __name__ == "__main__":
    # TODO: modify the fields of configure
    configure = Config(
        mode=Mode.none,
        output=Output.TF,
        test_file_suffix=".txt",
        test_output_suffix=".ans",
        example_file_suffix=".txt",
        pre_execute_commands=["make all"],
        exe_compile_command='',
        exe_run_command="./testPQ",
        exe_name="testPQ",
        example_compile_command="",
        example_run_command="",
        example_name="",
    )
    os.system("make valgrind")
    os.system("valgrind --leak-check=full -s ./PQtest_valgrind > ./zzh/my_results.txt")
    # os.system("valgrind --leak-check=full --show-leak-kinds=all ./PQtest_valgrind")
    # subprocess.run("g++ -std=c++17 test -Wall -g3 test.cpp -lm")
    # subprocess.run("./test")

    # current_path = os.getcwd()
    # files = os.listdir(current_path)
    # sample_file_pattern = "Sample-+.txt"
    #
    # test_file_pattern = "test-+" + configure.test_file_suffix
    # # find test files
    #
    # test_files = []
    # sample_files = []
    # for file in files:
    #     if re.match(sample_file_pattern, file, flags=0) is not None:
    #         hyphen = file.rfind('-')
    #         sample_files.append(file)
    #     if re.match(test_file_pattern, file, flags=0) is not None:
    #         name = file[5: len(file) - len(configure.test_file_suffix)]
    #         test_files.append(name)
    # print(test_files)
    # print(sample_files)
    #
    # os.system(configure.exe_compile_command)
    # if configure.mode == Mode.exe:
    #     os.system(configure.example_compile_command)

    # for test in test_files:
    #     # run test files
    #     if configure.output == Output.TF:
    #         # diff the results
    #         ans_file = "test_" + test + "_ans.txt"  # test_add_ans.txt
    #         correct_file = "z_" + test + "_ans.txt"
    #         diff_result = filecmp.cmp(ans_file, correct_file, shallow=False)
    #         print(test, end=": \t")
    #         print(diff_result)
