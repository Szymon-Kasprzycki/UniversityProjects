public class Grass extends Plant {
    private static final int GRASS_STRENGTH = 0;
    private static final int GRASS_INITIATIVE = 0;
    private static final char GRASS_SYMBOL = '*';

    public Grass(int x, int y, World world) {
        super(x, y, world, GRASS_STRENGTH, GRASS_INITIATIVE, GRASS_SYMBOL,0);
    }

    @Override
    public String getSpecieName() {
        return "Grass";
    }
}
