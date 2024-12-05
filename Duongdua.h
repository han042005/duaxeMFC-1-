// Duongdua.h

#pragma once
#include "ChuongngaiVat.h"
#include <vector>

class Duongdua : public Hcn {
public:
    Duongdua();
    Duongdua(int x1, int y1, int x2, int y2);

    void draw(CPaintDC* pdc);
    void scroll(int speed);
    bool isComplete() const;
    void reset(); // Thêm khai báo phương thức

    void addObstacle(const ChuongngaiVat& obstacle);
    const std::vector<ChuongngaiVat>& getObstacles() const;  // Phương thức truy xuất danh sách chướng ngại vật

private:
    std::vector<ChuongngaiVat> obstacles;  // Danh sách chướng ngại vật
    int totalScrollDistance;
    int scrolledDistance;
    int laneLineOffset;  // Vị trí bắt đầu của vạch phân cách
    int elapsedTime;     // Biến lưu thời gian đã trôi qua
    float speedMultiplier = 1.0f;  // Tỷ lệ tốc độ ban đầu
    float totalElapsedTime = 0.0f; // Tổng thời gian đã trôi qua tính bằng giây
};
