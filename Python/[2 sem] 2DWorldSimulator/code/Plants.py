from Organism import Organism
from random import randint
from dataContainers import Position
import Constants


class Plant(Organism):
    def __init__(self, world, strength: int, initiative: int, position: Position, age: int = 0):
        super().__init__(world, strength, initiative, position, age)

    def action(self):
        if not self.get_alive():
            return
        spread_limit = 7
        if randint(0, 100) < spread_limit:
            self.reproduce()

    def reproduce(self):
        new_position = self._position.get_random_neighbour(self._world, free=True)
        if new_position is not None:
            self._world.add_organism(self.__class__.__name__, new_position)
            self._world.add_comment(self.__class__.__name__ + " has spread")

    def collision(self, organism):
        if not self.get_alive():
            organism.set_position(self._position)
            return
        if organism.get_symbol() == self.get_symbol():
            self.reproduce()
        elif organism.__class__.__name__ in Constants.PLANTS_NAMES:
            return  # plants don't fight
        else:
            self._world.kill_organism(self)
            self._world.add_comment(self.__class__.__name__ + " has been eaten by " + organism.__class__.__name__)


class Grass(Plant):
    def __init__(self, world, position: Position, age: int = 0):
        data = Constants.ORGANISMS_DATA['Grass']
        super().__init__(world, data['strength'], data['initiative'], position, age)
        self._symbol = data['symbol']


class SowThistle(Plant):
    def __init__(self, world, position: Position, age: int = 0):
        data = Constants.ORGANISMS_DATA['SowThistle']
        super().__init__(world, data['strength'], data['initiative'], position, age)
        self._symbol = data['symbol']

    def action(self):
        for _ in range(3):
            super().action()


class Guarana(Plant):
    def __init__(self, world, position: Position, age: int = 0):
        data = Constants.ORGANISMS_DATA['Guarana']
        super().__init__(world, data['strength'], data['initiative'], position, age)
        self._symbol = data['symbol']

    def collision(self, organism):
        if not self.get_alive():
            organism.set_position(self._position)
            return
        if organism.get_symbol() == self.get_symbol():
            self.reproduce()
        else:
            organism.set_strength(organism.get_strength() + 3)
            self._world.kill_organism(self)


class Belladonna(Plant):
    def __init__(self, world, position: Position, age: int = 0):
        data = Constants.ORGANISMS_DATA['Belladonna']
        super().__init__(world, data['strength'], data['initiative'], position, age)
        self._symbol = data['symbol']

    def collision(self, organism):
        if not self.get_alive():
            organism.set_position(self._position)
            return
        if organism.get_symbol() == self.get_symbol():
            self.reproduce()
        else:
            self._world.kill_organism(organism)


class SosnowskyHogweed(Plant):
    def __init__(self, world, position: Position, age: int = 0):
        data = Constants.ORGANISMS_DATA['SosnowskyHogweed']
        super().__init__(world, data['strength'], data['initiative'], position, age)
        self._symbol = data['symbol']

    def action(self):
        if not self.get_alive():
            return
        neighbours = [(1, 0), (1, 0), (0, 1), (0, -1)]
        for neighbour in neighbours:
            new_position = Position(self.get_position().x + neighbour[0], self.get_position().y + neighbour[1])
            if new_position.is_on_map(self._world):
                organism = self._world.get_organism_from_position(new_position)
                if organism is not None and not organism.is_cyber_sheep():
                    self._world.kill_organism(organism)

    def collision(self, organism):
        if not self.get_alive():
            organism.set_position(self._position)
            return
        if organism.get_symbol() == self.get_symbol():
            self.reproduce()
        else:
            if organism.is_cyber_sheep():
                self._world.kill_organism(self)
            self._world.kill_organism(organism)
