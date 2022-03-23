#!/usr/bin/env python3

import argparse
import sys
from logging import Logger, basicConfig, getLogger
from os import getenv
from subprocess import run
from threading import Thread

from lib import compile_args, clear_folder, remove, standardized_folder, compile_gpp, \
    make_folder_if_not_exist, generate_single_dataset, compress_args

logger = getLogger(__name__)  # type: Logger

if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv('LOG_LEVEL', 'INFO'),
    )
    parser = argparse.ArgumentParser(description='Dataset Generator')
    parser.add_argument('-n', '--num', type=int, help='Number of data, default 20', default=20)
    parser.add_argument('-t', '--thread', type=int, help='Thread of generating data, default 8', default=8)
    parser.add_argument('-g', '--gen-file', help=r'Generator C++ source file, default src\gen.cpp',
                        default=sys.path[0] + r'\src\gen.cpp')
    parser.add_argument('-s', '--std-file', help=r'Standard C++ source file, default src\std.cpp',
                        default=sys.path[0] + r'\src\std.cpp')
    parser.add_argument('-o', '--output', help=r'Output folder, default out', default=sys.path[0] + r'\out')
    opts = parser.parse_args()

    gen_file = opts.gen_file
    std_file = opts.std_file
    data_total = opts.num
    thread_num = opts.thread
    output_folder = standardized_folder(opts.output)

    gen_exe, std_exe = output_folder + r'\gen', output_folder + r'\std'
    din_path, dout_path, alldata_path, archive_path = output_folder + r'\data\{}.in', output_folder + r'\data\{}.out', output_folder + r'\data\*', output_folder + r'\data.zip'

    make_folder_if_not_exist(output_folder)
    make_folder_if_not_exist(output_folder + r'\data')

    [remove(logger, filen) for filen in [gen_exe, std_exe, gen_exe + '.exe', std_exe + '.exe', archive_path]]
    clear_folder(logger, output_folder + r'\data')

    compile_gpp(logger, gen_file, gen_exe, compile_args)
    compile_gpp(logger, std_file, std_exe, compile_args)


    def _gen(_id: int):
        generate_single_dataset(logger, generator_file=gen_exe, standard_file=std_exe, data_id=_id,
                                in_path=din_path.format(_id), out_path=dout_path.format(_id))


    for cnt in range(1, data_total // thread_num * thread_num, thread_num):
        _ = [Thread(target=_gen, args=(cnt + i,)) for i in range(thread_num)]
        [t.start() for t in _]
        [t.join() for t in _]

    if data_total % thread_num:
        _ = [Thread(target=_gen, args=(i,)) for i in range(data_total // thread_num * thread_num + 1, data_total + 1)]
        [t.start() for t in _]
        [t.join() for t in _]

    logger.info('packing: {}'.format(archive_path))
    run(compress_args + [archive_path, alldata_path])
