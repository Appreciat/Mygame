package Model;

import java.util.List;

public class Game {
    private Dice dice;
    private Player player1;
    private Player player2;

    public Game(){
        initClass();
    }

    public void initClass(){
        dice = new Dice();
        player1 = new Player("player1",100);
        player2 = new Player("player2",100);
    }

    public Dice getDice() {
        return dice;
    }

    public void setDice(Dice dice) {
        this.dice = dice;
    }

    public Player getPlayer1() {
        return player1;
    }

    public void setPlayer1(Player player1) {
        this.player1 = player1;
    }

    public Player getPlayer2() {
        return player2;
    }

    public void setPlayer2(Player player2) {
        this.player2 = player2;
    }
}
