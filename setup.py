#!/usr/bin/env/python
"""
Yaposib is a python binding to OSI, the Open Solver Interface from
COIN-OR. It intends to give access to various solvers through
python. Yaposib was created in order to be integrated in pulp-or
(http://code.google.com/p/pulp-or).
"""
from __future__ import with_statement
from setuptools import setup, Extension
import subprocess
import sys
from os.path import join

def pkgconfig(*packages, **kw):
    """Finds a package using pkg-config"""
    flag_map = {'-I': 'include_dirs', '-L': 'library_dirs', '-l': 'libraries'}
    for token in subprocess.check_output("pkg-config --libs --cflags %s" % ' '.join(packages), shell=True).split():
        kw.setdefault(flag_map.get(token[:2]), []).append(token[2:])
    return kw

def yaposib_extension():
    """Returns yaposib extension properly configured"""
    solvers = {
            "Cbc": "osi-cbc",
            "Clp": "osi-clp",
            "Cpx": "osi-cplex",
            "Dylp": "osi-dylp",
            "Fmp": "osi-fortmp",
            "Glpk": "osi-glpk",
            "Grb": "osi-gurobi",
            "Msk": "osi-mosek",
            "Osl": "osi-osl",
            "Spx": "osi-soplex",
            "Sym": "osi-sym",
            "Vol": "osi-vol",
            "Xpr": "osi-xpress"
            }
    kw = {
            # python2.7 wants PY_FORMAT_LONG_LONG to be defined
            "define_macros": [("PY_FORMAT_LONG_LONG", "I64")],
            "include_dirs": [],
            "library_dirs": [],
            # TODO: find a way to detect boost_python
            "libraries": [ "boost_python" ]
            }

    # Required stuff. We fail if we miss that.
    for lib in ('python', 'osi'):
        try:
            pc = pkgconfig(lib)
            kw["include_dirs"] += pc.get("include_dirs", [])
            kw["library_dirs"] += pc.get("library_dirs", [])
            kw["libraries"] += pc.get("libraries", [])
        except subprocess.CalledProcessError:
            sys.exit(1)

    # Optional stuff.
    for solvername, lib in solvers.items():
        try:
            pc = pkgconfig(lib)
            kw["include_dirs"] += pc.get("include_dirs", [])
            kw["library_dirs"] += pc.get("library_dirs", [])
            kw["libraries"] += pc.get("libraries", [])
            kw["define_macros"] += [ (solvername, None) ]
        except subprocess.CalledProcessError:
            pass

    files = [ "CArrays.cpp",
              "Col.cpp",
              "Row.cpp",
              "Obj.cpp",
              "Problem.cpp",
              "Binding.cpp",
            ]
    sources = [join('src/yaposib', f) for f in files]
    return Extension("_yaposib",
                     sources = sources,
                     language = 'c++',
                     **kw
                    )

setup(name="yaposib",
      version="0.4.0",
      description= __doc__,
      long_description = open("README.md").read(),
      license = open("COPYING").read(),
      keywords = ["Optimization", "Linear Programming", "Operations Research"],
      author="Christophe-Marie Duquesne",
      author_email="chmd@chmd.fr",
      url="https://code.google.code/p/yaposib/",
      classifiers = ["Development Status :: 3 - Alpha",
                     "Environment :: Console",
                     "Intended Audience :: Science/Research",
                     "License :: OSI Approved",
                     "Natural Language :: English",
                     "Topic :: Scientific/Engineering :: Mathematics",
      ],
      ext_modules = [ yaposib_extension() ],
      package_data = { "" : [ "lib/*" ] },
      packages=['coinor.yaposib', 'coinor.yaposib.test', 'coinor'],
      package_dir = {'coinor': 'src'},
      scripts = [ "scripts/yaposib-config", "scripts/yaposib-solve" ]
      )
