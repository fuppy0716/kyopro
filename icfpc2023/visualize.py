from __future__ import annotations

import dataclasses
import json
from dataclasses import dataclass
from typing import Any, Mapping, Sequence

import matplotlib.patches as patches
import matplotlib.pyplot as plt
import requests


@dataclass
class Attendee:
    x: float
    y: float
    tastes: list[float]

    @classmethod
    def parse(cls, d: Mapping[str, Any]) -> Attendee:
        return Attendee(x=d["x"], y=d["y"], tastes=d["tastes"])


@dataclass
class Data:
    room_width: float
    room_height: float
    stage_width: float
    stage_height: float

    stage_bottom_left: tuple[float, float]

    musicians: Sequence[int]
    attendees: Sequence[Attendee]

    @classmethod
    def parse(cls, d: Mapping[str, Any]) -> Data:
        return Data(
            room_width=d["room_width"],
            room_height=d["room_height"],
            stage_width=d["stage_width"],
            stage_height=d["stage_height"],
            stage_bottom_left=(d["stage_bottom_left"][0], d["stage_bottom_left"][1]),
            musicians=d["musicians"],
            attendees=[Attendee.parse(a) for a in d["attendees"]],
        )


def visualize(data: Data) -> None:
    fig = plt.figure()
    ax = fig.add_subplot()

    M = max([data.room_width, data.room_height, data.stage_width, data.stage_height])

    print(data.room_width, data.room_height)
    print(data.stage_width, data.stage_height)

    ax.add_patch(
        patches.Rectangle(
            (0, 0), data.room_width / M, data.room_height / M, linewidth=1, fill=False
        )
    )
    ax.add_patch(
        patches.Rectangle(
            (data.stage_bottom_left[0] / M, data.stage_bottom_left[1] / M),
            data.stage_width / M,
            data.stage_height / M,
            linewidth=1,
            edgecolor="b",
            facecolor="b",
        )
    )

    ax.scatter(
        [a.x / M for a in data.attendees],
        [a.y / M for a in data.attendees],
    )

    plt.show()
    plt.close()


for i in range(1, 46):
    with open("input_json/{:04}.json".format(i)) as f:
        data_dict = json.load(f)

    data = Data.parse(data_dict)
    visualize(data)
    break
