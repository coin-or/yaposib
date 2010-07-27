#!/usr/bin/env/python
"""
Setup script for yaposib
"""
#from distutils.core import setup
from setuptools import setup, find_packages

Description = """
A comprehensive wiki can be found at https://code.google.code/p/yaposib/

Exported Classes:

Exported Functions:
"""
License = """
Copyright (c) 20010, Christophe-Marie Duquesne <chm.duquesne@gmail.com>
"""

setup(name="yaposib",
      version="0.1",
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
      classifiers = ['Development Status :: 3 - Alpha',
                     'Environment :: Console',
                     'Intended Audience :: Science/Research',
                     'License :: OSI Approved :: EPL License',
                     'Natural Language :: English',
                     'Programming Language :: Python',
                     'Topic :: Scientific/Engineering :: Mathematics',
      ],
      packages = ['yaposib'],
      package_dir={'yaposib':'src'},
      package_data = {'yaposib' : ["AUTHORS","LICENSE","_yaposib.so",
          "yaposib.py" ]})
