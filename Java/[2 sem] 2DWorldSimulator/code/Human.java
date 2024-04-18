import java.io.IOException;
import java.io.OutputStream;
import java.awt.event.KeyEvent;
import java.io.PrintWriter;

public class Human extends Animal {
    private int powerCounter;
    private int powerCooldownCounter;
    private boolean isPowerActive;
    private boolean isPowerOnCooldown;
    private boolean endGame;
    public Human(int x, int y, World world) {
        super(x, y, world, 5, 4, 'H', 0);
        this.type = "Human";
        this.powerCounter = 0;
        this.powerCooldownCounter = 0;
        this.isPowerActive = false;
        this.isPowerOnCooldown = false;
    }

    @Override
    public void action() {
        this.world.commentator.newRound();
        int newX = this.getX();
        int newY = this.getY();
        switch (world.getUi().lastPressedKey) {
            case KeyEvent.VK_UP -> newY--;
            case KeyEvent.VK_LEFT -> newX--;
            case KeyEvent.VK_DOWN -> newY++;
            case KeyEvent.VK_RIGHT -> newX++;
            default -> {}
        }
        if (!this.world.isOnMap(newX, newY)) { return; }
        this.world.makeMove(this, newX, newY);
        this.powerTick();
        this.world.makeTurn();
    }

    private void powerCooldownTick() {
        this.powerCooldownCounter++;
        int HUMAN_POWER_COOLDOWN = 5;
        this.world.MakeComment("Human special power cooldown: " + (HUMAN_POWER_COOLDOWN - this.powerCooldownCounter));
        if (this.powerCooldownCounter >= HUMAN_POWER_COOLDOWN) {
            this.powerCooldownCounter = 0;
            this.isPowerOnCooldown = false;
        }
    }

    private void powerDurationTick() {
        this.powerCounter++;
        int HUMAN_POWER_DURATION = 5;
        this.world.MakeComment("Human special power duration: " + (HUMAN_POWER_DURATION - this.powerCounter));
        this.setStrength(this.getStrength() - 1);
        if (this.powerCounter >= HUMAN_POWER_DURATION) {
            this.powerCounter = 0;
            this.isPowerActive = false;
            this.isPowerOnCooldown = true;
        }
    }

    public void powerTick() {
        if (this.isPowerActive) { this.powerDurationTick(); }
        else if (this.isPowerOnCooldown) { this.powerCooldownTick(); }
    }

    public void usePower() {
        if (!this.isPowerActive && !this.isPowerOnCooldown) {
            // chosen power is magical potion that increases strength by 5 and each turn decreases it by 1
            this.isPowerActive = true;
            int HUMAN_POWER = 5;
            this.setStrength(this.getStrength() + HUMAN_POWER);
            this.world.MakeComment("Human used magical potion. Strength increased by 5.");
        }
    }

    public boolean isEndGame() {
        return this.endGame;
    }

    public void endGame() {
        this.endGame = true;
        this.world.updateComments();
        this.world.getUi().showGameOver();
        this.world.getUi().endGame();
    }

    public void death() {
        this.alive = false;
        this.endGame();
    }

    public String getSpecieName() {
        return "Human";
    }

    public void saveToFile(PrintWriter file) throws IOException {
        file.printf("%s %d %d %d %d %d %d %d %d %d %d%n",
                this.getSpecieName(),
                this.x,
                this.y,
                this.getStrength(),
                this.getInitiative(),
                this.getAge(),
                this.isPowerActive ? 1 : 0,
                this.isPowerOnCooldown ? 1 : 0,
                this.powerCounter,
                this.powerCooldownCounter,
                this.endGame ? 1 : 0);
    }

    public void setPowerActive(boolean nIsPowerActive) {
        this.isPowerActive = nIsPowerActive;
    }

    public void setPowerOnCooldown(boolean nIsPowerOnCooldown) {
        this.isPowerOnCooldown = nIsPowerOnCooldown;
    }

    public void setPowerCounter(int nPowerCounter) {
        this.powerCounter = nPowerCounter;
    }

    public void setPowerCooldownCounter(int nPowerCooldownCounter) {
        this.powerCooldownCounter = nPowerCooldownCounter;
    }

    public void setEndGame(boolean nEndGame) {
        this.endGame = nEndGame;
    }

    public void setupFromFile(String filePath) {
        Human loadedHuman = (Human) this.world.loadFromFile(filePath);
        this.setX(loadedHuman.getX());
        this.setY(loadedHuman.getY());
        this.setStrength(loadedHuman.getStrength());
        this.setInitiative(loadedHuman.getInitiative());
        this.setAge(loadedHuman.getAge());
        this.powerCounter = loadedHuman.powerCounter;
        this.powerCooldownCounter = loadedHuman.powerCooldownCounter;
        this.isPowerActive = loadedHuman.isPowerActive;
        this.isPowerOnCooldown = loadedHuman.isPowerOnCooldown;
        this.setEndGame(loadedHuman.isEndGame());
        this.world.moveOrganism(this, this.getX(), this.getY());
        this.world.drawWorld();
    }
}