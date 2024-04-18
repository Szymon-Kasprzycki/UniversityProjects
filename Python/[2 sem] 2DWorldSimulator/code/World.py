import sys
from Plants import Grass, Guarana, SowThistle, Belladonna, SosnowskyHogweed
from Animals import Wolf, Sheep, Fox, Turtle, Antelope, CyberSheep, Human
import Constants
from dataContainers import Position
from Organism import Organism
import math


class GameWorld:
    def __init__(self, width: int, height: int):
        self._game_over = False
        self._organisms = []
        self._map = [[Constants.EMPTY_SPACE for _ in range(width)] for i in range(height)]
        self._to_kill = []
        self._sosnowsky_count = 0
        self._move_possible = True
        self._comments = []
        self._last_key = None
        self._human = Human(self, Position(Constants.HUMAN_STARTING_POSITION[0], Constants.HUMAN_STARTING_POSITION[1]))
        self._organisms.append(self._human)
        self._map[Constants.HUMAN_STARTING_POSITION[0]][Constants.HUMAN_STARTING_POSITION[1]] = self._human

    def add_organism(self, name: str, position: Position, age: int = 0, strength: int = 0):
        if name == "SosnowskyHogweed":
            self._sosnowsky_count += 1

        organism = None
        # make a switch case for all organisms
        match name:
            case "Grass":
                organism = Grass(self, position, age)
            case "SowThistle":
                organism = SowThistle(self, position, age)
            case "Guarana":
                organism = Guarana(self, position, age)
            case "Belladonna":
                organism = Belladonna(self, position, age)
            case "SosnowskyHogweed":
                organism = SosnowskyHogweed(self, position, age)
            case "Wolf":
                organism = Wolf(self, position, age, strength)
            case "Sheep":
                organism = Sheep(self, position, age, strength)
            case "Fox":
                organism = Fox(self, position, age, strength)
            case "Turtle":
                organism = Turtle(self, position, age, strength)
            case "Antelope":
                organism = Antelope(self, position, age, strength)
            case "CyberSheep":
                organism = CyberSheep(self, position, age, strength)
            case _:
                print("Wrong name of organism")

        self._organisms.append(organism)
        self._map[position.y][position.x] = organism

    def is_field_empty(self, position: Position):
        return self._map[position.y][position.x] == Constants.EMPTY_SPACE

    def get_organism_from_position(self, position: Position):
        return self._map[position.y][position.x]

    def kill_organism(self, organism: Organism):
        organism.death()
        if organism.get_symbol() == Constants.ORGANISMS_DATA['Human']['symbol']:
            self._game_over = True
        self._to_kill.append(organism)

    def is_any_sosnowsky(self):
        return self._sosnowsky_count != 0

    def get_nearest_sosnowsky(self, position: Position):
        sosnowsky_hogweeds = [org for org in self._organisms if
                              org.get_symbol() == Constants.ORGANISMS_DATA['SosnowskyHogweed']['symbol']]

        min_distance = sys.maxsize
        target = None

        for hogweed in sosnowsky_hogweeds:
            distance = math.sqrt(
                pow(position.x - hogweed.get_position().x, 2) + pow(position.y - hogweed.get_position().y, 2))
            if distance < min_distance:
                min_distance = distance
                target = hogweed

        return target

    def make_turn(self):
        self._move_possible = False

        self._clear_comments()

        # sort organisms by initiative
        self._organisms.sort(key=lambda org: org.get_initiative(), reverse=True)

        # make turn for each organism
        for org in self._organisms:
            org.action()

        if self._game_over:
            return self._organisms

        # kill organisms
        for org in self._to_kill:
            if org in self._organisms:
                self._organisms.remove(org)
            self._map[org.get_position().y][org.get_position().x] = Constants.EMPTY_SPACE
            if org.get_symbol() == Constants.ORGANISMS_DATA['SosnowskyHogweed']['symbol']:
                self._sosnowsky_count -= 1

        self._to_kill.clear()

        self._move_possible = True

        return self._organisms

    def get_organisms(self):
        return self._organisms

    def get_width(self):
        return len(self._map[0])

    def get_height(self):
        return len(self._map)

    def move_organism(self, organism: Organism, position: Position):
        self._map[organism.get_position().y][organism.get_position().x] = Constants.EMPTY_SPACE
        self._map[position.y][position.x] = organism
        organism.set_position(position)

    def is_move_possible(self):
        return self._move_possible

    def add_comment(self, comment: str):
        self._comments.append(comment)

    def get_comments(self):
        return self._comments

    def _clear_comments(self):
        self._comments.clear()

    def get_map(self):
        return self._map

    def save_to_file(self, file_name: str):
        with open(file_name, 'w+') as file:
            file.write(str(self.get_width()) + ' ' + str(self.get_height()) + '\n')
            file.write(str(self._sosnowsky_count) + '\n')
            for org in self._organisms:
                org.save(file)

    def load_from_file(self, file_name: str):
        self._organisms.clear()
        self._to_kill.clear()
        self._comments.clear()
        self._map.clear()
        with open(file_name, 'r') as file:
            lines = file.readlines()
            width = int(lines[0].split(' ')[0].strip())
            height = int(lines[0].split(' ')[1].strip())
            self._map = [[Constants.EMPTY_SPACE for _ in range(width)] for i in range(height)]
            self._sosnowsky_count = int(lines[1].strip())

            for i in range(2, len(lines)):
                line = lines[i].split(' ')
                if line[0] == 'Human':
                    self._human.set_position(Position(int(line[2]), int(line[1])))
                    self._map[int(line[2])][int(line[1])] = self._human
                    self._human.set_age(int(line[3]))
                    self._human.set_strength(int(line[4]))
                    self._human.set_special_ability_active(bool(int(line[5])))
                    self._human.set_special_ability_on_cooldown(bool(int(line[6])))
                    self._human.set_special_ability_duration(int(line[7]))
                    self._human.set_special_ability_cooldown(int(line[8]))
                    self._organisms.append(self._human)
                else:
                    self.add_organism(line[0], Position(int(line[2]), int(line[1])), int(line[3]), int(line[4]))

    def get_human(self):
        return self._human

    def set_last_key(self, key):
        self._last_key = key

    def get_last_key(self):
        return self._last_key

    def is_game_over(self):
        return self._game_over