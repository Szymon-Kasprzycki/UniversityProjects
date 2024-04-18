import java.util.Objects;
import java.util.Random;

public class Animal extends Organism {
    protected final World world;

    public Animal(int x, int y, World world, int strength, int initiative, char symbol, int age) {
        super(x, y, strength, initiative, symbol, age);
        this.world = world;
        this.type = "Animal";
    }

    public void move(int x, int y) {
        this.world.moveOrganism(this, x, y);
    }

    @Override
    public void action() {
        // Antelope has a chance to move twice as far
        int step = (this.symbol == 'A') ? 2 : 1;

        int newX = this.x;
        int newY = this.y;
        int direction = new Random().nextInt(4);
        switch (direction) {
            case 0 -> newX += step;
            case 1 -> newX -= step;
            case 2 -> newY += step;
            case 3 -> newY -= step;
            default -> {}
        }

        if (world.isOnMap(newX, newY)) {
            this.world.makeMove(this, newX, newY);
        } else {
            this.action();
        }
    }

    // Function checks collision and returns pointer to the winner or null if organisms multiply
    // When used, the pointer returned by this function should be used to set the pointer in the world to the winner
    @Override
    public Organism collision(Organism attacker) {
        if (attacker.getType().equals("Animal") && Objects.equals(this.getSymbol(), attacker.getSymbol())) {
            if (attacker.getAge() < 3 || this.getAge() < 3) { return null; }
            this.multiply(this.x, this.y);
            return null;
        } else if (attacker.getStrength() < this.strength) {
            return this;
        } else {
            return attacker;
        }
    }

    public void multiply(int x, int y) {
        int[] babyX = new int[1];
        int[] babyY = new int[1];

        // get random nearby position
        this.world.findFreeNeighbourCell(x, y, babyX, babyY);

        if (babyY[0] == -1 || babyX[0] == -1) return;

        Organism baby = switch (symbol) {
            case 'W' -> new Wolf(babyX[0], babyY[0], this.world);
            case 'S' -> new Sheep(babyX[0], babyY[0], this.world);
            case 'F' -> new Fox(babyX[0], babyY[0], this.world);
            case 'T' -> new Turtle(babyX[0], babyY[0], this.world);
            case 'A' -> new Antelope(babyX[0], babyY[0], this.world);
            default -> null;
        };

        this.world.MakeComment(this.getSpecieName() + " multiplied!");
        if (baby != null) this.world.addOrganism(baby);
    }

    public boolean isWolf() {
        return false;
    }

    public boolean isSheep() {
        return false;
    }

    public boolean isFox() {
        return false;
    }

    public boolean isAntelope() {
        return false;
    }

    @Override
    public String getSpecieName() {
        return "Animal";
    }
}