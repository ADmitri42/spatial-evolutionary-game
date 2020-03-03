# spatial-evolutionary-game

In this game L<sup>2</sup> individual "*players*" placed in two-dimensional spatial array.

Every individual can play one of two tactics: cooperate or defect. At the begining of the "games" each player has probability of being assigned **C** with probability **p<sub>c</sub>** and tactics **D** in other way.

In each round individuals "*play the game*" with 8 its neighbours and the *average cooperator*.

After all games played the site occupied either by its original owner or by one of the neighbours who scores the highest total payoff in that round.

## Where is what?
Let's take a quick look at files:

* [spatial evolutionary game.ipynb](spatial%20evolutionary%20game.ipynb) - The main notebook where one can find all main information
* [draft.ipynb](draft.ipynb) - used for experiments and testing
* [Animation.ipynb](Animation.ipynb) - animations
* [figures\\](figures) - Graphs and other images
- [data\\](data) - Folder with all generated data

- [games\\](games) - Folder with C++ and Cython realization of the game
- [games\\cpp](games\cpp) - Folder with C++ code
- [games\\test](games\test) - Folder with tests(uses pytest)

## How to setup
To compile Cython file
```bash
make
```
To test MeanGame
```bash
make pytest
```

### C++
To compile C++ version you need to install [cnpy](https://github.com/rogersce/cnpy) and [generate fields](spatial evolutionary game.ipynb)

After installation you can compile it
```bash
make cpp
```
