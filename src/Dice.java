import java.util.Random;

public class Dice {
    private int Point;
    private Random random;

    public Dice(){
        random = new Random();
    }

    public int roll(){
        Point = random.nextInt(6) + 1;
        return this.Point;
    }

    public int getPoint() {
        return Point;
    }

    public void setPoint(int point) {
        Point = point;
    }

    public Random getRandom() {
        return random;
    }

    public void setRandom(Random random) {
        this.random = random;
    }
}
