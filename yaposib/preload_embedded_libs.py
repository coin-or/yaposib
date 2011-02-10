import platform
import os
import ctypes

path = None
lib_dir = None
TO_PRELOAD = None

if __name__ != "__main__":
    # if we run as a lib
    path = os.path.dirname(__file__)
else:
    # if we run as main
    path = ""

if platform.system() == "Linux":
    if platform.uname()[4] == "x86_64":
        lib_dir = os.path.join(path, "embedded_libs", "x86_64")
        TO_PRELOAD = [
        "libblas.so",
        "liblapack.so",
        "libCoinUtils.so",
        "libOsi.so",
        "libClp.so",
        "libOsiClp.so",
                ]
    else:
        lib_dir = os.path.join(path, "embedded_libs", "i686")
        TO_PRELOAD = [
        "libblas.so",
        "liblapack.so",
        "libCoinUtils.so",
        "libOsi.so",
        "libClp.so",
        "libOsiClp.so",
                ]

for lib in TO_PRELOAD:
    lib_path = os.path.join(lib_dir, lib)
    ctypes.CDLL(lib_path, mode = ctypes.RTLD_GLOBAL)

