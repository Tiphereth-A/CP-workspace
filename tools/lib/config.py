import re
from typing import List, Any

compile_args = ['-O3', '-std=c++17', '-D_LOCAL_', '-D_CLI_']  # type: List[str]
compile_args_chk_std = ['-O2', '-std=c++17']  # type: List[str]
compress_args = ['7z', 'a', '-tzip']  # type: List[str]

regex_space_in_the_end_bytes = re.compile(r'\s+$'.encode())  # type: re.Pattern[Any]
