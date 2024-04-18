# Liveable data
ORGANISMS_DATA = {
    'Turtle': {
        'strength': 2,
        'initiative': 1,
        'symbol': 'T',
    },
    'Wolf': {
        'strength': 9,
        'initiative': 5,
        'symbol': 'W',
    },
    'Sheep': {
        'strength': 4,
        'initiative': 4,
        'symbol': 'S',
    },
    'Antelope': {
        'strength': 4,
        'initiative': 4,
        'symbol': 'A',
    },
    'Fox': {
        'strength': 3,
        'initiative': 7,
        'symbol': 'F',
    },
    'CyberSheep': {
        'strength': 11,
        'initiative': 4,
        'symbol': 'C',
    },
    'SosnowskyHogweed': {
        'strength': 10,
        'initiative': 0,
        'symbol': '$',
    },
    'Guarana': {
        'strength': 0,
        'initiative': 0,
        'symbol': '@',
    },
    'Belladonna': {
        'strength': 99,
        'initiative': 0,
        'symbol': '*',
    },
    'Grass': {
        'strength': 0,
        'initiative': 0,
        'symbol': '#',
    },
    'SowThistle': {
        'strength': 0,
        'initiative': 0,
        'symbol': '^',
    },
    'Human': {
        'strength': 5,
        'initiative': 4,
        'symbol': 'H',
    }
}

PLANTS_NAMES = ('SosnowskyHogweed', 'Guarana', 'Belladonna', 'Grass', 'SowThistle')
ANIMALS_NAMES = ('Turtle', 'Wolf', 'Sheep', 'Antelope', 'Fox', 'CyberSheep', 'Human')

# Empty space placeholder
EMPTY_SPACE = None

# GUI data

GUI_THEME = 'LightGreen4'

SIZES = {
    'window': (800, 600),
    'game_field': (5, 2),
    'comment_field': (50, 40),
    'window_margins': (100, 50),
}

FONTS = {
    'default': ('Helvetica', 15),
    'bold': ('Helvetica', 15, 'bold'),
    'italic': ('Helvetica', 15, 'italic'),
    'bold_italic': ('Helvetica', 15, 'bold', 'italic'),
    'title': ('Helvetica', 20, 'bold'),
}

HUMAN_STARTING_POSITION = (4, 4)