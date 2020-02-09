import os
import argparse
from collections import Counter

import numpy as np
from tqdm import tqdm

from meangame import MeanGamePy
from configurator import configure_workflow

parser = argparse.ArgumentParser(description='Collects data about persistence and saves it.')
parser.add_argument('config', metavar='config', type=str,
                    help='JSON file with configuration')

parser.add_argument('-y', dest='overwrite', action='store_true', help="If needed, answer yes")
parser.set_defaults(overwrite=False)

args = parser.parse_args()
config, path_to_results = configure_workflow(args.config, args.overwrite)


game = MeanGamePy(config["fields"]["size"], 1.3)
nmdists = []
clustersizes = [[], []]
field_temp = os.path.join(config["fields"]["dir"], f"field_{config['fields']['size']}" + "_{0}.npy")
max_size = 0

for b in tqdm(config["parameters"]):
    nmdist = np.zeros((1, 9, 9), dtype="int")
    clustersize = [[], []]
    game.b = b
    for i in range(config["fields"]["quantity"]):
        game.field = np.load(field_temp.format(i))
        game.evolve(config["steps"]["drop"])
        for _ in range(config["steps"]["measure"]):
            nmdist += game.n_m_distribution().reshape((9, 9))
            cl0, cl1 = game.clustering(True)

            clustersize[0].extend(cl0.tolist())
            clustersize[1].extend(cl1.tolist())

    nmdists.append(nmdist)
    max_size = max(max(max(clustersize[0]), max(clustersize[1])), max_size)
    clustersizes[0].append(clustersize[0])
    clustersizes[1].append(clustersize[1])

clustsizesdist = np.zeros((2, len(config["parameters"]), max_size+1))

for i in range(2):
    for b in range(len(config["parameters"])):
        count = Counter(clustersizes[i][b])
        for k, s in count.items():
            if k == 0:
                continue
            clustsizesdist[i, b, k] = s

np.save(os.path.join(path_to_results, "nmdistribution.npy"), np.array(nmdists))
np.save(os.path.join(path_to_results, "clustersizedist.npy"), clustsizesdist)
