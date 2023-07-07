from __future__ import annotations

import dataclasses
import json
from dataclasses import dataclass
from typing import Any, Mapping, Sequence

import matplotlib
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
