from dataContainers import Position
import Constants


class Organism:
    def __init__(self, world, strength: int, initiative: int, position: Position, age: int = 0):
        self._world = world
        self._age = age
        self._alive = True
        self._strength = strength
        self._initiative = initiative
        self._position = position
        self._symbol = '0'

    def get_age(self) -> int:
        return self._age

    def get_alive(self) -> bool:
        return self._alive

    def get_strength(self) -> int:
        return self._strength

    def get_initiative(self) -> int:
        return self._initiative

    def get_position(self) -> Position:
        return self._position

    def get_symbol(self) -> str:
        return self._symbol

    def set_age(self, age: int):
        self._age = age

    def set_alive(self, alive: bool):
        self._alive = alive

    def set_strength(self, strength: int):
        self._strength = strength

    def set_initiative(self, initiative: int):
        self._initiative = initiative

    def set_position(self, position: Position):
        self._position = position

    def death(self):
        self._alive = False

    def action(self):
        pass

    def collision(self, organism):
        pass

    def is_cyber_sheep(self):
        return self.get_symbol() == Constants.ORGANISMS_DATA['CyberSheep']['symbol']
