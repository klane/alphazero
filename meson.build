project('alphazero', 'cpp', version: '0.1.0', default_options: ['cpp_std=c++11'])

cpp_deps = [
    dependency('boost-headers', method: 'pkg-config'),
    dependency('eigen3', method: 'pkg-config'),
]

python = import('python').find_installation('python3')
python_deps = [
    python.dependency(),
    dependency('pybind11', method: 'pkg-config'),
]

board = library(
    'board',
    'src/cpp/board.cpp',
    dependencies: cpp_deps,
)

python.extension_module(
    'alphazero_cpp',
    'src/cpp/bindings.cpp',
    dependencies: cpp_deps + python_deps,
    link_with: board,
    install: true,
)

subdir('src/python')
