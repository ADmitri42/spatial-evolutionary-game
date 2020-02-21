cython:
	export CFLAGS='-I$(shell python3 -c "import numpy;print(numpy.get_include())")' && python3 setup.py build_ext --inplace
	if [ -d "build" ]; then rm -Rf build; fi
	rm cpp_mean_game/meangame.cpp

pytest:
	python3 -m pytest -q ./cpp_mean_game/test/

testcpp:
	g++ -o test.out cpp/tests.cpp cpp/utilities.cpp cpp/games.cpp cpp/abgame.cpp && ./test.out
	rm test.out
