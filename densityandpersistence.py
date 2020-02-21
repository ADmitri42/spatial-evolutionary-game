import os
import argparse
from collections import Counter

import numpy as np
from tqdm import tqdm

from spatgames import MeanGamePy
from configurator import configure_workflow

parser = argparse.ArgumentParser(description='Collects data about persistence and saves it.')
parser.add_argument('config', metavar='config', type=str,
                    help='JSON file with configuration')

parser.add_argument('-y', dest='overwrite', action='store_true', help="If needed, answer yes")
parser.set_defaults(overwrite=False)

args = parser.parse_args()
config, path_to_results = configure_workflow(args.config, args.overwrite)


game = MeanGamePy(config["fields"]["size"], 1.3, config["persistence"]["start"], config["persistence"]["end"])

persistence = np.zeros((len(config["parameters"]), config["fields"]["quantity"]))
density = np.zeros((len(config["parameters"]), config["fields"]["quantity"], config["persistence"]["end"] + 1))

field_temp = os.path.join(config["fields"]["dir"], f"field_{config['fields']['size']}" + "_{0}.npy")

for i, b in tqdm(zip(range(len(config["parameters"])), config["parameters"]), total=len(config["parameters"])):
    game.b = b
    for j in range(config["fields"]["quantity"]):
        game.field = np.load(field_temp.format(j))
        game.evolve(config["persistence"]["end"])
        persistence[i, j] = game.persistence
        density[i, j] = game.densities

np.save(os.path.join(path_to_results, "persistence.npy"), persistence)
np.save(os.path.join(path_to_results, "density.npy"), density)
