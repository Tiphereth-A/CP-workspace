#!/usr/bin/env python3

# from ac-library

import argparse
import re
from logging import Logger, basicConfig, getLogger
from os import getenv, environ, pathsep
from pathlib import Path
from typing import List, Set

logger = getLogger(__name__)  # type: Logger


class Expander:
    lib_include = re.compile(r'#\s*include\s*"([a-z_/]*\.hpp)"\s*')

    include_guard = re.compile(r'#.*[A-Z_]*_HPP')

    def is_ignored_line(self, line) -> bool:
        if self.include_guard.match(line):
            return True
        if line.strip() == "#pragma once":
            return True
        if line.strip().startswith('//'):
            return True
        return False

    def __init__(self, lib_paths: List[Path]):
        self.lib_paths = lib_paths

    included = set()  # type: Set[Path]

    def find_lib(self, lib_name: str) -> Path:
        for lib_path in self.lib_paths:
            path = lib_path / lib_name
            if path.exists():
                return path
        logger.error('cannot find: {}'.format(lib_name))
        raise FileNotFoundError()

    def expand_lib(self, lib_file_path: Path) -> List[str]:
        if lib_file_path in self.included:
            logger.info('already included: {}'.format(lib_file_path.name))
            return []
        self.included.add(lib_file_path)
        logger.info('include: {}'.format(lib_file_path.name))

        lib_source = open(str(lib_file_path)).read()

        result = []  # type: List[str]
        for line in lib_source.splitlines():
            if self.is_ignored_line(line):
                continue

            m = self.lib_include.match(line)
            if m:
                name = m.group(1)
                result.extend(self.expand_lib(self.find_lib(name)))
                continue

            result.append(line)
        return result

    def expand(self, source: str) -> str:
        self.included = set()
        result = []  # type: List[str]
        for line in source.splitlines():
            m = self.lib_include.match(line)
            if m:
                lib_path = self.find_lib(m.group(1))
                result.extend(self.expand_lib(lib_path))
                continue

            result.append(line)
        return '\n'.join(result)


if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv('LOG_LEVEL', 'INFO'),
    )
    parser = argparse.ArgumentParser(description='Library expander')
    parser.add_argument('source', help='C++ source File')
    parser.add_argument('-c', '--console',
                        action='store_true', help='Print to Console')
    parser.add_argument('--lib', help='Path to Library')
    opts = parser.parse_args()

    lib_paths = []
    if opts.lib:
        lib_paths.append(Path(opts.lib))
    if 'CPLUS_INCLUDE_PATH' in environ:
        lib_paths.extend(
            map(Path, filter(None, environ['CPLUS_INCLUDE_PATH'].split(pathsep))))
    lib_paths.append(Path.cwd())
    expander = Expander(lib_paths)
    source = open(opts.source).read()
    output = expander.expand(source)

    if opts.console:
        print(output)
    else:
        with open('out\expanded_l_' + opts.source, 'w') as f:
            f.write(output)
