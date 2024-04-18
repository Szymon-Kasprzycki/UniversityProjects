import java.util.Objects;
import java.util.Random;

public class Turtle extends Animal {
    private static final int TURTLE_STRENGTH = 2;
    private static final int TURTLE_INITIATIVE = 1;
    private static final char TURTLE_SYMBOL = 'T';
    private static final int STAY_CHANCE = 75;

    public Turtle(int x, int y, World world) {
        super(x, y, world, TURTLE_STRENGTH, TURTLE_INITIATIVE, TURTLE_SYMBOL, 0);
    }

    @Override
    public void action() {
        int stay = new Random().nextInt(101);
        if (stay > STAY_CHANCE) { super.action(); }
    }

    @Override
    public Organism collision(Organism attacker) {
        if (attacker.getType().equals("Animal") && Objects.equals(this.getSymbol(), attacker.getSymbol())) {
            this.multiply(this.getX(), this.getY());
            return new Turtle(0, 0, this.world);
        }
        if (attacker.getStrength() >= 5) {
            return attacker;
        } else {
            // attacker gets back to the previous position, so there's no need to return + move it
            return null;
        }
    }

    @Override
    public String getSpecieName() {
        return "Turtle";
    }
}