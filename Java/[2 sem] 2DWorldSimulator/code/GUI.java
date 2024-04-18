import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Objects;


public class GUI {
    private Human player;
    private final JButton[] gridButtons;
    private ArrayList<Integer> allowedKeys;
    private final JFrame gFrame;
    private final JPanel containerPanel;
    private final JPanel buttonPanel;
    private final JPanel commentPanel;
    private final int gridWidth;
    private final int gridHeight;
    private final String[] organismOptions = {"Antelope", "Turtle", "Fox", "Wolf", "Sheep", "Grass", "SowThistle", "Belladonna", "Guarana", "SosnowskyHogweed"};
    private final JLabel[] commentLabels;
    public Integer lastPressedKey;
    public GUI(int width, int height) {
        gridWidth = width;
        gridHeight = height;
        gridButtons = new JButton[height * width];
        commentLabels = new JLabel[20];
        gFrame = new JFrame();
        buttonPanel = new JPanel();
        containerPanel = new JPanel();
        commentPanel = new JPanel();

        gFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        gFrame.setTitle("Szymon Kasprzycki 193065");
        this.drawGrid();
        this.drawCommentPanel();
        this.setupMenuBar();
        this.addHumanMoveListener();

        containerPanel.setBorder(BorderFactory.createEmptyBorder(10,10,10,10));
        gFrame.getContentPane().add(containerPanel, BorderLayout.WEST); //
        gFrame.pack();
        gFrame.setExtendedState(JFrame.MAXIMIZED_BOTH);
        gFrame.setFocusable(true);
        gFrame.setVisible(true);
    }

    private void drawCommentPanel() {
        commentPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        commentPanel.setLayout(new GridLayout(20, 1));
        for (int i = 0; i < 20; i++) {
            JLabel label = new JLabel(Integer.toString(i));
            label.setBorder(BorderFactory.createEmptyBorder(10, 0, 10, 0));
            commentLabels[i] = label;
            commentPanel.add(label);
        }
        containerPanel.add(commentPanel, BorderLayout.EAST);
    }

    private void drawGrid() {
        buttonPanel.setLayout(new GridLayout(gridHeight,gridWidth));
        for (int k = 0; k < gridHeight; k++)
        {
            for (int j = 0; j < gridWidth; j++)
            {
                // Integer.toString(k*gridWidth + j)
                JButton button = new JButton();
                button.setFont(new Font("Arial", Font.PLAIN, 14));
                button.setMargin(new Insets(0,0,0,0));
                gridButtons[k * gridHeight + j] = button;

                this.setupButtonOrganismAdding(button, gFrame, organismOptions);
                buttonPanel.add(button);
            }
        }
        buttonPanel.setPreferredSize(new Dimension(1200, 900));
        containerPanel.add(buttonPanel, BorderLayout.EAST);
    }

    private static String getSpecieNameDialog(JFrame frame, String[] options) {
        return (String)JOptionPane.showInputDialog(
                frame,
                "Select specie:",
                "Add new organism",
                JOptionPane.PLAIN_MESSAGE,
                null,
                options,
                options[0]
        );
    }

    private void setupButtonOrganismAdding(JButton btn, JFrame frame, String[] options) {
        btn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (!Objects.equals(btn.getText(), "")) { return; }
                String result = GUI.getSpecieNameDialog(frame, options);
                if (Arrays.asList(options).contains(result)){
                    int index = Arrays.asList(gridButtons).indexOf(btn);
                    int x = index % gridWidth;
                    int y = index / gridWidth;
                    Organism newOrganism = player.world.createOrganism(result, x, y);
                    player.world.addOrganism(newOrganism);
                    player.world.drawWorld();
                }
                frame.requestFocus();
            }
        });
    }

    private void addHumanMoveListener() {
        allowedKeys = new ArrayList<>();
        allowedKeys.add(KeyEvent.VK_DOWN);
        allowedKeys.add(KeyEvent.VK_LEFT);
        allowedKeys.add(KeyEvent.VK_UP);
        allowedKeys.add(KeyEvent.VK_RIGHT);
        allowedKeys.add(KeyEvent.VK_Q);

        gFrame.addKeyListener(new MoveListener());
    }

    private class MoveListener implements KeyListener {
        @Override
        public void keyTyped(KeyEvent e) {}

        @Override
        public void keyPressed(KeyEvent e) {
            if (allowedKeys.contains(e.getKeyCode())) {
                if (e.getKeyCode() == KeyEvent.VK_Q) { endGame(); }
                else {
                    lastPressedKey = e.getKeyCode();
                    player.action();
                }
            }
        }

        @Override
        public void keyReleased(KeyEvent e) {}
    }

    private void clearComments() {
        for (int i = 0; i < 20; i++) {
            this.commentLabels[i].setText("");
        }
    }

    public void updateWorld(Organism[][] map) {
        for (int i = 0; i < this.gridHeight; i++) {
            for (int j = 0; j < this.gridWidth; j++) {
                if (map[i][j] != null) {
                    this.gridButtons[i*gridHeight + j].setText(map[i][j].getSymbol());
                }
                else {
                    this.gridButtons[i * gridHeight + j].setText("");
                }
            }
        }
    }

    public void endGame() {
        System.exit(0);
    }

    public void showComments(ArrayList<String> comments) {
        this.clearComments();
        for (int i = 0; i < comments.size(); i++) {
            this.commentLabels[i].setText(comments.get(i));
        }
    }

    public void showGameOver() {
        JOptionPane.showMessageDialog(gFrame, "Game over!");
    }

    public void setupMenuBar() {
        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("Menu");
        JMenuItem saveItem = new JMenuItem("Save");
        JMenuItem loadItem = new JMenuItem("Load");
        JMenuItem exitItem = new JMenuItem("Exit");
        JMenu playerMenu = new JMenu("Player");
        JMenuItem useSpecialAbilityItem = new JMenuItem("Use special ability");
        saveItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                fileChooser.setDialogTitle("Specify a file to save");

                int userSelection = fileChooser.showSaveDialog(gFrame);

                if (userSelection == JFileChooser.APPROVE_OPTION) {
                    File fileToSave = fileChooser.getSelectedFile();
                    String fileName = fileToSave.getAbsolutePath();
                    if (!fileName.endsWith(".txt")) {
                        fileName += ".txt";
                    }
                    System.out.println("Save as file: " + fileName);
                    player.world.saveToFile(fileName, player);
                }
            }
        });
        loadItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                fileChooser.setDialogTitle("Specify a file to save");

                int userSelection = fileChooser.showOpenDialog(gFrame);

                if (userSelection == JFileChooser.APPROVE_OPTION) {
                    File fileToSave = fileChooser.getSelectedFile();
                    String fileName = fileToSave.getAbsolutePath();
                    if (!fileName.endsWith(".txt")) {
                        fileName += ".txt";
                    }
                    System.out.println("Read from file: " + fileName);
                    player.setupFromFile(fileName);
                }

            }
        });
        exitItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                endGame();
            }
        });
        useSpecialAbilityItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                player.usePower();
            }
        });
        menu.add(saveItem);
        menu.add(loadItem);
        menu.add(exitItem);
        playerMenu.add(useSpecialAbilityItem);
        menuBar.add(menu);
        menuBar.add(playerMenu);
        gFrame.setJMenuBar(menuBar);
    }
    public void setPlayer(Human newPlayer) {
        this.player = newPlayer;
    }
    public Human getPlayer() {
        return this.player;
    }
}