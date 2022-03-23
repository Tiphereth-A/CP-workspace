#!/usr/bin/env python3

import argparse
import re
import subprocess
from logging import Logger, basicConfig, getLogger
from os import getenv
from typing import List

logger = getLogger(__name__)  # type: Logger

if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv('LOG_LEVEL', 'INFO'),
    )
    parser = argparse.ArgumentParser(description='Macro expander')
    parser.add_argument('source', help='C++ source file')
    opts = parser.parse_args()

    input_filename = opts.source
    output_filename = 'out\expanded_m_' + input_filename

    re_spilt = r'# \d+ \"' + (input_filename.split('\\')[-1] if '\\' in input_filename else input_filename) + r'\".*?\n'

    logger.info('preprocessing: {}'.format(input_filename))

    gppe = subprocess.run(['g++', input_filename, '-E', '-I', '.'], stdout=subprocess.PIPE, shell=False, check=True)

    logger.info('cleaning')
    psource_slice = re.split(re_spilt, gppe.stdout.decode())

    result = []  # type: List[str]
    source = open(input_filename).readlines()
    for line in source:
        if line.find('#include') == 0:
            result.append(line)
    result = list(set(result))

    for now_part in psource_slice:
        if now_part.find('#') != -1:
            continue
        for line in now_part.splitlines():
            result.append(line)

    open(output_filename, 'w').write('\n'.join(result))
