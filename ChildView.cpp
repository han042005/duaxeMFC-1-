#include "pch.h"
#include "framework.h"
#include "duaxeMFC.h"
#include "ChildView.h"
#include "ChuongngaiVat.h"
#include "afxwin.h" // Bao gồm thư viện để sử dụng CButton và CImage
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Constructor khởi tạo đối tượng xe1, d1, obstacle
CChildView::CChildView()
    : xe1(120, 200, 150, 250, RGB(255, 0, 0), 5), // Khởi tạo xe
    d1(0, 100, 400, 700),                     // Khởi tạo đường đua
    obstacle(150, 120, 300, 150),               // Khởi tạo chướng ngại vật
    gameComplete(false),                         // Trạng thái game mặc định là chưa hoàn thành
    dung(false),                                 // Trạng thái dừng game
    gameStarted(false)                           // Game chưa bắt đầu
{
    // Khởi tạo chướng ngại vật (giống như bạn đã làm)
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 50, rand() % (400 - 50) + 50, 100));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 150, rand() % (400 - 50) + 50, 200));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 250, rand() % (400 - 50) + 50, 300));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 350, rand() % (400 - 50) + 50, 400));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 450, rand() % (400 - 50) + 50, 500));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 550, rand() % (400 - 50) + 50, 600));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 650, rand() % (400 - 50) + 50, 700));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 750, rand() % (400 - 50) + 50, 800));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 850, rand() % (400 - 50) + 50, 900));

}

// Trạng thái game mặc định là chưa hoàn thành
CChildView::~CChildView() {}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
   
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_WM_KEYDOWN()
    ON_WM_SETFOCUS()
    ON_WM_CREATE()
    ON_BN_CLICKED(IDC_BUTTON_START, &CChildView::OnStartButtonClicked)  // Thêm sự kiện cho nút Start
END_MESSAGE_MAP()

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) {
    if (!CWnd::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    cs.style &= ~WS_BORDER;
    cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
        ::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

    return TRUE;
}

void CChildView::OnSetFocus(CWnd* pOldWnd)
{
    CWnd::OnSetFocus(pOldWnd);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // Phát nhạc nền chờ lặp lại
    PlaySound(L"C:\\Users\\ADMIN\\Downloads\\ChaoMungDenBinhNguyenVoTanVuhuynhRemix-VuHuynh-7847989.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    isMusicPlaying = true;

    SetFocus();
    gameStarted = false; // Ban đầu, trò chơi chưa bắt đầu

    // Tạo nút "Bắt đầu"
    startButton.Create(L"Bắt đầu", WS_CHILD | WS_VISIBLE | BS_BITMAP,
        CRect(100, 380, 300, 480), this, IDC_BUTTON_START);

    // Lấy kích thước của nút (button)
    CRect buttonRect;
    startButton.GetClientRect(buttonRect);
    int buttonWidth = buttonRect.Width();
    int buttonHeight = buttonRect.Height();

    // Tải hình ảnh vào đối tượng CImage
    HRESULT hr = startImage.Load(L"C:\\Users\\ADMIN\\Downloads\\5.png"); // Thay đường dẫn của bạn

    // Điều chỉnh kích thước hình ảnh nếu cần
    int imgWidth = startImage.GetWidth();
    int imgHeight = startImage.GetHeight();

    // Thay đổi tỷ lệ kích thước của hình ảnh nếu cần
    double scaleX = (double)buttonWidth / imgWidth;
    double scaleY = (double)buttonHeight / imgHeight;

    // Tạo hình ảnh đã được thay đổi kích thước
    CImage resizedImage;
    resizedImage.Create((int)(imgWidth * scaleX), (int)(imgHeight * scaleY), 24);  // Thêm tham số độ sâu màu 24 bit


    // Vẽ hình ảnh vào đối tượng resizedImage
    HDC hdc = resizedImage.GetDC();
    startImage.StretchBlt(hdc, 0, 0, resizedImage.GetWidth(), resizedImage.GetHeight(), 0, 0, imgWidth, imgHeight);
    resizedImage.ReleaseDC();

    // Chuyển CImage thành bitmap và gán cho nút
    HBITMAP hBitmap = (HBITMAP)resizedImage.Detach(); // Detach image từ CImage và lấy HBITMAP
    startButton.SetBitmap(hBitmap); // Gán bitmap vào nút

    return 0;
}




void CChildView::OnStartButtonClicked()
{
    if (isMusicPlaying) {
        // Dừng nhạc khi game bắt đầu
        PlaySound(NULL, 0, 0);
        isMusicPlaying = false;
    }
    // Phát nhạc khi game bắt đầu
    PlaySound(L"C:\\Users\\ADMIN\\Downloads\\Nhacduaxe.mp3.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    isMusicPlaying = true;

    // Khi nhấn nút "Bắt đầu"
    gameStarted = true;    // Cập nhật trạng thái game
    startButton.ShowWindow(SW_HIDE); // Ẩn nút "Bắt đầu"
    

    // Reset trạng thái game
    xe1.setPosition(120, 200); // Đặt lại vị trí xe
    d1.reset(); // Đặt lại đường đua và chướng ngại vật

    // Thêm lại chướng ngại vật
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 50, rand() % (400 - 50) + 50, 100));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 150, rand() % (400 - 50) + 50, 200));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 250, rand() % (400 - 50) + 50, 300));

    SetFocus();                // Đảm bảo cửa sổ nhận focus

    // Bắt đầu Timer
    SetTimer(1, 50, nullptr);
    Invalidate(); // Vẽ lại giao diện
}
  
