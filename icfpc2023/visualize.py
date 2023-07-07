from __future__ import annotations

import dataclasses
import json
from dataclasses import dataclass
from typing import Any, Mapping, Sequence

import matplotlib.cm as cm
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

    def most_favorite(self) -> int:
        max_value = max(self.tastes)
        return self.tastes.index(max_value)


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

    @property
    def musician_num(self) -> int:
        return len(self.musicians)

    @property
    def instrument_num(self) -> int:
        return len(self.attendees[0].tastes)

    @property
    def attendee_num(self) -> int:
        return len(self.attendees)


def visualize(data: Data, output_path: str) -> None:
    fig = plt.figure()
    ax = fig.add_subplot()

    ax.add_patch(
        patches.Rectangle(
            (0, 0), data.room_width, data.room_height, linewidth=1, fill=False
        )
    )
    ax.add_patch(
        patches.Rectangle(
            (data.stage_bottom_left[0], data.stage_bottom_left[1]),
            data.stage_width,
            data.stage_height,
            linewidth=1,
            edgecolor="b",
            facecolor="b",
        )
    )

    ax.scatter(
        [a.x for a in data.attendees],
        [a.y for a in data.attendees],
        c=[a.most_favorite() for a in data.attendees],
        cmap=cm.rainbow,
        alpha=0.5,
        s=4,
    )

    ax.set_title(
        f"musician: {data.musician_num}, instrument: {data.instrument_num}, attendee: {data.attendee_num}"
    )

    plt.savefig(output_path)
    plt.close()


for i in range(1, 46):
    with open("input_json/{:04}.json".format(i)) as f:
        data_dict = json.load(f)

    data = Data.parse(data_dict)
    visualize(data, "images/{:04}.png".format(i))
