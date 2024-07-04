import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GameFrame extends JFrame {
    private JLabel player1Label;
    private JLabel player2Label;
    private JPanel playerPanel;
    private JButton diceButton;
    private Dice dice = new Dice();
    private Player player1 = new Player("玩家1",100);
    private Player player2 = new Player("玩家2",100);
    private int clickCount = 0;

    GameFrame(){
        this.setTitle("大富翁游戏");
        this.setVisible(true);
        this.setResizable(false);
        this.setTitle("大富翁游戏");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(300,150);
        this.setLayout(new BorderLayout());
        this.setLocationRelativeTo(null);//窗口在屏幕中间显示

        player1Label = new JLabel();
        player2Label = new JLabel();
        playerPanel = new JPanel();
        diceButton = new JButton();

        this.player1Label.setText(player1.getName() + "  拥有金币" + player1.getCash());
        this.player2Label.setText(player2.getName() + "  拥有金币" + player2.getCash());
        playerPanel.setLayout(new GridLayout(2, 1));

        playerPanel.add(player1Label);
        playerPanel.add(player2Label);
        diceButton.setText("掷骰子");

        diceButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                clickCount++;
                PressButton(clickCount);
            }
        });

        this.add(playerPanel, BorderLayout.CENTER);
        this.add(diceButton, BorderLayout.SOUTH);
    }

    public JLabel getPlayer1Label() {
        return player1Label;
    }

    public void setPlayer1Label(JLabel player1Label) {
        this.player1Label = player1Label;
    }

    public JLabel getPlayer2Label() {
        return player2Label;
    }

    public void setPlayer2Label(JLabel player2Label) {
        this.player2Label = player2Label;
    }

    public JPanel getPlayerPanel() {
        return playerPanel;
    }

    public void setPlayerPanel(JPanel playerPanel) {
        this.playerPanel = playerPanel;
    }

    public JButton getDiceButton() {
        return diceButton;
    }

    public void setDiceButton(JButton diceButton) {
        this.diceButton = diceButton;
    }

    public static void main(String[] args) {
       GameFrame gameFrame = new GameFrame();
    }

    protected void updateCash(Player player){
        int cash = player.getCash();
        int point = this.dice.roll();
        player.setCash(cash - point*10);
    }

    public void gameOver(Player winner,Player loser){
        this.getPlayer1Label().setText(winner.getName() + "  赢!" + "   拥有金币：" + winner.getCash());
        this.getPlayer2Label().setText(loser.getName() + "  输!" + "   拥有金币" + loser.getCash());
    }

    public void PressButton(int clickCount) {
        if(clickCount % 2 != 0){
            updateCash(player1);
            this.getPlayer1Label().setText(player1.getName() + "  拥有金币" + player1.getCash());
            if(player1.getCash() <= 0) {
                gameOver(player2 , player1);
                this.diceButton.setEnabled(false);
            }
        } else {
            updateCash(player2);
            this.getPlayer2Label().setText(player2.getName() + "  拥有金币" + player2.getCash());
            if(player2.getCash() <= 0){
                gameOver(player1 , player2);
                this.diceButton.setEnabled(false);
            }
        }
    }
}
