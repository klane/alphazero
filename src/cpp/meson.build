cpp_deps = [
    dependency('boost-headers', method: 'pkg-config'),
    dependency('eigen3', method: 'pkg-config'),
]

python_deps = [
    python.dependency(),
    dependency('pybind11', method: 'pkg-config'),
]

board = library(
    'board',
    'board.cpp',
    dependencies: cpp_deps,
)

python.extension_module(
    'engine',
    'bindings.cpp',
    dependencies: cpp_deps + python_deps,
    link_with: board,
    subdir: 'alphazero',
    install: true,
)
