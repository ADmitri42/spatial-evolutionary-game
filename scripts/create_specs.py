# The script creates a directory
# with configuration files similar to ' template_two_f. json'
# with different pairs (b1, b2) for initially identical fields,
# where b2 >= b1,
# so that we can automatically run
# multiple processes with different win values

import json
import os
bs = [0.9, 0.919, 0.937, 0.956, 0.975, 0.993, 1.01, 1.03, 1.05,
      1.07, 1.09, 1.11, 1.12, 1.14, 1.16, 1.18, 1.2, 1.22,
      1.24, 1.25, 1.27, 1.29, 1.31, 1.33, 1.35, 1.37, 1.38,
      1.4, 1.42, 1.44, 1.46, 1.48, 1.5, 1.52, 1.53, 1.53,
      1.55, 1.57, 1.59, 1.61, 1.62, 1.63, 1.65, 1.66, 1.68,
      1.7, 1.72, 1.74, 1.76, 1.78, 1.79, 1.81, 1.83, 1.85,
      1.87, 1.89, 1.91, 1.93, 1.94, 1.96, 1.98, 2.]

with open("template_two_f.json") as f:
    config = json.load(f)

try:
    os.makedirs("specifications")
except FileExistsError:
    pass

for i in range(len(bs)):
    config["parameters"] = {
        "b1": [bs[i]],
        "b2": bs[i:]
    }
    config["results"]["name"] = f"part{i}"

    with open(os.path.join("specifications", f"{i}.json"), "w") as f:
        json.dump(config, f)
