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
# sns.set()

from spatgames import color_field_change, NovakMayGamePy as GamePy

steps = 110
b = 1.83
L = 50
game = GamePy(L, b)

# field = np.ones((L, L), dtype=int)
# field[L//2, L//2] = 0
field = np.random.choice((0, 1), (L, L), p=(1-.9, .9))
game.field = field

fig = plt.figure()
im = plt.imshow(color_field_change(field, field), animated=True, cmap=plt.get_cmap('Paired'))
# ax.grid(False)

# updater function
def animate(frame):
    if frame < 3:
        return im,
    field_ = game.field.astype("int")
    game.evolve()
    coll = color_field_change(field_, game.field.astype("int"))
    im.set_array(coll)
    return im,

ani = animation.FuncAnimation(fig, animate, frames=steps, interval=150, blit=True)
ani.save(f"squareevolution.mp4", dpi=300)
