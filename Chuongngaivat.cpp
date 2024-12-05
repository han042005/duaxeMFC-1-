#include "pch.h"
#include "ChuongngaiVat.h"
#include <cstdlib>  // Thêm thư viện này để sử dụng rand()
#include <ctime>    // Thêm thư viện này để khởi tạo seed cho rand()

ChuongngaiVat::ChuongngaiVat() : Hcn() {
    srand(time(0)); // Khởi tạo seed cho rand()
}

ChuongngaiVat::ChuongngaiVat(int x1, int y1, int x2, int y2) : Hcn(x1, y1, x2, y2) {
    srand(time(0)); // Khởi tạo seed cho rand()
}

void ChuongngaiVat::draw(CPaintDC* pdc) const {
    if (!pdc) return;

    // Vẽ chướng ngại vật
    CBrush obstacleBrush(RGB(57, 255, 20)); // Màu xanh cho chướng ngại vật
    CBrush* oldBrush = pdc->SelectObject(&obstacleBrush);
    pdc->Rectangle(x1, y1, x2, y2);  // Vẽ hình chữ nhật đại diện cho chướng ngại vật
    pdc->SelectObject(oldBrush); // Phục hồi cọ cũ
}

// Di chuyển chướng ngại vật theo hướng (dx, dy)
void ChuongngaiVat::move(int dx, int dy) {
    x1 += dx;
    y1 += dy;
    x2 += dx;
    y2 += dy;
}

void ChuongngaiVat::scroll(int speed) {
    // Di chuyển chướng ngại vật theo hướng cuộn của đường đua
    y1 += speed;
    y2 += speed;

    int screenHeight = 600;  // Chiều cao màn hình giả định
    int screenWidth = 400;   // Chiều rộng của đường đua
    int obstacleWidth = 50;  // Chiều rộng chướng ngại vật giả định
    int obstacleHeight = y2 - y1;  // Chiều cao chướng ngại vật

    // Kiểm tra xem chướng ngại vật có ra ngoài phạm vi của đường đua không
    if (y1 >= screenHeight) {
        // Đưa chướng ngại vật trở lại phía trên
        y1 = 0;
        y2 = y1 + obstacleHeight;
        // Giới hạn vị trí tạo chướng ngại vật
        int screenHeight = 600;  // Chiều cao của đường đua
        int screenWidth = 400;   // Chiều rộng của đường đua
        int obstacleWidth = 50;  // Chiều rộng của chướng ngại vật
        int obstacleHeight = 30; // Chiều cao của chướng ngại vật

        // Đảm bảo vị trí x ngẫu nhiên trong phạm vi của đường đua
        int newX1 = rand() % (screenWidth - obstacleWidth);  // Giới hạn x sao cho chướng ngại vật không ra ngoài màn hình
        int newX2 = newX1 + obstacleWidth;  // Giữ chiều rộng của chướng ngại vật là 50

        // Cập nhật lại vị trí của chướng ngại vật
        x1 = newX1;
        x2 = newX2;
    }
}

bool ChuongngaiVat::checkCollision(int xex1, int xey1, int xex2, int xey2)const
{
    return !(xex2 <= x1 || xex1 >= x2 || xey2 <= y1 || xey1 >= y2);
}

