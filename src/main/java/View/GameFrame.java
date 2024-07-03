package View;

import Control.Control;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GameFrame extends JFrame {
    private Control control;
    private JLabel player1Label;
    private JLabel player2Label;
    private JButton diceButton;
    private int clickCount = 0;

    public Control getControl() {
        return control;
    }

    public void setControl(Control control) {
        this.control = control;
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

    public JButton getDiceButton() {
        return diceButton;
    }

    public void setDiceButton(JButton diceButton) {
        this.diceButton = diceButton;
    }

    public int getClickCount() {
        return clickCount;
    }

    public void setClickCount(int clickCount) {
        this.clickCount = clickCount;
    }

    public GameFrame(Control control){
        this.control = control;
        this.setVisible(true);
        this.setResizable(false);
        this.setTitle("大富翁游戏");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(300,200);
        this.setLocationRelativeTo(null);//窗口在屏幕中间显示


        player1Label = new JLabel(control.getGame().getPlayer1().getName() + "  金币：" + control.getGame().getPlayer1().getCash());
        player2Label = new JLabel(control.getGame().getPlayer2().getName() + "  金币：" + control.getGame().getPlayer2().getCash());

        diceButton = new JButton("掷骰子");
        this.setLayout(new BorderLayout());
        JPanel playerPanel = new JPanel();

        diceButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                clickCount++;
                control.PressButton(clickCount);
            }
        });

        playerPanel.setLayout(new GridLayout(2, 1));
        playerPanel.add(player1Label);
        playerPanel.add(player2Label);
        this.add(playerPanel, BorderLayout.CENTER);
        this.add(diceButton, BorderLayout.SOUTH);
    }
}
