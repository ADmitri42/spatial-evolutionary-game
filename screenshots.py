import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from tqdm import tqdm

plt.style.use("seaborn-whitegrid")
plt.rcParams["axes.grid"] = False
sns.set()

from spatgames import color_field_change_flat, MeanTriangularGamePy as GamePy

b = 1.99
steps = 70
N = 90
game = GamePy(N, b)
field = np.random.choice((0, 1), (N, N), p=(1-.9, .9))
game.field = field

def create_scatter(field_size, point_size=10, scale=10):
    point_size = scale / (field_size ** 2) * 10000
    y, x = np.ones((field_size, field_size), dtype='int').nonzero()
    scatter = plt.scatter(x + y * np.sin(np.pi / 6), y * np.sin(np.pi / 3), s=point_size, marker='h')
    return scatter


def update_scatter_collors(prev_field, next_field, scatter):
    scatter.set_color(color_field_change_flat(np.asarray(prev_field), np.asarray(next_field)))

fig = plt.figure(figsize=(10 ,6))
# plt.xlim(1999, 2016)
# plt.ylim(np.min(overdose)[0], np.max(overdose)[0])
# f, (ax, cbar_ax) = plt.figure(figsize=(10, 6))
# plt.xlabel('N',fontsize=20)
# plt.ylabel('M',fontsize=20)
# plt.title('N-M distribution',fontsize=20)

scatter = create_scatter(game.L)


for b in tqdm([1.1, 1.3, 1.5, 1.6, 1.65, 1.7, 1.8, 1.9, 1.99]):
    game.field = field
    game.b = b
    game.evolve(5000)
    old_field = game.field.astype("int")
    game.evolve(1)
    update_scatter_collors(old_field.flat, game.field.astype("int").flat, scatter)
    plt.savefig(f"triangular_snapshot_b={b}.jpg", dpi=300, quality=95)
