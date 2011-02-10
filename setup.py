#!/usr/bin/env/python
"""
Setup script for yaposib
"""
from setuptools import setup, Extension, find_packages
import ConfigParser
import platform
import os
import shutil

Description = """
Documentation can be found at https://code.google.code/p/yaposib/

Exported Classes:
    Problem, YaposibVectorError

Exported Functions:
    vec, test, available_solvers
"""
License = """
Copyright (c) 2010-2011, Christophe-Marie Duquesne <chm.duquesne@gmail.com>

This code is provided under the terms of the Eclipse Public License. A
copy of this license can be found at http://www.eclipse.org/legal/epl-v10.html
and in the file COPYING.
"""

SOLVERS = [ "Cbc", "Clp", "Cpx", "Dylp", "Fmp", "Glpk", "Grb", "Msk",
            "Osl", "Spx", "Sym", "Vol", "Xpr"]

config = ConfigParser.RawConfigParser()
config.read("build.conf")

# If we just want to build the egg with the embedded libraries, we
# override the config
if config.get("Global", "use_prebuilt_osi") == "true":
    # We replace __init__.py in yaposib with a different __init__.py that
    # preloads the necessary embedded libs.
    shutil.copy(
            os.path.join("yaposib", "init_preload"),
            os.path.join("yaposib", "__init__.py")
            )
    # We read the right build config
    if platform.system() == "Linux":
        if platform.uname()[4] == "x86_64":
            config.read("build_x86_64.conf")
        else:
            config.read("build_i686.conf")

embedded_solvers = [ solver for solver in SOLVERS
        if config.get(solver, "enabled") == "true" ]

# libraries we compile yaposib for
solver_libs = []
for solver in embedded_solvers:
    solver_libs += config.get(solver, "libraries").split(" ")

yaposib_shared_lib = Extension("_yaposib",
        define_macros = [(solver, None) for solver in embedded_solvers if
            config.get(solver, "libraries")],
        sources = [
            "cpp/CArrays.cpp",
            "cpp/Col.cpp",
            "cpp/Row.cpp",
            "cpp/Obj.cpp",
            "cpp/Problem.cpp",
            "cpp/Binding.cpp"
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

package_data = [ "yaposib/embedded_libs/i686/*",
        "yaposib/embedded_libs/x86_64/*", "AUTHORS", "COPYING" ]

setup(name="yaposib",
      version="0.2.2",
      description="""
      Yaposib is a python binding to OSI, the Open Solver Interface from
      COIN-OR. It intends to give access to various solvers through
      python. Yaposib was created in order to be integrated in pulp-or
      (http://code.google.com/p/pulp-or).
      """,
      long_description = Description,
      license = License,
      keywords = ["Optimization", "Linear Programming",
          "Operations Research"],
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
      ext_modules = [ yaposib_shared_lib ],
      test_suite = "yaposib.test_suite",
      package_data = { "" : package_data },
      eager_resources = package_data
      )
