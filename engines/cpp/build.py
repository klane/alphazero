from pathlib import Path
from typing import Any

import mesonpy
from conan.api.conan_api import ConanAPI
from conan.cli.cli import Cli as ConanCLI
from conans.errors import ConanException


def _download_conan_packages(config_settings: dict[str, Any]) -> None:
    source_dir = Path(__file__).parent
    conan_package_dir = config_settings.pop('package-dir', 'packages')
    meson_native_file = source_dir / conan_package_dir / 'conan_meson_native.ini'

    conan_api = ConanAPI()
    conan_cli = ConanCLI(conan_api)

    try:
        conan_cli.run(('profile', 'detect'))
    except ConanException:
        # profile already exists
        pass

    install_args = (
        'install',
        str(source_dir),
        f'--output-folder={conan_package_dir}',
        '--build=missing',
    )
    conan_cli.run(install_args)

    setup_args_key = 'setup-args'
    setup_args = config_settings.get(setup_args_key, [])
    setup_args.append(f'--native-file={meson_native_file}')
    config_settings[setup_args_key] = setup_args


def build_sdist(
    sdist_directory: str, config_settings: dict[str, Any] | None = None
) -> str:
    config_settings = {} if config_settings is None else config_settings
    _download_conan_packages(config_settings)
    return mesonpy.build_sdist(sdist_directory, config_settings)


def build_wheel(
    wheel_directory: str,
    config_settings: dict[str, Any] | None = None,
    metadata_directory: str | None = None,
) -> str:
    config_settings = {} if config_settings is None else config_settings
    _download_conan_packages(config_settings)
    return mesonpy.build_wheel(wheel_directory, config_settings, metadata_directory)
