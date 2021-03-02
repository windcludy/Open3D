import pathlib
import sys

if sys.version_info < (3, 6):
    raise RuntimeError(
        "Python version must be >= 3.6, however, Python {}.{} is used.".format(
            sys.version_info[0], sys.version_info[1]))

test_dia_dir = pathlib.Path(__file__).parent.absolute().resolve()
open3d_downloads_dir = test_dia_dir / "open3d_downloads"


def hello():
    print(f"{open3d_downloads_dir}")


if __name__ == "__main__":
    hello()
    pass
