import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.path as path
import matplotlib.animation as animation
import seaborn as sns
plt.style.use("seaborn-whitegrid")
plt.rcParams["axes.grid"] = False
sns.set()

from spatgames import color_field_change_flat, MeanTriangularGamePy as GamePy

b = 1.99
steps = 70

game = GamePy(200, b)
game.field = np.random.choice((0, 1), (200, 200), p=(1-.9, .9))


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
old_field = game.field

def animate(i):
    global game, scatter, old_field
    game.evolve(1)
    update_scatter_collors(old_field.flat, game.field.astype("int").flat, scatter)
    old_field = game.field.astype("int")
    return scatter,

ani = animation.FuncAnimation(fig, animate, frames=steps, interval=150, blit=True)
ani.save(f"evolution{b}.mp4", dpi=300)
