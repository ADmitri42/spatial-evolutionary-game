# spatial-evolutionary-game

In this game L<sup>2</sup> individual "*players*" placed in two-dimensional spatial array.

Every individual can play one of two tactics: cooperate or defect. At the begining of the "games" each player has probability of being assigned $\mathcal{C}$ with probability $p_c$ and tactics $\mathcal{D}$ in other way.

In each round individuals "*play the game*" with 8 its neighbours and the *average cooperator*.

After all games played the site occupied either by its original owner or by one of the neighbours who scores the highest total payoff in that round.

## Where is what?
Let's take a quick look at filуs:

* [spatial evolutionary game.ipynb](spatial%20evolutionary%20game.ipynb) - The main notebook where one can find all main information
* [draft.ipynb](draft.ipynb) - used for experiments and testing
* [Animation.ipynb](Animation.ipynb) - animations
* [figures\\](figures) - Graphs and other images
- [data\\](data) - Folder with all generated data
- [data\\density_of_cooperators.npy](data\density_of_cooperators.npy) - densities of cooperators with initial densities of 0.9
- [data\\density_of_cooperators.npy](data\density_of_cooperators15-17.npy) - same but b between 1.5 and 1.7
- [data\\density_of_cooperators.npy](data\density_of_cooperators5.npy) - densities of cooperators with initial densities of 0.5
- [data\\density_of_cooperators.npy](data\density_of_cooperators515-17.npy) - same but b between 1.5 and 1.7

* [cpp_mean_game\\](cpp_mean_game) - Folder with C++ and Cython realization of the game

## How to setup
To use whole speed of C++ and Cython one have to compile code with -O3 optimization.
### Cython
```bash
OPT="-DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes" python3 setup.py build_ext
```
If you get error like
```bash
meangame.cpp:613:10: fatal error: numpy/arrayobject.h: No such file or directory
 #include "numpy/arrayobject.h"
          ^~~~~~~~~~~~~~~~~~~~~
compilation terminated.
```
Then try to execute this line first
```bash
export CFLAGS='-I~/.local/lib/python3.6/site-packages/numpy/core/include'
```
Note that it can be different in your system

### C++
To compile C++ version you need to install [cnpy](https://github.com/rogersce/cnpy) and [generate fields](spatial evolutionary game.ipynb)

After installation you can compile it
```bash
g++ -o build/computedens.out main.cpp -L/usr/local/lib evolve.cc -lcnpy -lz -O3 --std=c++11
export LD_LIBRARY_PATH=/usr/local/lib/
```
