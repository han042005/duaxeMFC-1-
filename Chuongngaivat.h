#pragma once
#include "Hcn.h"

class ChuongngaiVat : public Hcn {
public:
    ChuongngaiVat();  // Khởi tạo mặc định
    ChuongngaiVat(int x1, int y1, int x2, int y2);  // Khởi tạo với tham số

    void draw(CPaintDC* pdc) const;  // Phương thức vẽ chướng ngại vật (const vì không thay đổi trạng thái của đối tượng)

    void move(int dx, int dy);  // Di chuyển chướng ngại vật
   
    void scroll(int speed);  // Di chuyển chướng ngại vật theo hướng cuộn của đường đua
    bool checkCollision(int xex1, int xey1, int xex2, int xey2)const ;
};
