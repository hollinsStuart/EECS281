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
        self.test_file_suffix = ".as"
        self.test_output_suffix = ".txt"
        self.example_file_suffix = ".txt"
        self.pre_execute_commands = []
        self.exe_compile_command = "make"
        self.exe_name = ""
        self.example_compile_command = ""
        self.example_name = ""


if __name__ == "__main__":
    os.system("make all")
    os.system("./zombbb_debug -vms 100 < Sample-large.txt > large-vms100-ans.txt")
    large_result = filecmp.cmp("large-vms100-ans.txt", "Sample-large-out-vms100.txt", shallow=False)
    print("----------------------------------------")
    print("Sample-large-vms100: ", end='')
    print(large_result)
    print("----------------------------------------")

    os.system("./zombbb_debug -vms 10 < Sample-small.txt > small-vms10-ans.txt")
    small_result = filecmp.cmp("small-vms10-ans.txt", "Sample-small-out-vms10.txt", shallow=False)
    print("----------------------------------------")
    print("Sample-small-vms10: ", end='')
    print(small_result)
    print("----------------------------------------")

    os.system("./zombbb_debug -vms 10 < spec.txt > spec-vms10-ans.txt")
    small_result = filecmp.cmp("spec-out-vms10.txt", "spec-vms10-ans.txt", shallow=False)
    print("----------------------------------------")
    print("spec-vms10: ", end='')
    print(small_result)
    print("----------------------------------------")

    os.system("./zombbb_debug -vms 10 < simpleTest.txt > simple-test-ans.txt")
    os.system("./zombbb_debug -vms 10 < twoTest.txt > two-test-ans.txt")
    os.system("./zombbb_debug -vms 10 < slowTest.txt > slow-test-ans.txt")
    os.system("./zombbb_debug -vms 10 < lifeTest.txt > life-test-ans.txt")
    print("AlwaysDie....")
    os.system("./zombbb_debug -vms 10 < alwaysDie.txt > alwaysDie-ans.txt")
    print("LessThanStats....")
    os.system("./zombbb_debug -vms 100 < lessThanStats.txt > lessThanStats-ans.txt")
    os.system("./zombbb_debug < twoTest.txt > two-test-clean-ans.txt")
    os.system("./zombbb_debug < spec.txt > spec-clean-ans.txt")
    os.system("./zombbb_debug < test-9-v.txt > nothing-ans.txt")
