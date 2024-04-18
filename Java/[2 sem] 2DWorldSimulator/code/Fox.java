import java.util.Objects;
import java.util.Random;

public class Fox extends Animal {
    private static final int FOX_STRENGTH = 3;
    private static final int FOX_INITIATIVE = 7;
    private static final char FOX_SYMBOL = 'F';

    public Fox(int x, int y, World world) {
        super(x, y, world, FOX_STRENGTH, FOX_INITIATIVE, FOX_SYMBOL, 0);
    }

    @Override
    public boolean isFox() {
        return true;
    }

    @Override
    public void action() {
        int newX = this.getX();
        int newY = this.getY();
        Organism occupant;
        int tries = 0;
        do {
            int direction = new Random().nextInt(4);
            switch (direction) {
                case 0 -> newX++;
                case 1 -> newX--;
                case 2 -> newY++;
                case 3 -> newY--;
            }
            if (!this.world.isOnMap(newX, newY)) {
                newX = this.getX();
                newY = this.getY();
                tries++;
                continue;
            }
            occupant = this.world.getOrganism(newX, newY);
            if (occupant == null || occupant.getStrength() <= this.getStrength() || Objects.equals(occupant.getSymbol(), this.getSymbol())) {
                break;
            }
            else {
                newX = this.getX();
                newY = this.getY();
                tries++;
            }
        } while (tries < 8);

        if (tries == 8) { return; }
        this.world.makeMove(this, newX, newY);
    }

    @Override
    public String getSpecieName() {
        return "Fox";
    }
}