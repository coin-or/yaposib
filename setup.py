#!/usr/bin/env/python
"""
Yaposib is a python binding to OSI, the Open Solver Interface from
COIN-OR. It intends to give access to various solvers through
python. Yaposib was created in order to be integrated in pulp-or
(http://code.google.com/p/pulp-or).
"""
from __future__ import with_statement
from setuptools import setup, Extension, find_packages
import ConfigParser
import platform
import os
import os.path
import shutil
import urllib2
import hashlib
from zipfile import ZipFile

def security_check(filename):
    known_hashes = ('a780bb709516a6fcc7abb05e719ed2a4d94d3bae',
            '54dbe692f5b23f834eb2f74dcf5c3a9927c566be',
            'f5de697e85134c42e5da00405827f7ebadadccd7')
    assert hashlib.sha1(open(filename).read()).hexdigest() in known_hashes

def download_prebuilt_osi():
    """Downloads and extracts a prebuilt OSI"""
    print("Downloading and extracting a prebuilt Osi, this may take time...")
    lib, include = "lib.zip", "include.zip"
    if not os.path.exists(lib): # don't re-download if already there
        if platform.system() == "Linux":
            if platform.uname()[4] == "x86_64":
                url = 'http://yaposib.googlecode.com/files/osi_x86_64.zip'
            else:
                url = 'http://yaposib.googlecode.com/files/osi_i686.zip'
        with open(lib, "wb") as f:
            f.write(urllib2.urlopen(url).read())
    if not os.path.exists(include): # don't re-download if already there
        url = 'http://yaposib.googlecode.com/files/osi_headers.zip'
        with open(include, "wb") as f:
            f.write(urllib2.urlopen(url).read())
    security_check(lib)
    security_check(include)
    ZipFile(lib, mode="r").extractall("yaposib/lib")
    ZipFile(include, mode="r").extractall()

def yaposib_extension():
    """Returns yaposib extension properly configured"""
    config = ConfigParser.RawConfigParser()
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
      version="0.2.74",
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
      packages = find_packages(),
      ext_modules = [ yaposib_extension() ],
      test_suite = "yaposib.test",
      eager_resources = [ "lib/*" ],
      package_data = { "" : [ "lib/*" ] },
      entry_points = ("""
      [console_scripts]
      yaposib = yaposib.test.test_yaposib:main
          """)
      )
