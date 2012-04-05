#!/usr/bin/env/python
"""
Yaposib is a python binding to OSI, the Open Solver Interface from
COIN-OR. It intends to give access to various solvers through
python. Yaposib was created in order to be integrated in pulp-or
(http://code.google.com/p/pulp-or).
"""
from __future__ import with_statement
from distutils.core import setup, Extension

try:
    import ConfigParser as configparser
except ImportError:
    import configparser
import platform
import os
import os.path
import shutil
try:
    from urllib import urlopen
except ImportError:
    from urllib.request import urlopen
import hashlib
from functools import partial
from zipfile import ZipFile

def sha1_hash(path):
    """Returns the sha1 hash of the input file (works for python2/3)"""
    with open(path, mode='rb') as f:
        d = hashlib.sha1()
        for buf in iter(partial(f.read, 128), b''):
            d.update(buf)
    return d.hexdigest()

def download(url, path, sha1_sum):
    """downloads url to file, checking it for sha1_sum (works for python2/3)"""
    if os.path.exists(path):
        print("%s already on the system, skipping download." % path)
    else:
        print("Downloading %s to %s" % (url, path))
        remote = urlopen(url)
        with open(path, 'wb') as local:
            local.write(remote.read())
        remote.close()
        if sha1_sum:
            print("Checking %s for the given sha1_sum %s" % (path, sha1_sum))
            assert sha1_hash(path) == sha1_sum

def download_prebuilt_osi():
    """Downloads and extracts a prebuilt OSI"""
    # download the binary libs
    if platform.system() == "Linux":
        if platform.uname()[4] == "x86_64":
            download(
                    'http://yaposib.googlecode.com/files/osi_x86_64.zip',
                    'lib.zip',
                    '54dbe692f5b23f834eb2f74dcf5c3a9927c566be')
        else:
            download(
                    'http://yaposib.googlecode.com/files/osi_i686.zip',
                    'lib.zip',
                    'f5de697e85134c42e5da00405827f7ebadadccd7')
    # download the headers
    download(
            'http://yaposib.googlecode.com/files/osi_headers.zip',
            'include.zip',
            'a780bb709516a6fcc7abb05e719ed2a4d94d3bae')
    # unzip
    ZipFile('lib.zip', mode="r").extractall("yaposib/lib")
    ZipFile('include.zip', mode="r").extractall()

def yaposib_extension():
    """Returns yaposib extension properly configured"""
    config = configparser.RawConfigParser()
    config.read("build.conf")
    if config.get("Global", "use_prebuilt_osi") == "true":
        print("Building yaposib against a prebuilt OSI.")
        print("Modify build.conf if you want to use your own build.")
        download_prebuilt_osi()
        shutil.copy(
                os.path.join("yaposib", "init_preload"),
                os.path.join("yaposib", "__init__.py")
                )
    else:
        print("Building yaposib against your local OSI build.")
        shutil.copy(
                os.path.join("yaposib", "init_normal"),
                os.path.join("yaposib", "__init__.py")
                )
    embedded_solvers = [ solver for solver in
            [ "Cbc", "Clp", "Cpx", "Dylp", "Fmp", "Glpk", "Grb", "Msk",
                "Osl", "Spx", "Sym", "Vol", "Xpr"]
            if config.get(solver, "enabled") == "true" ]
    solver_libs = []
    for solver in embedded_solvers:
        solver_libs += config.get(solver, "libraries").split(" ")
    return Extension("yaposib._yaposib",
            define_macros = [(solver, None) for solver in embedded_solvers if
                config.get(solver, "libraries")] + [("PY_FORMAT_LONG_LONG",
                    "I64")], # python2.7 wants PY_FORMAT_LONG_LONG to be defined
            sources = [
                "yaposib/CArrays.cpp",
                "yaposib/Col.cpp",
                "yaposib/Row.cpp",
                "yaposib/Obj.cpp",
                "yaposib/Problem.cpp",
                "yaposib/Binding.cpp"
                ],
            include_dirs =
                  [ config.get("OSI",    "include_dir"),
                    config.get("python", "include_dir"),
                    config.get("boost",  "include_dir") ]
                + [ config.get(solver,   "include_dir")
                    for solver in embedded_solvers ],
            library_dirs =
                  [ config.get("OSI",    "library_dir"),
                    config.get("python", "library_dir"),
                    config.get("boost",  "library_dir") ]
                + [ config.get(solver,   "library_dir")
                    for solver in embedded_solvers ],
            libraries =
                  config.get("OSI",    "libraries").split(" ")
                + config.get("boost",  "libraries").split(" ")
                + config.get("python", "libraries").split(" ")
                + solver_libs
                + [ "Osi" + solver for solver in embedded_solvers ],
            language = 'c++'
            )

setup(name="yaposib",
      version="0.2.76",
      description= __doc__,
      long_description = open("README").read(),
      license = open("COPYING").read(),
      keywords = ["Optimization", "Linear Programming", "Operations Research"],
      author="Christophe-Marie Duquesne",
      author_email="chm.duquesne@gmail.com",
      url="https://code.google.code/p/yaposib/",
      classifiers = ["Development Status :: 3 - Alpha",
                     "Environment :: Console",
                     "Intended Audience :: Science/Research",
                     "License :: OSI Approved",
                     "Natural Language :: English",
                     "Topic :: Scientific/Engineering :: Mathematics",
      ],
      packages = ['yaposib', 'yaposib.test'] ,
      ext_modules = [ yaposib_extension() ],
      package_data = { "" : [ "lib/*" ] },
      scripts = [ "yaposib/test/test_yaposib.py" ]
      )
