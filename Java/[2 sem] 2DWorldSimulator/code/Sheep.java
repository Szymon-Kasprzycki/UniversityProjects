public class Sheep extends Animal {
    private static final int SHEEP_STRENGTH = 4;
    private static final int SHEEP_INITIATIVE = 4;
    private static final char SHEEP_SYMBOL = 'S';

    public Sheep(int x, int y, World world) {
        super(x, y, world, SHEEP_STRENGTH, SHEEP_INITIATIVE, SHEEP_SYMBOL, 0);
    }

    @Override
    public boolean isSheep() {
        return true;
    }

    @Override
    public String getSpecieName() {
        return "Sheep";
    }
}