import argparse
import os
from collections import Counter

import numpy as np
import spatgames
from tqdm import tqdm

from configurator import configure_workflow

# Configure workflow
parser = argparse.ArgumentParser(
    description="Collects data about persistence and saves it."
)
parser.add_argument(
    "config", metavar="config", type=str, help="JSON file with configuration"
)

parser.add_argument(
    "-y", dest="overwrite", action="store_true", help="If needed, answer yes"
)
parser.set_defaults(overwrite=False)

args = parser.parse_args()
config, path_to_results = configure_workflow(args.config, args.overwrite)

# Game setup
GamePy = getattr(spatgames, config["GameType"])

# Configuring some variables and game
if config["GameType"] == "DoubleMeanFieldGamePy":
    from itertools import product

    if type(config["parameters"]) == dict:
        bs = list(product(config["parameters"]["b1"], config["parameters"]["b2"]))
    else:
        bs = list(product(config["parameters"], config["parameters"]))
    persistence_shape = (len(bs), config["fields"]["quantity"], 2)
    density_shape = (
        len(bs),
        config["fields"]["quantity"],
        2,
        config["persistence"]["end"] + 1,
    )
    game = GamePy(
        config["fields"]["size"],
        1.3,
        1.3,
        config["persistence"]["start"],
        config["persistence"]["end"],
    )
else:
    bs = config["parameters"]
    persistence_shape = (len(bs), config["fields"]["quantity"])
    density_shape = (
        len(bs),
        config["fields"]["quantity"],
        config["persistence"]["end"] + 1,
    )
    game = GamePy(
        config["fields"]["size"],
        1.3,
        config["persistence"]["start"],
        config["persistence"]["end"],
    )

persistence = np.zeros(persistence_shape)
density = np.zeros(density_shape)

field_temp = os.path.join(
    config["fields"]["dir"], f"field_{config['fields']['size']}" + "_{0}.npy"
)

# Evolution
for i, b in tqdm(zip(range(len(bs)), bs), total=len(bs)):
    game.b = b
    for j in range(config["fields"]["quantity"]):
        game.field = np.load(field_temp.format(j))
        game.evolve(config["persistence"]["end"])
        persistence[i, j] = game.persistence
        density[i, j] = game.densities

# Fixing data
if config["GameType"] == "DoubleMeanFieldGamePy":
    if type(config["parameters"]) == dict:
        new_density = np.zeros(
            (
                len(config["parameters"]["b1"]),
                len(config["parameters"]["b2"]),
                config["fields"]["quantity"],
                2,
                config["persistence"]["end"] + 1,
            )
        )
        new_persistence = np.zeros(
            (
                len(config["parameters"]["b1"]),
                len(config["parameters"]["b2"]),
                config["fields"]["quantity"],
                2,
            )
        )
        indeces = product(
            range(len(config["parameters"]["b1"])),
            range(len(config["parameters"]["b2"])),
        )
    else:
        new_density = np.zeros(
            (
                len(config["parameters"]),
                len(config["parameters"]),
                config["fields"]["quantity"],
                config["persistence"]["end"] + 1,
                2,
            )
        )
        new_persistence = np.zeros(
            (
                len(config["parameters"]),
                len(config["parameters"]),
                config["fields"]["quantity"],
                2,
            )
        )
        indeces = product(
            range(len(config["parameters"])), range(len(config["parameters"]))
        )

    for k, (i, j) in enumerate(indeces):
        new_density[i, j] = density[k]
        new_persistence[i, j] = persistence[k]
    density = new_density
    persistence = new_persistence

np.save(os.path.join(path_to_results, "persistence.npy"), persistence)
np.save(os.path.join(path_to_results, "density.npy"), density)
