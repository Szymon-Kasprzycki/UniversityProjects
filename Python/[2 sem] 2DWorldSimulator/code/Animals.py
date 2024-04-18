import random
import typing.io
from Organism import Organism
from dataContainers import Position
import Constants


class Animal(Organism):
    def __init__(self, world, strength: int, initiative: int, position: Position, age: int):
        super().__init__(world, strength, initiative, position, age)

    def action(self):
        if not self.get_alive():
            return
        new_position = self._position.get_random_neighbour(self._world)

        if new_position.is_on_map(self._world):
            if self._world.is_field_empty(new_position):
                self._world.move_organism(self, new_position)
            else:
                fight_result = self.collision(self._world.get_organism_from_position(new_position))
                if fight_result == "turtle_defense":
                    return

    def collision(self, organism):
        if not self.get_alive():
            self._world.move_organism(organism, self._position)
            return
        if self._symbol == organism.get_symbol():
            self.reproduce()
        elif organism.get_symbol() == Constants.ORGANISMS_DATA['Turtle']['symbol']:
            if self.get_strength() < 5:
                self._world.add_comment(f"{self.__class__.__name__} failed to attack Turtle")
                return
            else:
                self._world.kill_organism(organism)
                self._world.move_organism(self, organism.get_position())
        elif self._strength > organism.get_strength():
            self._world.kill_organism(organism)
            self._world.move_organism(self, organism.get_position())
            if organism.__class__.__name__ in Constants.ANIMALS_NAMES:
                self._world.add_comment(f"{self.__class__.__name__} killed {organism.__class__.__name__}")
            else:
                self._world.add_comment(f"{self.__class__.__name__} ate {organism.__class__.__name__}")
        else:
            self._world.kill_organism(self)
            self._world.add_comment(f"{organism.__class__.__name__} killed {self.__class__.__name__}")

    def reproduce(self):
        new_position = self._position.get_random_neighbour(self._world, True)
        if new_position is not None and self.get_age() > 3:
            name = self.__class__.__name__
            self._world.add_organism(name, new_position)
            self._world.add_comment(f"New {name} was born at {new_position.y}, {new_position.x}")

    def save(self, file: typing.io.TextIO):
        file.write(self.__class__.__name__ + " " +
                   str(self.get_position().y) + " " +
                   str(self.get_position().x) + " " +
                   str(self.get_age()) + " " +
                   str(self.get_strength()) +
                   '\n'
                   )


class Human(Animal):
    data = Constants.ORGANISMS_DATA['Human']

    def __init__(self, world, position: Position, age: int = 0):
        super().__init__(world, Human.data['strength'], Human.data['initiative'], position, age)
        self._symbol = Human.data['symbol']
        self._special_ability_active = False
        self._special_ability_on_cooldown = False
        self._special_ability_duration = 5
        self._special_ability_cooldown = 0

    def action(self):
        if not self.get_alive():
            return
        key = self._world.get_last_key()
        match key:
            case 'Up:38':
                new_position = Position(self._position.x, self._position.y - 1)
            case 'Down:40':
                new_position = Position(self._position.x, self._position.y + 1)
            case 'Left:37':
                new_position = Position(self._position.x - 1, self._position.y)
            case 'Right:39':
                new_position = Position(self._position.x + 1, self._position.y)
            case _:
                return
        if new_position.is_on_map(self._world):
            if self._world.is_field_empty(new_position):
                self._world.move_organism(self, new_position)
            else:
                fight_result = self.collision(self._world.get_organism_from_position(new_position))
                if fight_result == "turtle_defense":
                    return
        self.special_ability_tick()

    def activate_special_ability(self):
        if not self._special_ability_active and not self._special_ability_on_cooldown:
            self._special_ability_active = True
            self._special_ability_cooldown = 5
            self._strength += 5
        self._world.add_comment("Human activated special ability")

    def special_ability_tick(self):
        if self._special_ability_active:
            self._special_ability_duration -= 1
            if self._special_ability_duration == 0:
                self._special_ability_active = False
                self._special_ability_on_cooldown = True
            if self._special_ability_duration > 0:
                self._world.add_comment(f"Human special ability active for {self._special_ability_duration} more turns")
        if self._special_ability_on_cooldown:
            self._special_ability_cooldown -= 1
            if self._special_ability_cooldown == 0:
                self._special_ability_on_cooldown = False
                self._special_ability_duration = 5
            if self._special_ability_cooldown > 0:
                self._world.add_comment(
                    f"Human special ability on cooldown for {self._special_ability_cooldown} more turns")

    def set_special_ability_active(self, active: bool):
        self._special_ability_active = active

    def get_special_ability_active(self):
        return self._special_ability_active

    def set_special_ability_on_cooldown(self, cooldown: bool):
        self._special_ability_on_cooldown = cooldown

    def get_special_ability_on_cooldown(self):
        return self._special_ability_on_cooldown

    def set_special_ability_duration(self, duration: int):
        self._special_ability_duration = duration

    def get_special_ability_duration(self):
        return self._special_ability_duration

    def set_special_ability_cooldown(self, cooldown: int):
        self._special_ability_cooldown = cooldown

    def get_special_ability_cooldown(self):
        return self._special_ability_cooldown

    def save(self, file: typing.io.TextIO):
        file.write(self.__class__.__name__ + " " +
                   str(self.get_position().y) + " " +
                   str(self.get_position().x) + " " +
                   str(self.get_age()) + " " +
                   str(self.get_strength()) + " " +
                   str(int(self._special_ability_active)) + " " +
                   str(int(self._special_ability_on_cooldown)) + " " +
                   str(self._special_ability_duration) + " " +
                   str(self._special_ability_cooldown) +
                   '\n'
                   )


