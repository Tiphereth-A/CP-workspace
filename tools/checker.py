#!/usr/bin/python3
# -*- coding: utf-8 -*-

import os
import secrets
import subprocess
import click
import coloredlogs

from libs.decorator import withlog
from libs.common import compile_cpp, generate_data_in, generate_data_out, wipe_folder


@click.group()
@click.option('-l', '--level', type=click.Choice(['CRITICAL', 'ERROR', 'WARNING', 'INFO', 'DEBUG']), help='log level',
              default='INFO')
def cli(level: str):
    coloredlogs.install(level=level,
                        fmt='%(asctime)s:%(msecs)03d %(levelname)s %(programname)s::%(name)s [%(process)d] %(message)s',
                        field_styles={'asctime': {'color': 'green'},
                                      'msecs': {'color': 'green'},
                                      'hostname': {'color': 'red'},
                                      'levelname': {'bold': True, 'color': 'magenta'},
                                      'name': {'faint': True, 'color': 'blue'},
                                      'programname': {'bold': True, 'color': 'cyan'},
                                      'process': {'faint': True, 'color': 'green'},
                                      'username': {'color': 'yellow'}},
                        level_styles={'critical': {'bold': True, 'color': 'red'},
                                      'debug': {'color': 'cyan'},
                                      'error': {'color': 'red'},
                                      'info': {'bright': True, 'color': 'white'},
                                      'notice': {'color': 'magenta'},
                                      'spam': {'color': 'green', 'faint': True},
                                      'success': {'bold': True, 'color': 'green'},
                                      'verbose': {'color': 'blue'},
                                      'warning': {'bright': True, 'color': 'yellow'}})


DEFAULT_TESTCASE_COUNT = 5000
DEFAULT_TIME_LIMIT = 2.0
DEFAULT_CPP_COMPILE_ARGS = '-std=c++17 -O2 -D_CLI_ -DONLINE_JUDGE'
DEFAULT_TESTLIB_DIR = os.path.join('..', 'lib', 'testlib')
DEFAULT_GEN = os.path.join('src', 'gen.cpp')
DEFAULT_STD = os.path.join('src', 'std.cpp')
DEFAULT_MY = os.path.join('src', 'my.cpp')
DEFAULT_JUDGER = os.path.join(DEFAULT_TESTLIB_DIR, 'checkers', 'lcmp.cpp')
DEFAULT_OUT_DIR = 'out'


@cli.command('judge')
@click.option('-n', '--num', type=int, default=DEFAULT_TESTCASE_COUNT, help=f"Number of testcases, default {DEFAULT_TESTCASE_COUNT}")
@click.option('-t', '--time-limit', type=float, default=DEFAULT_TIME_LIMIT, help=f"Time limit (s), default {DEFAULT_TIME_LIMIT}")
@click.option('-c', '--compile-args', type=str, default=DEFAULT_CPP_COMPILE_ARGS, help=f"C++ compile arguments, default '{DEFAULT_CPP_COMPILE_ARGS}'")
@click.option('-l', '--testlib-repo-dir', type=click.Path(exists=True, file_okay=False), default=DEFAULT_TESTLIB_DIR, help=f'testlib repo dir, default {DEFAULT_TESTLIB_DIR}')
@click.option('-g', '--gen-file', type=click.Path(exists=True, dir_okay=False), default=DEFAULT_GEN, help=f"Generator source file (C++), default {DEFAULT_GEN}")
@click.option('-s', '--std-file', type=click.Path(exists=True, dir_okay=False), default=DEFAULT_STD, help=f"Standard source file (C++), default {DEFAULT_STD}")
@click.option('-m', '--my-file', type=click.Path(exists=True, dir_okay=False), default=DEFAULT_MY, help=f"My source file (C++), default {DEFAULT_MY}")
@click.option('-j', '--judger-file', type=click.Path(exists=True, dir_okay=False), default=DEFAULT_JUDGER, help=f"Judger source file (C++), default {DEFAULT_JUDGER}")
@click.option('-o', '--out-dir', type=click.Path(exists=True, file_okay=False), default=DEFAULT_OUT_DIR, help=f"testlib repo dir, default {DEFAULT_OUT_DIR}")
def _judge(num: int, time_limit: float, compile_args: str, testlib_repo_dir, gen_file, std_file, my_file, judger_file, out_dir):
    """Simple dynamic local checker with data generator and standard source file

    Usage of generator should be like:
        generator <seed> <data-id>

    Usage of judger should be like:
        judger <input-file> <output-file> <answer-file>
    """

    @withlog
    def judge(_num: int, _time_limit_s: float, _compile_args: str, _testlib_repo_dir: str, _gen_file: str, _std_file: str, _my_file: str, _judger_file: str, _out_dir: str, **kwargs):
        _data_dir: str = os.path.join(_out_dir, 'data')

        wipe_folder(_out_dir)
        os.makedirs(_data_dir)

        _judger_bin: str = compile_cpp(_judger_file, _out_dir,
                                       _compile_args.split()+['-I', _testlib_repo_dir])[1]
        _gen_bin: str = compile_cpp(_gen_file, _out_dir, _compile_args.split() +
                                    ['-I', _testlib_repo_dir])[1]
        _std_bin: str = compile_cpp(_std_file, _out_dir, _compile_args.split() +
                                    ['-I', _testlib_repo_dir])[1]
        _my_bin: str = compile_cpp(_my_file, _out_dir, _compile_args.split() +
                                   ['-I', _testlib_repo_dir])[1]

        def _single_run(_id: int, _gen_prog: str, _std_prog: str, _my_prog: str, _judger_prog: str):
            kwargs.get('logger').info(f'Test #{_id}')

            data_in = generate_data_in(_id, secrets.randbits(64), _gen_prog)
            data_ans = generate_data_out(
                _std_prog, data_in.stdout, _time_limit_s)
            data_out = generate_data_out(
                _my_prog, data_in.stdout, _time_limit_s)

            kwargs.get('logger').debug('Saving results')
            open(os.path.join(_data_dir, 'in.in'), 'wb').write(data_in.stdout)
            open(os.path.join(_data_dir, 'out.out'),
                 'wb').write(data_out.stdout)
            open(os.path.join(_data_dir, 'ans.out'),
                 'wb').write(data_ans.stdout)

            kwargs.get('logger').debug('Checking')
            return subprocess.run([_judger_prog, os.path.join(_data_dir, 'in.in'), os.path.join(_data_dir, 'out.out'), os.path.join(_data_dir, 'ans.out')], shell=False, check=True)

        for i in range(_num):
            try:
                _single_run(i, _gen_bin, _std_bin, _my_bin, _judger_bin)
            except Exception as e:
                kwargs.get('logger').error(
                    f'Test #{i} failed with exception {e}')
                raise e

    judge(num, time_limit, compile_args, click.format_filename(testlib_repo_dir), click.format_filename(gen_file), click.format_filename(
        std_file), click.format_filename(my_file), click.format_filename(judger_file), click.format_filename(out_dir))


if __name__ == '__main__':
    cli()
