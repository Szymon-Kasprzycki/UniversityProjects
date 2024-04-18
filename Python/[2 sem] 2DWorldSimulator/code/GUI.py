import PySimpleGUI as sg
from World import GameWorld
import Constants
from dataContainers import Position


class GameGUI(sg.Window):
    def __init__(self, width: int, height: int, title: str):
        sg.theme(Constants.GUI_THEME)
        self._game_organisms = None
        self._world = GameWorld(width, height)
        self._window_layout = self._generate_main_layout(width, height)
        super().__init__(title=title, layout=self._window_layout, return_keyboard_events=True, use_default_focus=False,
                         margins=Constants.SIZES['window_margins'], finalize=True)

    def run(self):
        while True:
            event, values = self.read()
            if event == sg.WIN_CLOSED or event == 'OK' or event == 'q':
                break

            self._process_event(event, values)

            if self._world.is_game_over():
                break
        self.close()

    def _process_event(self, event, values):
        if event.startswith('cell--'):
            if self[event].GetText() != ' ':
                return
            organism_name = self._popup_select_organism()
            if organism_name is not None:
                position = tuple(map(int, event.split('--')[1:]))
                self.add_organism(organism_name, position)
            self._update()
        elif event in ('Down:40', 'Up:38', 'Left:37', 'Right:39') and self._world.is_move_possible():
            self._world.set_last_key(event)
            self._game_organisms = self._world.make_turn()
            self._update()
            if self._world.is_game_over():
                self._popup_game_over()
        elif event in ('s', 'S'):
            filename = self._popup_save_game()
            if filename is not None:
                self._world.save_to_file(filename)
        elif event in ('l', 'L'):
            filename = self._popup_load_game()
            if filename is not None:
                self._world.load_from_file(filename)
                self._game_organisms = self._world.get_organisms()
                self._update()
        elif event in ('p', 'P'):
            human = self._world.get_human()
            if human is not None:
                human.activate_special_ability()
                self._update_comments()

    def _update(self):
        # Clear all cells
        for row in range(len(self._world.get_map())):
            for col in range(len(self._world.get_map()[row])):
                key = f'cell--{row}--{col}'
                self[key].update(' ')

        # Update cells with organisms
        for org in self._game_organisms:
            key = f'cell--{org.get_position().y}--{org.get_position().x}'
            self[key].update(org.get_symbol())

        # Update comments
        self._update_comments()

    def _update_comments(self):
        self['_COMMENTS_'].update(value='\n'.join(self._world.get_comments()))

    def add_organism(self, organism_name: str, position: tuple):
        pos = Position(position[1], position[0])
        self._world.add_organism(organism_name, pos)
        self._game_organisms = self._world.get_organisms()
        self._update()

    @staticmethod
    def _generate_main_layout(width: int, height: int):
        grid_column = [
            [sg.Button("_", key=f'cell--{row}--{col}', size=Constants.SIZES['game_field'], pad=(0, 0)) for col in
             range(width)]
            for row in range(height)
        ]
        comments_column = [
            [sg.Text("Comments: ", expand_x=True, justification='center', font=Constants.FONTS['bold'])],
            [sg.Multiline(size=(50, 40), key='_COMMENTS_', disabled=True, font=Constants.FONTS['default'])],
        ]
        return [[sg.Column(grid_column), sg.Push(), sg.Column(comments_column)]]

    @staticmethod
    def _popup_select_organism():
        org_list = tuple(name for name in Constants.ORGANISMS_DATA.keys() if name != "Human")
        layout = [
            [sg.Listbox(org_list, key='_LIST_', size=(45, len(org_list)), select_mode='single', bind_return_key=True),
             sg.OK()]
        ]
        window = sg.Window('Select organism', layout=layout)
        event, values = window.read()
        window.close()
        del window
        if values['_LIST_']:
            return values['_LIST_'][0]
        return None

    @staticmethod
    def _popup_game_over():
        layout = [
            [sg.Text("Game over!", font=Constants.FONTS['bold'])],
            [sg.Button('OK', key='OK')]
        ]
        window = sg.Window('Game over', layout=layout)
        window.read()
        window.close()
        del window

    @staticmethod
    def _popup_save_game():
        layout = [
            [sg.Text("Enter file name: ", font=Constants.FONTS['bold'])],
            [sg.InputText(key='_INPUT_')],
            [sg.Button('OK', key='OK')]
        ]
        window = sg.Window('Save game', layout=layout)
        event, values = window.read()
        window.close()
        del window
        if values['_INPUT_']:
            result = values['_INPUT_']
            if not result.endswith('.txt'):
                result += '.txt'
            return result
        return None

    @staticmethod
    def _popup_load_game():
        layout = [
            [sg.Text("Enter file name: ", font=Constants.FONTS['bold'])],
            [sg.InputText(key='_INPUT_')],
            [sg.Button('OK', key='OK')]
        ]
        window = sg.Window('Load game', layout=layout)
        event, values = window.read()
        window.close()
        del window
        if values['_INPUT_']:
            result = values['_INPUT_']
            if not result.endswith('.txt'):
                result += '.txt'
            return result
        return None