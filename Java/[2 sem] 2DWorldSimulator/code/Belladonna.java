public class Belladonna extends Plant {
    private static final int BELLADONNA_STRENGTH = 99;
    private static final int BELLADONNA_INITIATIVE = 0;
    private static final char BELLADONNA_SYMBOL = '@';

    public Belladonna(int x, int y, World world) {
        super(x, y, world, BELLADONNA_STRENGTH, BELLADONNA_INITIATIVE, BELLADONNA_SYMBOL, 0);
        this.spreadChance = 2; // 2% chance to spread
    }

    @Override
    public Organism collision(Organism attacker) {
        this.world.MakeComment("Belladonna killed " + attacker.getSpecieName());
        return this;
    }

    @Override
    public String getSpecieName() {
        return "Belladonna";
    }
}