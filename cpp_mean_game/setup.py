from distutils.core import setup
from Cython.Build import cythonize
import numpy as np


# OPT = -DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes
setup(ext_modules = cythonize(
           ["meangame.pyx", "evolve.cc"],                 # our Cython source
           include_path = [np.get_include(),],
           language="c++",             # generate C++ code
      ))
