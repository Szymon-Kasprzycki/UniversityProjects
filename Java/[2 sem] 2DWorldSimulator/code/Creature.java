public interface Creature {
    Organism collision(Organism attacker);
    void action();
    void death();
    boolean isAlive();
    int getX();
    int getY();
    int getStrength();
    int getInitiative();
    int getAge();
    String getSymbol();
    String getType();
    void setX(int newX);
    void setY(int newY);
    void setStrength(int newStrength);
    void setInitiative(int newInitiative);
    void setAge(int newAge);
    void setSymbol(char newSymbol);
    default String getSpecieName() {
        return "Organism";
    }
}