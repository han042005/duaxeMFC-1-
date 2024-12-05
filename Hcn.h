#pragma once

class Hcn
{
public:
    int x1, y1, x2, y2;

    Hcn();
    Hcn(int x1, int y1, int x2, int y2);
    void setHcn(int x1, int y1, int x2, int y2);
    void draw(CPaintDC* dc);
    void draw(CClientDC* dc);
    int getX1() const { return x1; }
    int getX2() const { return x2; }
    int getY1() const { return y1; }
    int getY2() const { return y2; }
};