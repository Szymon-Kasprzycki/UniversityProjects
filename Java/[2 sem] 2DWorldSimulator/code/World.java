import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class World {
    private final GUI ui;
    private int width;
    private int height;
    private final Organism[][] map;
    private final List<Organism> allOrganisms;
    private final List<Organism> queue;
    private final List<Organism> toDelete;
    public final Commentator commentator;
    public Integer lastPressedKey;

    public boolean isOnMap(int x, int y) {
        return (x >= 0 && x < this.width && y >= 0 && y < this.height);
    }

    public World(int w, int h) {
        this.width = w;
        this.height = h;
        this.map = new Organism[h][w];
        this.queue = new ArrayList<>();
        this.toDelete = new ArrayList<>();
        this.allOrganisms = new ArrayList<>();
        this.commentator = new Commentator("Szymon Kasprzycki 193065");
        this.lastPressedKey = 0;
        this.initWorld();
        this.ui = new GUI(w, h);
    }

    public void initWorld() {
        for (int i = 0; i < this.height; i++) {
            for (int j = 0; j < this.width; j++) {
                this.map[i][j] = null;
            }
        }
    }

    public void destroyWorld() {
        this.queue.clear();
        this.toDelete.clear();
//        Human humanObject = this.ui.getPlayer();
        for (int i = 0; i < this.height; i++) {
            for (int j = 0; j < this.width; j++) {
                this.map[i][j] = null;
            }
        }
        for (Organism organism : this.allOrganisms) {
            if (organism.getType().equals("Human")) {
                continue;
            }
            organism.death();
            this.toDelete.add(organism);
        }
        for (Organism organism : this.toDelete) {
            this.allOrganisms.remove(organism);
        }

        this.toDelete.clear();
    }

    public void drawWorld() {
        this.ui.updateWorld(map);
        this.updateComments();
    }

    public void addOrganism(Organism organism) {
        if (!isOnMap(organism.getX(), organism.getY())) {
            return;
        }
        this.map[organism.getY()][organism.getX()] = organism;
        this.allOrganisms.add(organism);
    }

    public void removeOrganism(Organism organism) {
        this.map[organism.getY()][organism.getX()] = null;
        organism.death();
        toDelete.add(organism);
    }

    public void removeOrganism(int x, int y) {
        if (!isOnMap(x, y)) {
            return;
        }
        Organism organism = this.map[y][x];
        if (organism != null) {
            this.map[y][x] = null;
            organism.death();
            toDelete.add(organism);
        }
    }

    public void moveOrganism(Organism organism, int x, int y) {
        this.map[organism.getY()][organism.getX()] = null;
        organism.setX(x);
        organism.setY(y);
        this.map[y][x] = organism;
    }

    void makeMove(Organism organism, int x, int y) {
        Organism opponent = getOrganism(x, y);
        if (opponent != null) {
            Organism temp = opponent.collision(organism);
            if (temp == organism) {
                removeOrganism(opponent);
                moveOrganism(organism, x, y);
                if (opponent.getType().equals("Plant")) {
                    commentator.commentEat(organism, opponent);
                } else {
                    commentator.commentFight(organism, opponent, true);
                }
            } else if (temp == opponent) {
                removeOrganism(organism);
                commentator.commentFight(organism, opponent, false);
            } else {
                if (organism.getType().equals("Animal") && ((Animal)organism).isAntelope()) {
                    // In this case, antelope escaped from opponent
                    moveOrganism(organism, x, y);
                    commentator.comment("Antelope escaped from fight!");
                } else if (opponent.getSpecieName().equals("Turtle")) {
                    // In this case, turtle blocked opponent
                    if (temp == null) commentator.comment("Turtle blocked opponent!");
                }
            }
        } else {
            moveOrganism(organism, x, y);
        }
    }

    Organism getOrganism(int x, int y) {
        return map[y][x];
    }

    void makeTurn() {
        // Make turn for every organism, organism with higher initiative will move first
        // If two organisms have the same initiative, the one that was added to the world first will move first
        queue.clear();

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                Organism temp = getOrganism(j, i);
                if (temp != null) {
                    queue.add(temp);
                }
            }
        }

        // Sort queue
        queue.sort((o1, o2) -> {
            int initiative1 = o1.getInitiative();
            int initiative2 = o2.getInitiative();
            if (initiative1 > initiative2) {
                return -1;
            } else if (initiative1 < initiative2) {
                return 1;
            } else {
                int age1 = o1.getAge();
                int age2 = o2.getAge();
                return Integer.compare(age1, age2);
            }
        });

        // Main loop of action invoke
        for (Organism organism : queue) {
            if (organism != null && organism.isAlive() && !Objects.equals(organism.type, "Human")) {
                organism.action();
                // Update age of organism
                organism.setAge(organism.getAge() + 1);
            }
        }

        queue.clear();
        for (Organism organism : toDelete) {
            allOrganisms.remove(organism);
        }
        toDelete.clear();

        this.drawWorld();
    }

    void findFreeNeighbourCell(int x, int y, int[] newX, int[] newY) {
        int[] xPossible = new int[4];
        int[] yPossible = new int[4];
        int possibleMoves = 0;
        if (isOnMap(x - 1, y) && getOrganism(x - 1, y) == null) {
            xPossible[possibleMoves] = x - 1;
            yPossible[possibleMoves] = y;
            possibleMoves++;
        }
        if (isOnMap(x + 1, y) && getOrganism(x + 1, y) == null) {
            xPossible[possibleMoves] = x + 1;
            yPossible[possibleMoves] = y;
            possibleMoves++;
        }
        if (isOnMap(x, y - 1) && getOrganism(x, y - 1) == null) {
            xPossible[possibleMoves] = x;
            yPossible[possibleMoves] = y - 1;
            possibleMoves++;
        }
        if (isOnMap(x, y + 1) && getOrganism(x, y + 1) == null) {
            xPossible[possibleMoves] = x;
            yPossible[possibleMoves] = y + 1;
            possibleMoves++;
        }
        if (possibleMoves > 0) {
            int position = (int) (Math.random() * possibleMoves);
            newX[0] = xPossible[position];
            newY[0] = yPossible[position];
        } else {
            newX[0] = -1;
            newY[0] = -1;
        }
    }

    void MakeComment(String comment) {
        commentator.comment(comment);
    }

    void saveToFile(String fileName, Organism human) {
        try {
            FileWriter fileWriter = new FileWriter(fileName);
            PrintWriter printWriter = new PrintWriter(fileWriter);
            printWriter.printf("%d %d\n", this.width, this.height);
            // write commentator round
            printWriter.printf("%d\n", commentator.getCurrentRound());
            // write organisms amount
            printWriter.printf("%d\n", allOrganisms.size());
            for (Organism i : allOrganisms) {
                if (i.getSpecieName().equals("Human")) {
                    continue;
                }
                else
                    if (toDelete.contains(i)) continue;
                    printWriter.printf("%s %d %d %d %d %d\n", i.getSpecieName(), i.getX(), i.getY(), i.getStrength(), i.getInitiative(), i.getAge());
            }
            ((Human) human).saveToFile(printWriter);
            printWriter.close();
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    public Organism loadFromFile(String fileName) {
        try {
            File file = new File(fileName);
            Scanner scanner = new Scanner(file);
            Organism human = null;
            if (scanner.hasNext()) {
                destroyWorld();
                // read width and height
                width = scanner.nextInt();
                height = scanner.nextInt();
                initWorld();
                // read commentator round
                int commentatorRound = scanner.nextInt();
                commentator.setCurrentRound(commentatorRound);
                // read organisms
                int organismsAmount = scanner.nextInt();
                for (int z = 0; z < organismsAmount; z++) {
                    String specieName = scanner.next();
                    int x = scanner.nextInt();
                    int y = scanner.nextInt();
                    int strength = scanner.nextInt();
                    int initiative = scanner.nextInt();
                    int age = scanner.nextInt();
                    // Save human as special, because he is controlling main loop
                    if (specieName.equals("Human")) {
                        boolean isPowerActive = scanner.nextInt() > 0;
                        boolean isPowerOnCooldown = scanner.nextInt() > 0;
                        int powerCounter = scanner.nextInt();
                        int powerCooldownCounter = scanner.nextInt();
                        boolean endGame = scanner.nextInt() > 0;
                        human = createOrganism(specieName, x, y);
                        human.setStrength(strength);
                        human.setInitiative(initiative);
                        human.setAge(age);
                        ((Human)human).setPowerActive(isPowerActive);
                        ((Human)human).setPowerOnCooldown(isPowerOnCooldown);
                        ((Human)human).setPowerCounter(powerCounter);
                        ((Human)human).setPowerCooldownCounter(powerCooldownCounter);
                        ((Human)human).setEndGame(endGame);
                        continue;
                    }
                    Organism temp = createOrganism(specieName, x, y);
                    if (temp == null) continue;
                    temp.setAge(age);
                    temp.setStrength(strength);
                    temp.setInitiative(initiative);
                    addOrganism(temp);
                }
                scanner.close();
                System.out.println("File loaded");
                return human;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        System.out.println("File not found");
        return null;
    }

    public Organism createOrganism(String specieName, int x, int y) {
        return switch (specieName) {
            case "Antelope" -> new Antelope(x, y, this);
            case "Fox" -> new Fox(x, y, this);
            case "Sheep" -> new Sheep(x, y, this);
            case "Turtle" -> new Turtle(x, y, this);
            case "Wolf" -> new Wolf(x, y, this);
            case "Human" -> new Human(x, y, this);
            case "Grass" -> new Grass(x, y, this);
            case "Guarana" -> new Guarana(x, y, this);
            case "Belladonna" -> new Belladonna(x, y, this);
            case "SosnowskyHogweed" -> new SosnowskyHogweed(x, y, this);
            case "SowThistle" -> new SowThistle(x, y, this);
            default -> null;
        };
    }

    public void updateComments() {
        this.ui.showComments(commentator.getComments());
    }

    public GUI getUi() {
        return ui;
    }
}