from dataclasses import dataclass
import random

NEIGHBOURS_TEMPLATE = [(1, 0), (-1, 0), (0, 1), (0, -1)]


@dataclass
class Position:
    x: int
    y: int

    def __repr__(self):
        return f"({self.x}, {self.y})"

    def get_random_neighbour(self, world, free=False):
        neighbours = NEIGHBOURS_TEMPLATE.copy()
        random.shuffle(neighbours)
        while True:
            if len(neighbours) == 0:
                return None
            neighbour = neighbours.pop(0)
            neighbour_position = Position(self.x + neighbour[0], self.y + neighbour[1])
            if neighbour_position.is_on_map(world):
                if free:
                    if world.is_field_empty(neighbour_position):
                        break
                else:
                    break
        return neighbour_position

    def is_on_map(self, world):
        return 0 <= self.x < world.get_width() and 0 <= self.y < world.get_height()
