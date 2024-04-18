public class SosnowskyHogweed extends Plant {
    private static final int SOSNOWSKY_HOGWEED_STRENGTH = 10;
    private static final int SOSNOWSKY_HOGWEED_INITIATIVE = 0;
    private static final char SOSNOWSKY_HOGWEED_SYMBOL = '$';

    public SosnowskyHogweed(int x, int y, World world) {
        super(x, y, world, SOSNOWSKY_HOGWEED_STRENGTH, SOSNOWSKY_HOGWEED_INITIATIVE, SOSNOWSKY_HOGWEED_SYMBOL, 0);
        this.spreadChance = 3; // 3% chance to spread
    }

    @Override
    public Organism collision(Organism attacker) {
        return this;
    }

    @Override
    public void action() {
        int[] x = {getX() - 1, getX() + 1, getX(), getX()};
        int[] y = {getY(), getY(), getY() + 1, getY() - 1};

        for (int i = 0; i < 4; i++) {
            if (!this.world.isOnMap(x[i], y[i])) continue;
            Organism occupant = world.getOrganism(x[i], y[i]);
            if (occupant != null && !occupant.getType().equals("Plant")) {
                world.MakeComment(getSpecieName() + " killed " + occupant.getSpecieName());
                world.removeOrganism(x[i], y[i]);
            }
        }

        // Spreading chance
        super.action();
    }

    @Override
    public String getSpecieName() {
        return "SosnowskyHogweed";
    }
}