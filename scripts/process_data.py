# The main purpose of this script
# is to combine all the data
# obtained from the simulation for two initially identical fields
# for pairs (b1, b2), where b2 >= b1
#
# The raw data is approximately 19 gb total,
# so we need to pre-process it on the cluster

import numpy as np
from tqdm import tqdm

density = np.zeros((62, 62, 2))
persistence = np.zeros((62, 62, 2))

for i in tqdm(range(62)):
    dens = np.load(f"data/part{i}/density.npy").mean(axis=(2, 4))
    density[i, i:] = dens
    density[i:, i] = dens[..., (1, 0)]
    pers = np.load(f"data/part{i}/persistence.npy").mean(axis=2)
    persistence[i, i:] = pers
    persistence[i:, i] = pers[..., (1, 0)]

np.save("two_field_density.npy", density)
np.save("two_field_persistence.npy", persistence)
