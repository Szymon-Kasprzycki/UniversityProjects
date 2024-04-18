
public class Main {
    public static void main(String[] args) {
        World game = new World(20, 20);
        Human player = new Human(11,11,game);
        game.addOrganism(player);
//        game.addOrganism(new Wolf(10,10,game));
//        game.addOrganism(new Wolf(10,11,game));
//        game.addOrganism(new Wolf(10,12,game));
//        game.addOrganism(new Wolf(11,10,game));
//        game.addOrganism(new Wolf(11,12,game));
//        game.addOrganism(new Wolf(12,10,game));
//        game.addOrganism(new Wolf(12,11,game));
//        game.addOrganism(new Wolf(12,12,game));
//        game.addOrganism(new Fox(5,2,game));
//        game.addOrganism(new Sheep(3,3,game));
        game.addOrganism(new Turtle(4,4,game));
        game.addOrganism(new Turtle(4,5,game));
        game.addOrganism(new Turtle(4,6,game));
        game.addOrganism(new Turtle(4,7,game));
        game.addOrganism(new Turtle(4,8,game));
        game.addOrganism(new Turtle(4,9,game));
        game.addOrganism(new Turtle(4,10,game));
//        game.addOrganism(new Antelope(5,5,game));
//        game.addOrganism(new Grass(6,6,game));
        game.addOrganism(new SowThistle(7,7,game));
        game.addOrganism(new Guarana(8,8,game));

        game.getUi().setPlayer(player);
        game.drawWorld();
    }
}

