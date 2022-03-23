import os
import re
import secrets
import subprocess
from logging import Logger
from threading import Thread
from typing import List, AnyStr


def remove(logger: Logger, filepath: AnyStr):
    logger.info('removing: {}'.format(filepath))
    try:
        os.remove(filepath)
    except:
        logger.info('{} not found'.format(filepath))


def clear_folder(logger: Logger, folder: AnyStr):
    for filepath, dirnames, filenames in os.walk(standardized_folder(folder)):
        [remove(logger, os.path.join(filepath, filename)) for filename in filenames]


def standardized_folder(folder: AnyStr):
    return re.sub(r'\\+$', '', folder)


def make_folder_if_not_exist(folder: AnyStr):
    if not os.path.exists(standardized_folder(folder)):
        os.mkdir(standardized_folder(folder))


def compile_gpp(logger: Logger, source_file: AnyStr, execute_file: AnyStr,
                compile_args: List[AnyStr]) -> subprocess.CompletedProcess:
    logger.info('compiling: {}'.format(source_file))
    return subprocess.run(['g++', source_file, '-o', execute_file] + compile_args, shell=False, check=True)


def write_in_once(logger: Logger, file: AnyStr, info: bytes):
    logger.info('writing: {}'.format(file))
    open(file, mode='wb').write(info)


def write_input_output(logger: Logger, input_file: AnyStr, input_info: bytes, output_file: AnyStr,
                       output_info: bytes):
    write_in_once(logger, input_file, input_info)
    write_in_once(logger, output_file, output_info)


def write_input_output_answer(logger: Logger, input_file: AnyStr, input_info: bytes, output_file: AnyStr,
                              output_info: bytes, answer_file: AnyStr,
                              answer_info: bytes):
    write_input_output(logger, input_file, input_info, output_file, output_info)
    write_in_once(logger, answer_file, answer_info)


def generate_data(logger: Logger, generator_file: AnyStr, data_id) -> subprocess.CompletedProcess:
    # now_seed = secrets.randbits(25) # less than 1e8
    now_seed = secrets.randbits(32)
    logger.info('generating: data #{} with seed {}'.format(data_id, now_seed))

    return subprocess.run([generator_file, str(now_seed), str(data_id)], stdout=subprocess.PIPE, shell=False,
                          check=True)


def generate_single_dataset(logger: Logger, generator_file: AnyStr, standard_file: AnyStr, data_id,
                            in_path: AnyStr, out_path: AnyStr):
    din = generate_data(logger, generator_file=generator_file, data_id=data_id)
    dout = subprocess.run(standard_file, input=din.stdout, stdout=subprocess.PIPE, shell=False, check=True)

    write_input_output(logger=logger, input_file=in_path, input_info=din.stdout,
                       output_file=out_path, output_info=dout.stdout)