void CChildView::OnPaint() {
    CPaintDC dc(this);

    // Kích thước đường đua (có thể thay đổi tùy vào game)
    const int roadWidth = 400;
    const int roadHeight = 600;

    // Nếu game chưa bắt đầu, vẽ nền hình ảnh và nút "Bắt đầu"
    if (!gameStarted) {
        // Tạo đối tượng CImage để tải hình ảnh nền
        CImage backgroundImage;
        HRESULT hr = backgroundImage.Load(L"C:\\Users\\ADMIN\\Downloads\\synthwave_pixelart_by_radiantsdreams_df3ghr6-pre.jpg");  // Đường dẫn tới hình ảnh       

        // Lấy kích thước của hình ảnh
        int imgWidth = backgroundImage.GetWidth();
        int imgHeight = backgroundImage.GetHeight();

        // Tính toán tỷ lệ để thu phóng hình ảnh sao cho vừa với kích thước đường đua
        double scaleX = (double)roadWidth / imgWidth;
        double scaleY = (double)roadHeight / imgHeight;

        // Vẽ hình ảnh lên cửa sổ sao cho vừa với kích thước đường đua
        backgroundImage.Draw(dc.m_hDC, 0, 0, (int)(imgWidth * scaleX), (int)(imgHeight * scaleY));

        // Hiển thị nút "Bắt đầu"
        startButton.ShowWindow(SW_SHOW); // Hiển thị nút "Bắt đầu"
        return;
    }

    // Nếu game đã kết thúc, vẽ nền trắng và chỉ giữ lại hình chữ nhật
    if (dung) {
        // Vẽ nền hình chữ nhật
        CRect backgroundRect(0, 0, roadWidth, roadHeight);
        dc.FillSolidRect(backgroundRect, RGB(200, 200, 255));  // Nền hình chữ nhật

        // Tạo đối tượng CImage để tải hình ảnh nền khi game kết thúc
        CImage endImage;
        HRESULT hr = endImage.Load(L"C:\\Users\\ADMIN\\Downloads\\z6101705081283_3e732b2a2785c2802e96ebc55641fde1.jpg");  // Đường dẫn tới hình ảnh

        if (SUCCEEDED(hr)) {
            // Lấy kích thước của hình ảnh
            int imgWidth = endImage.GetWidth();
            int imgHeight = endImage.GetHeight();

            // Tính toán tỷ lệ để thu phóng hình ảnh sao cho vừa với kích thước đường đua
            double scaleX = (double)roadWidth / imgWidth;
            double scaleY = (double)roadHeight / imgHeight;

            // Vẽ hình ảnh vào khu vực nền
            endImage.Draw(dc.m_hDC, 0, 0, (int)(imgWidth * scaleX), (int)(imgHeight * scaleY));
        }

      

        // Tải hình ảnh "Over game"
        CImage imageInsideFrame;
        hr = imageInsideFrame.Load(L"C:\\Users\\ADMIN\\Downloads\\image-removebg-preview (3).png");  // Đường dẫn hình ảnh bạn muốn vẽ vào khung

        if (SUCCEEDED(hr)) {
            // Lấy kích thước của hình ảnh
            int imgWidth = imageInsideFrame.GetWidth();
            int imgHeight = imageInsideFrame.GetHeight();

            // Tính toán tỷ lệ để thu phóng hình ảnh sao cho vừa với kích thước của khung
            double scaleX = (double)(roadWidth)*0.7/  imgWidth; // Vẽ hình ảnh sao cho phù hợp với chiều rộng của đường đua
            double scaleY = (double)(roadHeight)*0.4 / imgHeight; // Vẽ hình ảnh sao cho phù hợp với chiều cao của đường đua

            int offsetY = 30; // Giá trị này có thể điều chỉnh để di chuyển hình ảnh xuống 

            // Tính toán vị trí để căn giữa ảnh
            int xPos = (roadWidth - (int)(imgWidth * scaleX)) / 2; // Vị trí X căn giữa
            int yPos = (roadHeight - (int)(imgHeight * scaleY)) / 2 + offsetY; // Vị trí Y căn giữa

            // Vẽ hình ảnh trực tiếp lên màn hình tại vị trí đã tính toán
            imageInsideFrame.Draw(dc.m_hDC, xPos, yPos, (int)(imgWidth * scaleX), (int)(imgHeight * scaleY));
        
        }

        return;
    }

    // Vẽ đường đua, chướng ngại vật, xe
    d1.draw(&dc);
    const std::vector<ChuongngaiVat>& obstacles = d1.getObstacles();
    for (const auto& obstacle : obstacles) {
        obstacle.draw(&dc);
    }
    xe1.drawPaint(&dc);
}



