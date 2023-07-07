import json
import os

import requests


def get(problem_id):
    response = requests.get(
        f"https://api.icfpcontest.com/problem?problem_id={problem_id}"
    )
    return json.loads(response.json()["Success"])


for i in range(1, 46):
    ret = get(i)
    with open("in/{:04}.json".format(i), "w") as f:
        json.dump(ret, f, indent=4)
