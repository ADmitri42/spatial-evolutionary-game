# spatial-evolutionary-game

In this game L<sup>2</sup> individual "*players*" placed in two-dimensional spatial array.

Every individual can play one of two tactics: cooperate or defect. At the begining of the "games" each player has probability of being assigned **C** with probability **p<sub>c</sub>** and tactics **D** in other way.

In each round individuals "*play the game*" with 8 its neighbours and the *average cooperator*.

After all games played the site occupied either by its original owner or by one of the neighbours who scores the highest total payoff in that round.

## Where is what?
Let's take a quick tour into repo:
### Notebooks
- [2DMeanGame.ipynb](2DMeanGame.ipynb) - Notebook with all graphs and some data for 2D Mean game
- [1Dgame.ipynb](1Dgame.ipynb) - There we looking into 1D case
- [notebooks\\](notebooks) - Folder with some old notebooks
### Scripts
- [densityandpersistence.py](densityandpersistence.py) - script to calculate density and persistence of the games
- [nmandclusteranaly.py](nmandclusteranaly.py) - script used to calculate NM-distribution and sizes of clusters
- [scripts\\](scripts) - some useful script to render animation and fields images
### Everything else
- [figures\\](figures) - Graphs and other images
- [games\\](games) - Folder with C++ and Cython realization of the game
- [games\\cpp](games\cpp) - Folder with C++ code
- [games\\test](games\test) - Folder with tests(uses pytest)
### What about data?
You can download data [here](https://www.dropbox.com/s/wl29ihi0mmh0t4d/data.tar.gz?dl=0)

## How to setup
To compile Cython file
```bash
make
```
To test Games
```bash
make pytest
```

## How to use it?
```bash
densityandpersistence.py config.json
```

Example of `config.json`

[More](basic_setup.json)
```json
{
  "GameType": "NovakMayTriangularGamePy",
  "parameters": [0.9, 1.25423729, 1.53389831, 1.81355932, 2.0],
  "steps": {
    "drop": 10000,
    "measure": 10
  },
  "results": {
    "dir": "./data",
    "name": "NovakMayTriangle"
  },
  "fields": {
    "size": 200,
    "dir": "./fields",
    "quantity": 40
  },
  "persistence": {
    "start": 15000,
    "end": 16000
  }
}
```

`nmandclusteranaly.py` works only with square games