cython:
	export CFLAGS='-I$(shell python3 -c "import numpy;print(numpy.get_include())")' && python3 setup.py build_ext --inplace
	if [ -d "build" ]; then rm -Rf build; fi
	rm games/meangame.cpp

pytest:
	python3 -m pytest -q ./games/test/

cpptest:
	g++ -o test.out ./games/cpp/tests.cpp ./games/cpp/utilities.cpp ./games/cpp/games.cpp && ./test.out
	rm test.out
