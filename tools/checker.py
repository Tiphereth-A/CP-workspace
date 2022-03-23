#!/usr/bin/env python3

import argparse
import re
import sys
from logging import Logger, basicConfig, getLogger
from os import getenv
from subprocess import run, PIPE

from lib import standardized_folder, remove, compile_gpp, make_folder_if_not_exist, write_input_output_answer, \
    regex_space_in_the_end_bytes, generate_data, compile_args, compile_args_chk_std

logger = getLogger(__name__)  # type: Logger

if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv('LOG_LEVEL', 'INFO'),
    )
    parser = argparse.ArgumentParser(description='Checker')
    parser.add_argument('-ns', '--no-strict-mode', action='store_true',
                        help='Ignore difference of nonprinting characters in the end each line')
    parser.add_argument('-n', '--num', type=int, help='Number of testcases, default 5000', default=5000)
    parser.add_argument('-t', '--time', type=float, help='Time limit (s), default 1.0', default=1.0)
    parser.add_argument('-g', '--gen-file', help=r'Generator C++ source file, default src\gen.cpp',
                        default=sys.path[0] + r'\src\gen.cpp')
    parser.add_argument('-s', '--std-file', help=r'Standard C++ source file, default src\std.cpp',
                        default=sys.path[0] + r'\src\std.cpp')
    parser.add_argument('-c', '--check-file', help=r'C++ source file which will be checked, default src\my.cpp',
                        default=sys.path[0] + r'\src\my.cpp')
    parser.add_argument('-spj', '--spj-file', type=str, help='Special Judge C++ source file, optimal')
    parser.add_argument('-o', '--output', help=r'Output folder, default out', default=sys.path[0] + r'\out')
    opts = parser.parse_args()

    gen_file, std_file, chk_file, spj_file = opts.gen_file, opts.std_file, opts.check_file, opts.spj_file
    output_folder = standardized_folder(opts.output)

    gen_exe, std_exe, chk_exe, spj_exe = output_folder + r'\gen', output_folder + r'\std', output_folder + r'\check', output_folder + r'\spj'
    din_path, dout_path, dans_path = output_folder + r'\data\in.in', output_folder + r'\data\out.out', output_folder + r'\data\ans.out'

    make_folder_if_not_exist(output_folder)
    make_folder_if_not_exist(output_folder + r'\data')

    [remove(logger, filen) for filen in
     [gen_exe, std_exe, chk_exe, spj_exe, gen_exe + '.exe', std_exe + '.exe', chk_exe + '.exe', spj_exe + '.exe',
      din_path, dout_path, dans_path]]

    compile_gpp(logger, gen_file, gen_exe, compile_args)
    compile_gpp(logger, std_file, std_exe, compile_args_chk_std)
    compile_gpp(logger, chk_file, chk_exe, compile_args_chk_std)
    if spj_file:
        compile_gpp(logger, spj_file, spj_exe, compile_args)

    for cnt in range(opts.num):
        din = generate_data(logger, generator_file=gen_exe, data_id=cnt)
        dans = run(std_exe, input=din.stdout, stdout=PIPE, shell=False, check=True)
        dout = run(chk_exe, input=din.stdout, stdout=PIPE, shell=False, check=True, timeout=opts.time)

        if spj_file:
            write_input_output_answer(logger=logger, input_file=din_path, input_info=din.stdout,
                                      output_file=dout_path, output_info=dout.stdout,
                                      answer_file=dans_path, answer_info=dans.stdout)

            dspj = run([spj_exe, din_path, dout_path, dans_path], stdout=PIPE, shell=False)
            if dspj.returncode:
                raise Exception('spj returned {}, rather than 0'.format(dspj.returncode))
        elif opts.no_strict_mode:
            for [line, line_s] in zip(dout.stdout.splitlines(), dans.stdout.splitlines()):
                if re.sub(regex_space_in_the_end_bytes, ''.encode(), line) != \
                        re.sub(regex_space_in_the_end_bytes, ''.encode(), line_s):
                    write_input_output_answer(logger=logger, input_file=din_path, input_info=din.stdout,
                                              output_file=dout_path, output_info=dout.stdout,
                                              answer_file=dans_path, answer_info=dans.stdout)
                    raise Exception('Wrong answer!')
        else:
            if dout.stdout != dans.stdout:
                write_input_output_answer(logger=logger, input_file=din_path, input_info=din.stdout,
                                          output_file=dout_path, output_info=dout.stdout,
                                          answer_file=dans_path, answer_info=dans.stdout)
                raise Exception('Wrong answer!')
