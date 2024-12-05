#pragma once
#include "Duongdua.h"      // Bao gồm lớp Duongdua để sử dụng đường đua
#include "Xe.h"             // Bao gồm lớp Xe để điều khiển đối tượng xe
#include "ChuongngaiVat.h"  // Bao gồm lớp ChuongngaiVat để chướng ngại vật

class CChildView : public CWnd {
public:
    CChildView();  // Constructor khởi tạo đối tượng

protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs); // Phương thức tạo cửa sổ, điều chỉnh các thuộc tính của cửa sổ

public:
    virtual ~CChildView(); // Destructor

protected:
    
    afx_msg void OnPaint();  // Phương thức vẽ các đối tượng (đường đua, xe, chướng ngại vật)
    afx_msg void OnTimer(UINT_PTR nIDEvent); // Xử lý sự kiện timer, cập nhật game
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags); // Xử lý sự kiện bàn phím
    afx_msg void OnSetFocus(CWnd* pOldWnd); // Xử lý khi cửa sổ nhận được tiêu điểm
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct); // Xử lý khi cửa sổ được tạo
    afx_msg void OnStartButtonClicked(); // Xử lý sự kiện nhấn nút "Bắt đầu"
    DECLARE_MESSAGE_MAP() // Macro xử lý các sự kiện

private:
    Duongdua d1;                // Đối tượng đường đua
    xe xe1;                      // Đối tượng xe
    ChuongngaiVat obstacle;      // Đối tượng chướng ngại vật
    bool gameComplete;          // Biến trạng thái game
    bool dung = false;
    CButton startButton; // Nút Bắt đầu
    bool gameStarted ; // Biến kiểm tra trạng thái game
    CImage startImage; // Khai báo đối tượng CImage cho hình ảnh nút "Bắt đầu"
    bool isMusicPlaying = false; // Kiểm tra trạng thái nhạc nền

};