void CChildView::OnTimer(UINT_PTR nIDEvent) {
    if (nIDEvent == 1 && !dung) {
        xe1.move(); // Gọi phương thức move() của xe để di chuyển tự động
        d1.scroll(5); // Cuộn đường đua

        // Kiểm tra va chạm với từng chướng ngại vật
        const std::vector<ChuongngaiVat>& obstacles = d1.getObstacles(); // Lấy danh sách chướng ngại vật
        for (const auto& obstacle : obstacles) {
            if (obstacle.checkCollision(xe1.getX1(), xe1.getY1(), xe1.getX2(), xe1.getY2())) {
                dung = true; // Dừng trò chơi khi va chạm xảy ra
                KillTimer(1); // Dừng Timer
                // Dừng nhạc gameplay
                PlaySound(NULL, 0, 0);
                isMusicPlaying = false;
                // Phát nhạc kết thúc
                PlaySound(L"C:\\Users\\ADMIN\\Downloads\\nhacthuacuocgameduaxe.wav", NULL, SND_FILENAME | SND_ASYNC);
                Invalidate(); // Vẽ lại cửa sổ
                return;  // Dừng kiểm tra va chạm khi game đã kết thúc
            }
        }

        // Kiểm tra nếu xe đi hết đường đua
        if (d1.isComplete()) {
            gameComplete = true;
            KillTimer(1); // Dừng Timer khi game hoàn thành
        }

        Invalidate(); // Vẽ lại cửa sổ sau mỗi khung hình
    }

    CWnd::OnTimer(nIDEvent);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
    if (gameComplete) return; // Nếu game đã kết thúc, không xử lý phím
    if (gameStarted == true) {


        int roadLeft = 0;   // Giới hạn trái của đường đua
        int roadRight = 400; // Giới hạn phải của đường đua

        switch (nChar) {
        case VK_LEFT: // Nhấn phím mũi tên trái
            xe1.setX(xe1.getX1() - 10, xe1.getX2() - 10, roadLeft, roadRight); // Di chuyển xe sang trái
            break;
        case VK_RIGHT: // Nhấn phím mũi tên phải
            xe1.setX(xe1.getX1() + 10, xe1.getX2() + 10, roadLeft, roadRight); // Di chuyển xe sang phải
            break;
        }
    }

    Invalidate(); // Vẽ lại cửa sổ sau mỗi lần thay đổi vị trí
    CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
    OutputDebugString(L"Key pressed\n");
}