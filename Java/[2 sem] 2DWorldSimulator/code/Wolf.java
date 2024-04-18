public class Wolf extends Animal {
    private static final int WOLF_STRENGTH = 9;
    private static final int WOLF_INITIATIVE = 5;
    private static final char WOLF_SYMBOL = 'W';

    public Wolf(int x, int y, World world) {
        super(x, y, world, WOLF_STRENGTH, WOLF_INITIATIVE, WOLF_SYMBOL, 0);
    }

    @Override
    public boolean isWolf() {
        return true;
    }

    @Override
    public String getSpecieName() {
        return "Wolf";
    }
}
