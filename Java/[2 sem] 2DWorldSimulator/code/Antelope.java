import java.util.Random;

public class Antelope extends Animal {
    private static final int ANTELOPE_STRENGTH = 4;
    private static final int ANTELOPE_INITIATIVE = 4;
    private static final char ANTELOPE_SYMBOL = 'A';
    private static final int CHANCE_OF_ESCAPE = 50;

    public Antelope(int x, int y, World world) {
        super(x, y, world, ANTELOPE_STRENGTH, ANTELOPE_INITIATIVE, ANTELOPE_SYMBOL, 0);
    }

    @Override
    public Organism collision(Organism attacker) {
        int chance = new Random().nextInt(101);
        if (chance <= CHANCE_OF_ESCAPE) {
            int[] moveX = new int[1];
            int[] moveY = new int[1];
            this.world.findFreeNeighbourCell(this.getX(), this.getY(), moveX, moveY);
            if (moveX[0] != -1 && moveY[0] != -1) {
                this.world.moveOrganism(this, moveX[0], moveY[0]);
            }
            // return attacker but does not remove antelope
            return null;
        } else {
            return super.collision(attacker);
        }
    }

    @Override
    public boolean isAntelope() {
        return true;
    }

    @Override
    public String getSpecieName() {
        return "Antelope";
    }
}