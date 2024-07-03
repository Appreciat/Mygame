package Control;

import Model.Game;
import Model.Player;
import View.GameFrame;

public class Control {
    private Game game = null;
    private GameFrame gameFrame = null;

    public GameFrame getGameFrame() {
        return gameFrame;
    }

    public void setGameFrame(GameFrame gameFrame) {
        this.gameFrame = gameFrame;
    }

    public Control(Game game){
        this.game = game;
    }

    public Game getGame() {
        return game;
    }

    public void setGame(Game game) {
        this.game = game;
    }

    public void PressButton(int clickCount){
        if(clickCount % 2 != 0){
            updateCash(game.getPlayer1());
            this.gameFrame.getPlayer1Label().setText(game.getPlayer1().getName() + "  金币" + game.getPlayer1().getCash());
            if(game.getPlayer1().getCash() <= 0) {
                gameOver(game.getPlayer2(),game.getPlayer1());
                this.gameFrame.getDiceButton().setEnabled(false);
            }
        } else {
            updateCash(game.getPlayer2());
            this.gameFrame.getPlayer2Label().setText(game.getPlayer2().getName() + "  金币" + game.getPlayer2().getCash());
            if(game.getPlayer2().getCash() <= 0){
                gameOver(game.getPlayer1(),game.getPlayer2());
                this.gameFrame.getDiceButton().setEnabled(false);
            }
        }
    }

    public void updateCash(Player player){
        int cash = player.getCash();
        int point = game.getDice().roll();
        player.setCash(cash - point*10);
    }

    public void gameOver(Player winner,Player loser){
        this.gameFrame.getPlayer1Label().setText(winner.getName() + "  赢!" + "   拥有金币：" + winner.getCash());
        this.gameFrame.getPlayer2Label().setText(loser.getName() + "  输!" + "   拥有金币" + loser.getCash());
    }
}
