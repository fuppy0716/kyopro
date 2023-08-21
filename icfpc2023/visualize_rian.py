from __future__ import annotations

import dataclasses
import json
import os
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
class Placement:
    x: float
    y: float

    @classmethod
    def parse(cls, d: Mapping[str, Any]) -> Placement:
        return Placement(x=d["x"], y=d["y"])


@dataclass
class Pillar:
    x: float
    y: float

    radius: float

    @classmethod
    def parse(cls, d: Mapping[str, Any]) -> Pillar:
        return Pillar(x=d["center"][0], y=d["center"][1], radius=d["radius"])


@dataclass
class Problem:
    room_width: float
    room_height: float
    stage_width: float
    stage_height: float

    stage_bottom_left: tuple[float, float]

    musicians: Sequence[int]
    attendees: Sequence[Attendee]

    musician_placements: Sequence[Placement]

    @classmethod
    def parse(cls, d: Mapping[str, Any], d2: Mapping[str, Any]) -> Problem:
        return Problem(
            room_width=d["room_width"],
            room_height=d["room_height"],
            stage_width=d["stage_width"],
            stage_height=d["stage_height"],
            stage_bottom_left=(d["stage_bottom_left"][0], d["stage_bottom_left"][1]),
            musicians=d["musicians"],
            attendees=[Attendee.parse(a) for a in d["attendees"]],
            pillars=[Pillar.parse(p) for p in d["pillars"]],
            musician_placements=[Placement.parse(a) for a in d2["placements"]],
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


def visualize(problem: Problem, output_path: str, problem_id: int) -> None:
    fig = plt.figure(figsize=(16, 12))
    ax = fig.add_subplot()

    ax.add_patch(
        patches.Rectangle(
            (0, 0), problem.room_width, problem.room_height, linewidth=1, fill=False
        )
    )
    ax.add_patch(
        patches.Rectangle(
            (problem.stage_bottom_left[0], problem.stage_bottom_left[1]),
            problem.stage_width,
            problem.stage_height,
            linewidth=1,
            edgecolor="b",
            facecolor="b",
            fill=False,
        )
    )

    ax.scatter(
        [a.x for a in problem.attendees],
        [a.y for a in problem.attendees],
        c=[a.most_favorite() for a in problem.attendees],
        cmap=cm.rainbow,
        alpha=0.5,
        s=5,
    )

    ax.scatter(
        [a.x for a in problem.musician_placements],
        [a.y for a in problem.musician_placements],
        c="red",
        alpha=0.5,
        s=5,
    )

    ax.set_title(
        f"problem_id: {problem_id}, musician: {problem.musician_num}, instrument: {problem.instrument_num}, attendee: {problem.attendee_num}"
    )

    plt.savefig(output_path)
    plt.close()


for i in range(1, 1000):
    if os.path.isfile(f"input_json/{i:04}.json"):
        with open(f"input_json/{i:04}.json") as f:
            problem_dict = json.load(f)

        if os.path.isfile(f"output_json/{i:04}.json"):
            with open(f"output_json/{i:04}.json") as f:
                solution_dict = json.load(f)
        else:
            solution_dict = {"placements": []}

        problem = Problem.parse(problem_dict, solution_dict)
        visualize(problem, "images/{:04}.png".format(i), problem_id=i)
    break
