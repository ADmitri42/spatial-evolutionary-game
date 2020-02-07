import os
import json


def configure_workflow(config_file: str, def_override: bool = False):
    with open(config_file) as f:
        config = json.load(f)

    path_to_results = os.path.join(config["results"]["dir"], config["results"]["name"])

    try:
        os.makedirs(path_to_results)
    except FileExistsError:
        if not def_override:
            ans = input("Are you sure you want to override existing results?(y/[n]) ").lower()
            if len(ans) == 0 or ans == "n":
                exit(0)
            elif len(ans) > 1 or ans != "y":
                print("Unknown answer")
                exit(1)

    if not os.path.exists(config["fields"]["dir"]):
        raise FileNotFoundError("Can't find " + config["fields"]["dir"])

    for i in range(config["fields"]["quantity"]):
        if not os.path.exists(os.path.join(config["fields"]["dir"], f"field_{config['fields']['size']}_{i}.npy")):
            raise FileNotFoundError("Not enough fields")

    with open(os.path.join(path_to_results, "info.json"), "w") as f:
        json.dump(config, f)

    return config, path_to_results