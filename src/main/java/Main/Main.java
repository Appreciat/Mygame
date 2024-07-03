package Main;

import Control.Control;
import Model.Game;
import View.GameFrame;

public class Main {
    public static void main(String[] args) {
       new Main();
    }
    public Main(){
        startGame();
    }
    public void startGame(){
        Game game = new Game();
        Control control = new Control(game);
        GameFrame gameFrame = new GameFrame(control);

        control.setGameFrame(gameFrame); //保证控制器和视图是相互持有的状态
    }
}
