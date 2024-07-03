package View.UI;

import javax.swing.*;
import java.awt.*;

public abstract class Layer extends JPanel {
    /*
    * 窗口左上角的坐标
    * */
    protected int x;
    protected int y;

    /*
    * 窗口的高度与宽度
    * */
    protected int w;
    protected int h;

    protected Layer(int x,int y,int w,int h){
        this.setBounds(x, y, w, h);
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
    }

    public void setLocation(int x,int y){
        this.x = x;
        this.y = y;
    }

    @Override
    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    @Override
    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getW() {
        return w;
    }

    public void setW(int w) {
        this.w = w;
    }

    public int getH() {
        return h;
    }

    public void setH(int h) {
        this.h = h;
    }

    abstract public void paint(Graphics g);
    abstract public void startPanel();
}
