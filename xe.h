#pragma once
#include "Hcn.h"
#include "afx.h"

class xe : public Hcn {
private:
    COLORREF mauxe;  // Màu xe
    int tocdo;       // Tốc độ di chuyển của xe
    CImage m_imgXe;        // Đối tượng CImage chứa hình ảnh của xe
public:
    xe();  // Constructor mặc định
    xe(int x1, int y1, int x2, int y2, COLORREF mauxe, int tocdo);  // Constructor với tham số

    void setX(int newX1, int newX2, int roadLeft, int roadRight);  // Di chuyển xe ngang
    int getX1() const;  // Getter cho x1
    int getX2() const;  // Getter cho x2
    void setmauxe(COLORREF mauxe);  // Setter cho màu xe
    void settocdo(int tocdo);  // Setter cho tốc độ
    void drawPaint(CPaintDC* pdc);  // Phương thức vẽ xe
    void setPosition(int x1, int y1);  // Đặt lại vị trí xe
    void move();  // Di chuyển xe theo chiều dọc
    bool loadImage(LPCTSTR szFilePath);  // Tải hình ảnh từ file
};
