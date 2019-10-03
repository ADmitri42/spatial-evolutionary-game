# spatial-evolutionary-game

In this game L<sup>2</sup> individual "*players*" placed in two-dimensional spatial array.

Every individual can play one of two tactics: cooperate or defect. At the begining of the "games" each player has probability of being assigned $\mathcal{C}$ with probability $p_c$ and tactics $\mathcal{D}$ in other way.

In each round individuals "*play the game*" with 8 its neighbours and the *average cooperator*.

After all games played the site occupied either by its original owner or by one of the neighbours who scores the highest total payoff in that round.


## To-Do

- [] Check if density of cooperators depends on initial density
- [] Look at cooperator surrounded by defectors
- [] Rewrite game in C++