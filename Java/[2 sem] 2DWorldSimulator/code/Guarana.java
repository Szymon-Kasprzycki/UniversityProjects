public class Guarana extends Plant {
    private static final int GUARANA_STRENGTH = 0;
    private static final int GUARANA_INITIATIVE = 0;
    private static final char GUARANA_SYMBOL = '^';

    public Guarana(int x, int y, World world) {
        super(x, y, world, GUARANA_STRENGTH, GUARANA_INITIATIVE, GUARANA_SYMBOL, 0);
    }

    @Override
    public Organism collision(Organism attacker) {
        attacker.setStrength(attacker.getStrength() + 3);
        return attacker;
    }

    @Override
    public String getSpecieName() {
        return "Guarana";
    }
}