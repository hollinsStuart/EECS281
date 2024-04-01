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


if __name__ == "__main__":
    # compile your program
    os.system("make clean")
    os.system("make debug")
    os.system("make valgrind")
    os.system("valgrind --leak-check=full -s ./bank_valgrind -vf spec-reg.txt < spec-commands.txt > specOutV.txt")
    os.system("valgrind --leak-check=full -s ./bank_valgrind -f spec-reg.txt < spec-commands.txt > specOut.txt")
    os.system("./bank_debug -vf test-1-reg.txt < test-1-commands.txt > 1Out.txt")
    os.system("./bank_debug -vf test-2-reg.txt < test-2-commands.txt > 2Out.txt")
    os.system("./bank_debug -vf test-3-reg.txt < test-3-commands.txt > 3Out.txt")
    os.system("./bank_debug -vf test-4-reg.txt < test-4-commands.txt > 4Out.txt")
    os.system("./bank_debug -vf test-5-reg.txt < test-5-commands.txt > 5Out.txt")
    os.system("./bank_debug -vf test-6-reg.txt < test-6-commands.txt > 6Out.txt")
    os.system("./bank_debug -vf test-7-reg.txt < test-7-commands.txt > 7Out.txt")
    os.system("./bank_debug -vf test-11-reg.txt < test-11-commands.txt > 11Out.txt")
    os.system("./bank_debug -vf test-12-reg.txt < test-12-commands.txt > 12Out.txt")

    configure = Config(mode=Mode.txt,
                       output=Output.none,
                       test_file_suffix='.txt',
                       test_output_suffix='.txt',
                       example_file_suffix='.txt',
                       pre_execute_commands=["make clean"],
                       exe_compile_command='make valgrind',
                       exe_run_command="valgrind --leak-check=full -s ./bank_valgrind -vf spec-reg.txt < "
                                       "spec-commands.txt > specOut.txt",
                       exe_name='assembler',
                       example_compile_command='',
                       example_run_command='',
                       example_name='')
    test_file_pattern = 'test-\w+' + configure.test_file_suffix

    if len(configure.pre_execute_commands) != 0:
        for command in configure.pre_execute_commands:
            os.system(command)

    # find test files
    os.chdir("./test")
    current_path = os.getcwd()
    files = os.listdir(current_path)
    os.chdir("..")
    print(os.getcwd())
    for i in range(1, 13):
        if i == 4:
            continue
        run = "./bank_debug -vf ./test/test-" + str(i) + "-reg.txt " + "< ./test/test-" + str(
            i) + "-commands.txt > ./test/" + str(i) + "Out.txt"
        os.system(run)

        ans_file = "./test/" + str(i) + "Out.txt"
        correct_file = "./test/test-" + str(i) + ".out"
        diff_result = filecmp.cmp(ans_file, correct_file, shallow=False)
        print("    test " + str(i) + ": ", end="\t")
        print(diff_result)

    # ans_file = "2Out.txt"
    # correct_file = "2Correct.txt"
    # diff_result = filecmp.cmp(ans_file, correct_file, shallow=False)
    # print(" ")
    # print("My case 2:", end=" ")
    # print(diff_result, end='')

    ans_file = "3Out.txt"
    correct_file = "3Correct.txt"
    diff_result = filecmp.cmp(ans_file, correct_file, shallow=False)
    print(" ")
    print("    My case 3:", end="\t")
    print(diff_result)

    ans_file = "5Out.txt"
    correct_file = "5Correct.txt"
    diff_result = filecmp.cmp(ans_file, correct_file, shallow=False)
    print("    My case 5:", end="\t")
    print(diff_result)

    os.chdir("./lqj")
    current_path = os.getcwd()
    files = os.listdir(current_path)
    os.chdir("..")
    print(" ")
    for i in range(1, 5):
        run = "./bank_debug -vf ./lqj/test-" + str(i) + "-reg.txt " + "< ./lqj/test-" + str(
            i) + "-commands.txt > ./lqj/" + str(i) + "Out.txt"
        os.system(run)
        ans_file = "./lqj/" + str(i) + "Out.txt"
        correct_file = "./lqj/test-" + str(i) + "-output.txt"
        diff_result = filecmp.cmp(ans_file, correct_file, shallow=False)
        print("    lqj " + str(i) + ": ", end="\t")
        print(diff_result)

    print(" ")
    for i in range(1, 22):
        if i == 4:
            continue
        run = "./bank_debug -vf ./zzh/test-" + str(i) + "-reg.txt " + "< ./zzh/test-" + str(
            i) + "-commands.txt > ./zzh/" + str(i) + "Out.txt"
        os.system(run)
        ans_file = "./zzh/" + str(i) + "Out.txt"
        correct_file = "./zzh/test-" + str(i) + ".out"
        diff_result = filecmp.cmp(ans_file, correct_file, shallow=False)
        print("    zzh " + str(i) + ": ", end="\t")
        print(diff_result)

    ans_file = "specOutV.txt"
    correct_file = "spec-output-verbose.txt"
    diff_result = filecmp.cmp(ans_file, correct_file, shallow=False)
    print(" ")
    print("Spec -vf:", end=" ")
    print(diff_result)

    ans_file = "specOut.txt"
    correct_file = "spec-output.txt"
    diff_result = filecmp.cmp(ans_file, correct_file, shallow=False)
    print("Spec -f: ", end=" ")
    print(diff_result)
    print(" ")

    os.system("./bank_debug -vf ./largetest/test-reg.txt < ./largetest/test-commands.txt > ./largetest/lOut.txt")
    ans_file = "./largetest/test.correct"
    correct_file = "./largetest/lOut.txt"
    diff_result = filecmp.cmp(ans_file, correct_file, shallow=False)
    print("Large: ", end=" ")
    print(diff_result)
    print(" ")

    os.system("./bank_debug -f ./pyh/test-reg.txt < ./pyh/test-commands.txt > ./pyh/myOut.txt")
    ans_file = "./pyh/correct.txt"
    correct_file = "./pyh/myOut.txt"
    diff_result = filecmp.cmp(ans_file, correct_file, shallow=False)
    print("    pyh -v: ", end="\t")
    print(diff_result)
    print(" ")

    os.system("./bank_debug -vf ./pyh/test-reg.txt < ./pyh/test-commands.txt > ./pyh/myOutV.txt")
    ans_file = "./pyh/VFcorrect.txt"
    correct_file = "./pyh/myOutV.txt"
    diff_result = filecmp.cmp(ans_file, correct_file, shallow=False)
    print("    pyh -vf:", end="\t")
    print(diff_result)
    print(" ")

    os.system("./bank_debug -vf ./pyh/test-reg.txt < ./pyh/newC.txt > ./pyh/myOutNew.txt")
    ans_file = "./pyh/myOutNew.txt"
    correct_file = "./pyh/newOutCorrect.txt"
    diff_result = filecmp.cmp(ans_file, correct_file, shallow=False)
    print("    pyh new:", end="\t")
    print(diff_result)
    print(" ")

    # os.system(configure.exe_compile_command)
    # if configure.mode == Mode.exe:
    #     os.system(configure.example_compile_command)
    #
    # for test in test_files:
    #     # run test files
    #     assemble = './assembler mult.as mult.mc'
    #     mult = './zsimulator mult.mc > m.txt'
    #     os.system(assemble)
    #     os.system(mult)
    #     if configure.output == Output.TF:
    #         # diff the results
    #         ans_file = 'test_' + test + '_ans.txt'  # test_add_ans.txt
    #         correct_file = 'z_' + test + '_ans.txt'
    #         diff_result = filecmp.cmp(ans_file, correct_file, shallow=False)
    #         print(test, end=': \t')
    #         print(diff_result)
#     "./bank_debug -vf /test/test-1-reg.txt <./test/test-1-commands.txt >./test/1Out.txt"
