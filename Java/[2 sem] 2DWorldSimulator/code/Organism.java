public abstract class Organism implements Creature {
    protected int x;
    protected int y;
    protected int strength;
    protected int initiative;
    protected int age;
    protected char symbol;
    protected String type;
    protected boolean alive;

    public Organism(int x, int y, int strength, int initiative, char symbol, int age) {
        this.x = x;
        this.y = y;
        this.strength = strength;
        this.initiative = initiative;
        this.age = age;
        this.symbol = symbol;
        this.type = "Organism";
        this.alive = true;
    }

    public void death() {
        this.alive = false;
    }

    public boolean isAlive() {
        return this.alive;
    }

    public int getX() {
        return this.x;
    }

    public int getY() {
        return this.y;
    }

    public int getStrength() {
        return this.strength;
    }

    public int getInitiative() {
        return this.initiative;
    }

    public int getAge() {
        return this.age;
    }

    public String getSymbol() {
        return Character.toString(this.symbol);
    }

    public String getType() {
        return this.type;
    }

    public void setX(int newX) {
        this.x = newX;
    }

    public void setY(int newY) {
        this.y = newY;
    }

    public void setStrength(int newStrength) {
        this.strength = newStrength;
    }

    public void setInitiative(int newInitiative) {
        this.initiative = newInitiative;
    }

    public void setAge(int newAge) {
        this.age = newAge;
    }

    public void setSymbol(char newSymbol) {
        this.symbol = newSymbol;
    }
}