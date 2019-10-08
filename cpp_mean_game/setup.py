from distutils.core import setup
from Cython.Build import cythonize
from distutils.extension import Extension
from Cython.Distutils import build_ext
import numpy as np

# OPT="-DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes" python3 setup.py build_ext
# export CFLAGS='-I/home/admitri/.local/lib/python3.6/site-packages/numpy/core/include'

# setup(ext_modules = cythonize(
#            ["meangame.pyx", "evolve.cc"],                 # our Cython source
#            include_path = [np.get_include(),],
#            language="c++",             # generate C++ code
#       ))

setup(ext_modules=[Extension("meangame",
                             ["meangame.pyx", "evolve.cc"],
                             language="c++",
                             include_path = [np.get_include(),])],
      cmdclass = {'build_ext': build_ext})