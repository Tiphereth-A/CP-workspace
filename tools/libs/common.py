import os
import shutil
import subprocess
from libs.decorator import withlog


@withlog
def wipe_folder(dir: str, **kwargs):
    kwargs.get('logger').info(f'Wipe dir {dir}')
    shutil.rmtree(dir)
    os.makedirs(dir)


@withlog
def compile_cpp(file: str, output_dir: str, compile_args: list[str], **kwargs) -> tuple[subprocess.CompletedProcess, str]:
    def compile_cpp_target(file: str, output_dir: str):
        return os.path.join(output_dir, os.path.splitext(os.path.basename(file))[0])

    target: str = compile_cpp_target(file, output_dir)
    kwargs.get('logger').info(f'Compiling {file} -> {target}')
    return (subprocess.run(['g++', file, '-o', target] + compile_args, check=True), target)


@withlog
def generate_data_in(data_id: int, seed: int, generator_name: str, **kwargs) -> subprocess.CompletedProcess:
    f"""Generate input data

    Example:
    ```python
    result = {__name__}(data_id, seed, generator_name)
    open('in.in', 'wb').write(result.stdout)  # storage result
    ```
    """

    kwargs.get('logger').debug(
        f'Generating input data #{data_id} with seed {seed}')
    return subprocess.run([generator_name, str(seed), str(data_id)], stdout=subprocess.PIPE, shell=False, check=True)


@withlog
def generate_data_out(program_name: str, input_pipe, timeout: float, **kwargs) -> subprocess.CompletedProcess:
    f"""Generate output data

    Example:
    ```python
    result = {__name__}(program_name, input_pipe, timeout)
    open('out.out', 'wb').write(result.stdout)  # storage result
    ```
    """

    kwargs.get('logger').debug(f'Generating output of {program_name}')
    return subprocess.run([program_name], input=input_pipe, stdout=subprocess.PIPE, shell=False, check=True, timeout=timeout)
