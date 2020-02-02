cython:
	export CFLAGS='-I/home/admitri/.local/lib/python3.6/site-packages/numpy/core/include' && python3 setup.py build_ext --inplace
	if [ -d "build" ]; then rm -Rf build; fi
optcython:
	export CFLAGS='-I/home/admitri/.local/lib/python3.6/site-packages/numpy/core/include' && OPT="-DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes" python3 setup.py build_ext --inplace
	if [ -d "build" ]; then rm -Rf build; fi
pytest:
	python3 -m pytest -q ./cpp_mean_game/test/

testcpp:
	g++ -o test.out cpp/tests.cpp cpp/utilities.cpp cpp/evolve.cc && ./test.out
	rm test.out
