public class SowThistle extends Plant {
    private static final int SOW_INITIATIVE = 0;
    private static final int SOW_STRENGTH = 0;
    private static final char SOW_SYMBOL = '&';

    public SowThistle(int x, int y, World world) {
        super(x, y, world, SOW_STRENGTH, SOW_INITIATIVE, SOW_SYMBOL, 0);
        this.spreadChance = 2;
    }

    @Override
    public void action() {
        for (int i = 0; i < 3; i++) {
            super.action();
        }
    }

    @Override
    public String getSpecieName() {
        return "SowThistle";
    }
}