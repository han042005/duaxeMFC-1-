#include "pch.h"
#include "xe.h"
#include "vector"

// Constructor mặc định
xe::xe() : Hcn(), mauxe(RGB(255, 255, 255)), tocdo(5) {}

// Constructor với tham số
xe::xe(int x1, int y1, int x2, int y2, COLORREF mauxe, int tocdo)
    : Hcn(x1, y1, x2, y2), mauxe(mauxe), tocdo(tocdo) {
    loadImage(_T("C:\\Users\\ADMIN\\Downloads\\Remove-bg.ai_1732717256696.png"));  // Tải hình ảnh của xe từ file
}

// Phương thức setX di chuyển xe và kiểm tra phạm vi của đường đua
void xe::setX(int newX1, int newX2, int roadLeft, int roadRight)
{
    if (newX1 >= roadLeft && newX2 <= roadRight) {
        x1 = newX1;
        x2 = newX2;
    }
}

// Getter cho x1
int xe::getX1() const { return x1; }

// Getter cho x2
int xe::getX2() const { return x2; }

// Setter cho màu xe
void xe::setmauxe(COLORREF mauxe) {
    this->mauxe = mauxe;
}

// Setter cho tốc độ xe
void xe::settocdo(int tocdo) {
    if (tocdo > 0) {  // Đảm bảo tốc độ dương
        this->tocdo = tocdo / 2;  // Giảm tốc độ đi 2 lần
    }
    else {
        this->tocdo = tocdo;  // Tốc độ âm hoặc bằng 0 giữ nguyên
    }
}

// Phương thức vẽ xe
void xe::drawPaint(CPaintDC* pdc)
{
    /// Kiểm tra xem hình ảnh có được tải thành công không
    if (!m_imgXe.IsNull()) {
        // Điều chỉnh kích thước ảnh nếu cần, hoặc vẽ nó theo kích thước mặc định
        int imgWidth = m_imgXe.GetWidth();
        int imgHeight = m_imgXe.GetHeight();

        // Điều chỉnh tỷ lệ hình ảnh để phù hợp với kích thước của xe
        int newWidth = x2 - x1;
        int newHeight = y2 - y1;

        // Vẽ hình ảnh lên màn hình với kích thước mới
        m_imgXe.Draw(pdc->m_hDC, x1, y1, newWidth, newHeight);
    }
    else {
        // Nếu không có hình ảnh, vẽ hình chữ nhật (trường hợp mặc định)
        CBrush brush(mauxe);
        CBrush* oldBrush = pdc->SelectObject(&brush);
        pdc->Rectangle(x1, y1, x2, y2);
        pdc->SelectObject(oldBrush);
    }
}

void xe::setPosition(int x1, int y1)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x1 + (this->x2 - this->x1); // Giữ nguyên chiều rộng của xe
    this->y2 = y1 + (this->y2 - this->y1); // Giữ nguyên chiều cao của xe
}

// Phương thức di chuyển xe tự động theo chiều dọc
void xe::move()
{
    y1 -= tocdo / 2;  // Di chuyển xe lên
    y2 -= tocdo / 2;

    // Nếu xe đi ra ngoài màn hình, đưa xe về lại đầu màn hình
    if (y1 < 500) {  // Giả sử chiều cao màn hình là 600px
        y1 = 400;  // Đưa xe trở lại từ trên cùng
        y2 = y1 + 50;  // Cập nhật chiều dài xe
    }
}
bool xe::loadImage(LPCTSTR szFilePath) {
    // Tải hình ảnh từ file
    HRESULT hr = m_imgXe.Load(szFilePath);
    if (FAILED(hr)) {
        AfxMessageBox(_T("Không thể tải hình ảnh!"));
        return false;
    }
    return true;
}
