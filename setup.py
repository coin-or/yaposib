#!/usr/bin/env/python
"""
Setup script for yaposib
"""
from setuptools import setup, Extension, find_packages
import sys
import ConfigParser

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

config = ConfigParser.RawConfigParser()
config.read("build.conf")

ENABLED_SOLVERS = [ solver for solver in
        ["Cbc", "Clp", "Cpx", "Dylp", "Fmp", "Glpk", "Grb", "Msk", "Osl",
        "Spx", "Sym", "Vol", "Xpr"] if config.get(solver, "enabled") == "true" ]

SOLVER_LIBRARIES = []
for solver in ENABLED_SOLVERS:
    SOLVER_LIBRARIES += config.get(solver, "libraries").split(" ")

PYTHON_LIBRARY = [ "python" + str(sys.version_info[0]) + "." +
        str(sys.version_info[1]) ]

yaposib_shared_lib = Extension("_yaposib",
        define_macros = [(solver, None) for solver in ENABLED_SOLVERS if
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
                for solver in ENABLED_SOLVERS ],
        library_dirs =
              [ config.get("OSI",    "library_dir"),
                config.get("python", "library_dir"),
                config.get("boost",  "library_dir") ]
            + [ config.get(solver,   "library_dir")
                for solver in ENABLED_SOLVERS ],
        libraries =
              config.get("OSI",    "libraries").split(" ")
            + config.get("boost",  "libraries").split(" ")
            + PYTHON_LIBRARY
            + SOLVER_LIBRARIES
            + [ "Osi" + solver for solver in ENABLED_SOLVERS ],
        language = 'c++'
        )

setup(name="yaposib",
      version="0.2",
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
                     "License :: OSI Approved :: EPL License",
                     "Natural Language :: English",
                     "Topic :: Scientific/Engineering :: Mathematics",
      ],
      packages = find_packages(),
      ext_modules = [ yaposib_shared_lib ],
      test_suite = "yaposib.test_suite"
      )
