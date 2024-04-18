import java.util.ArrayList;
import java.util.List;

public class Commentator {
    public final ArrayList<String> comments;
    private int currentRound;
    public int currentRoundComments;
    private final String author;
    private static final int MAX_COMMENTS_PER_ROUND = 20;

    public Commentator(String author) {
        this.comments = new ArrayList<>();
        this.currentRound = 0;
        this.currentRoundComments = 0;
        this.author = author;
    }

    public void comment(String comment) {
        if (currentRoundComments >= MAX_COMMENTS_PER_ROUND) {return;}
        comments.add(comment);
        currentRoundComments++;
    }

    public void newRound() {
        comments.clear();
        currentRoundComments = 0;
        currentRound++;
        comments.add("Round " + currentRound);
    }

    public void commentFight(Organism attacker, Organism defender, boolean won) {
        String comment = attacker.getSpecieName() + " attacked " + defender.getSpecieName() + " and ";
        if (won) {
            comment += "won";
        } else {
            comment += "lost";
        }
        this.comment(comment);
    }

    public void commentEat(Organism eater, Organism eaten) {
        String comment = eater.getSpecieName() + " ate " + eaten.getSpecieName();
        this.comment(comment);
    }

    public int getCurrentRound() {
        return currentRound;
    }

    public void setCurrentRound(int newCurrentRound) {
        currentRound = newCurrentRound;
        comments.clear();
        comments.add("Round " + currentRound);
        currentRoundComments = 1;
    }

    public ArrayList<String> getComments() {
        return comments;
    }
}
