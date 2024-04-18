from GUI import GameGUI

if __name__ == '__main__':
    ui = GameGUI(20, 20, 'Szymon Kasprzycki 193065')
    ui.add_organism('Wolf', (0, 2))
    ui.add_organism('Wolf', (0, 1))
    ui.add_organism('Sheep', (0, 5))
    ui.add_organism('Fox', (0, 6))
    ui.maximize()
    ui.run()
