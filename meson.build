project(
    'alphazero',
    'cpp',
    version: '0.1.0',
    default_options: [
        'cpp_std=c++11',
        'default_library=static',
        'python.install_env=venv',
    ],
)

python = import('python').find_installation('python3')

subdir('engines/cpp')