class Wolf(Animal):
    data = Constants.ORGANISMS_DATA['Wolf']

    def __init__(self, world, position: Position, age: int = 0, strength: int = 0):
        strength = strength if strength != 0 else Wolf.data['strength']
        super().__init__(world, strength, Wolf.data['initiative'], position, age)
        self._symbol = Wolf.data['symbol']


class Sheep(Animal):
    data = Constants.ORGANISMS_DATA['Sheep']

    def __init__(self, world, position: Position, age: int = 0, strength: int = 0):
        strength = strength if strength != 0 else Sheep.data['strength']
        super().__init__(world, strength, Sheep.data['initiative'], position, age)
        self._symbol = Sheep.data['symbol']


class Fox(Animal):
    data = Constants.ORGANISMS_DATA['Fox']

    def __init__(self, world, position: Position, age: int = 0, strength: int = 0):
        strength = strength if strength != 0 else Fox.data['strength']
        super().__init__(world, strength, Fox.data['initiative'], position, age)
        self._symbol = Fox.data['symbol']

    def action(self):
        if not self.get_alive():
            return
        new_position = self._position.get_random_neighbour(self._world)

        if new_position.is_on_map(self._world):
            if self._world.is_field_empty(new_position):
                self._world.move_organism(self, new_position)
            elif self._world.get_organism_from_position(new_position).get_strength() > 5:
                return
            else:
                self.collision(self._world.get_organism_from_position(new_position))


class Turtle(Animal):
    data = Constants.ORGANISMS_DATA['Turtle']

    def __init__(self, world, position: Position, age: int = 0, strength: int = 0):
        strength = strength if strength != 0 else Turtle.data['strength']
        super().__init__(world, strength, Turtle.data['initiative'], position, age)
        self._symbol = Turtle.data['symbol']

    def action(self):
        if random.randint(0, 4) == 0:
            super().action()

    def collision(self, organism):
        if not self.get_alive():
            self._world.move_organism(organism, self._position)
            return
        else:
            super().collision(organism)


class Antelope(Animal):
    data = Constants.ORGANISMS_DATA['Antelope']

    def __init__(self, world, position: Position, age: int = 0, strength: int = 0):
        strength = strength if strength != 0 else Antelope.data['strength']
        super().__init__(world, strength, Antelope.data['initiative'], position, age)
        self._symbol = Antelope.data['symbol']

    def action(self):
        super().action()
        super().action()

    def collision(self, organism):
        if not self.get_alive():
            self._world.move_organism(organism, self._position)
            return
        if random.randint(0, 1) == 0:
            super().collision(organism)
        else:
            new_position = self._position.get_random_neighbour(self._world, free=True)
            if new_position is not None:
                self._world.move_organism(self, new_position)
            else:
                super().collision(organism)


class CyberSheep(Animal):
    data = Constants.ORGANISMS_DATA['CyberSheep']

    def __init__(self, world, position: Position, age: int = 0, strength: int = 0):
        strength = strength if strength != 0 else CyberSheep.data['strength']
        super().__init__(world, strength, CyberSheep.data['initiative'], position, age)
        self._symbol = CyberSheep.data['symbol']

    def action(self):
        if not self.get_alive():
            return
        if not self._world.is_any_sosnowsky():
            super().action()
        else:
            nearest_sosnowsky = self._world.get_nearest_sosnowsky(self._position)
            # go in the direction of the nearest sosnowsky
            if nearest_sosnowsky.get_position().x > self._position.x:
                new_position = Position(self._position.x + 1, self._position.y)
            elif nearest_sosnowsky.get_position().x < self._position.x:
                new_position = Position(self._position.x - 1, self._position.y)
            elif nearest_sosnowsky.get_position().y > self._position.y:
                new_position = Position(self._position.x, self._position.y + 1)
            elif nearest_sosnowsky.get_position().y < self._position.y:
                new_position = Position(self._position.x, self._position.y - 1)
            else:
                new_position = self._position

            if new_position.is_on_map(self._world):
                if self._world.is_field_empty(new_position):
                    self._world.move_organism(self, new_position)
                else:
                    self.collision(self._world.get_organism_from_position(new_position))

    def collision(self, organism):
        if not self.get_alive():
            self._world.move_organism(organism, self._position)
        if organism.get_symbol() == Constants.ORGANISMS_DATA['SosnowskyHogweed']['symbol']:
            self._world.kill_organism(organism)
            self._world.move_organism(self, organism.get_position())
        else:
            super().collision(organism)
