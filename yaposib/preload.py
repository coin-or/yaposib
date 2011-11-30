import platform
import os
import ctypes
from pkg_resources import resource_filename

def preload():
    if platform.system() == "Linux":
        if platform.uname()[4] == "x86_64":
            to_preload = [
            #"libboost_python-py26.so.1.42.0",
            "libgfortran.so.3.0.0",
            "libblas.so.3gf",
            "liblapack.so.3gf.0",
            "libCoinUtils.so.0.0.0",
            "libOsi.so.0.0.0",
            "libClp.so.0.0.0",
            "libOsiClp.so.0.0.0",
                    ]
        else:
            to_preload = [
            #"libboost_python-py26.so.1.42.0",
            "libgfortran.so.3.0.0",
            "libblas.so.3.2.1",
            "liblapack.so.3.2.1",
            "libCoinUtils.so.0.0.0",
            "libOsi.so.0.0.0",
            "libClp.so.0.0.0",
            "libOsiClp.so.0.0.0",
                    ]
    for lib in to_preload:
        lib_path = resource_filename(__name__, os.path.join("lib", lib))
        ctypes.CDLL(lib_path, mode = ctypes.RTLD_GLOBAL)

preload()
