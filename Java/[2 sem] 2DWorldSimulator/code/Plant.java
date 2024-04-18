import java.util.Random;

public class Plant extends Organism {
    private static final int DEFAULT_CHANCE_OF_MULTIPLY = 5;

    protected World world;
    protected int spreadChance;

    public Plant(int x, int y, World world, int strength, int initiative, char symbol, int age) {
        super(x, y, strength, initiative, symbol, age);
        this.type = "Plant";
        this.world = world;
        this.spreadChance = DEFAULT_CHANCE_OF_MULTIPLY;
    }

    @Override
    public void action() {
        if (new Random().nextInt(101) <= this.spreadChance) {
            multiply(this.x, this.y);
        }
    }

    protected void multiply(int x, int y) {
        int[] babyX = {x};
        int[] babyY = {y};
        // get random nearby position
        this.world.findFreeNeighbourCell(x, y, babyX, babyY);
        // if there is no free cell in the neighborhood, return
        if (babyX[0] == -1 || babyY[0] == -1) {
            return;
        }
        // create a new plant of the same type
        Organism baby = null;
        switch (this.symbol) {
            case '*' -> baby = new Grass(babyX[0], babyY[0], this.world);
            case '$' -> baby = new SosnowskyHogweed(babyX[0], babyY[0], this.world);
            case '^' -> baby = new Guarana(babyX[0], babyY[0], this.world);
            case '&' -> baby = new SowThistle(babyX[0], babyY[0], this.world);
            case '@' -> baby = new Belladonna(babyX[0], babyY[0], this.world);
            default -> {}
        }
        assert baby != null;
        this.world.addOrganism(baby);
    }

    @Override
    public Organism collision(Organism attacker) {
        if (attacker.getType().equals("Animal") || attacker.getType().equals("Human")) {
            return attacker;
        } else {
            return this;
        }
    }
}