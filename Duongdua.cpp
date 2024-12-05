// Duongdua.cpp

#include "pch.h"
#include "Duongdua.h"

Duongdua::Duongdua() : Hcn(), totalScrollDistance(0), scrolledDistance(0) {}

Duongdua::Duongdua(int x1, int y1, int x2, int y2)
    : Hcn(x1, y1, x2, y2), totalScrollDistance(2 * 300 * 100 * 50 ), scrolledDistance(0) {}

void Duongdua::draw(CPaintDC* pdc) {
    if (!pdc) return;

    // Vẽ hình chữ nhật đường đua 
    Hcn::draw(pdc);

    int midX = (x1 + x2) / 2;

    // Vẽ các làn đường
    CBrush lane1Brush(RGB(169, 169, 169));
    CBrush* oldBrush = pdc->SelectObject(&lane1Brush);
    pdc->Rectangle(x1, y1, midX, y2);

    CBrush lane2Brush(RGB(169, 169, 169));
    pdc->SelectObject(&lane2Brush);
    pdc->Rectangle(midX, y1, x2, y2);

    // Vẽ vạch phân cách giữa các làn đường bằng hình chữ nhật
    CBrush lineBrush(RGB(255, 255, 255));
    pdc->SelectObject(&lineBrush);
    pdc->FillSolidRect(x1, y1, x2 - x1, y2 - y1, RGB(169, 169, 169)); // Làm sạch với màu nền


    int dashHeight = 65; // Chiều cao 
    int dashWidth = 30;  // Độ rộng 
    int gap = 20;        // Khoảng cách giữa các nét đứt
    int segmentHeight = dashHeight + gap;

    // Tính vị trí bắt đầu cho vạch phân cách
    int startY = y1 - (laneLineOffset % segmentHeight);
    if (startY > y1) startY -= segmentHeight; // Đảm bảo bắt đầu từ đúng điểm trên màn hình

    for (int y = startY; y < y2; y += segmentHeight) {
        int rectTop = y;
        int rectBottom = min(y + dashHeight, y2); // Không vượt quá y2
        pdc->Rectangle(midX - dashWidth / 2, rectTop, midX + dashWidth / 2, rectBottom);
    }

    // Khôi phục bút và cọ cũ
    pdc->SelectObject(oldBrush);
}

void Duongdua::scroll(int speed) {
    totalElapsedTime += 1.0f; // Cập nhật tổng thời gian đã trôi qua (giả sử mỗi lần cuộn là 1 giây)

    if (totalElapsedTime >= 1.0f) {  // Mỗi  giây
        speedMultiplier += 0.003f;  // Tăng tốc độ từ từ mỗi giây
        totalElapsedTime = 0.0f;  // Đặt lại thời gian mỗi giây
    }


    // Áp dụng tỷ lệ tốc độ vào tốc độ cuộn
    int adjustedSpeed = static_cast<int>(speed * speedMultiplier);
    laneLineOffset -= adjustedSpeed; // Di chuyển vạch phân cách với tốc độ điều chỉnh

    y1 += speed;
    y2 += speed;
    scrolledDistance += speed;

    // Nếu vạch phân cách vượt quá chiều cao của một đoạn, đặt lại vị trí
    int dashHeight = 65; // Cùng kích thước như trong draw
    int gap = 20;
    int segmentHeight = dashHeight + gap;

    if (laneLineOffset >= segmentHeight) {
        laneLineOffset -= segmentHeight;
    }

    // Nếu đường đua cuộn hết màn hình, đặt lại vị trí
    if (y1 >= 5) {
        int height = y2 - y1;
        y1 = 0;
        y2 = height;
    }

    // Di chuyển tất cả các chướng ngại vật cùng với đường đua
    for (auto& obstacle : obstacles) {
        obstacle.scroll(adjustedSpeed);
    }
}

bool Duongdua::isComplete() const {
    return scrolledDistance >= totalScrollDistance;
}

void Duongdua::reset()
{
    obstacles.clear(); // Xóa tất cả chướng ngại vật
    // Thêm lại chướng ngại vật mặc định
    obstacles.push_back(ChuongngaiVat(rand() % (400 - 50), 50, rand() % (400 - 50) + 50, 100));
    obstacles.push_back(ChuongngaiVat(rand() % (400 - 50), 150, rand() % (400 - 50) + 50, 200));
    obstacles.push_back(ChuongngaiVat(rand() % (400 - 50), 250, rand() % (400 - 50) + 50, 300));
}

void Duongdua::addObstacle(const ChuongngaiVat& obstacle) {
    obstacles.push_back(obstacle);
}

const std::vector<ChuongngaiVat>& Duongdua::getObstacles() const {
    return obstacles;
}
