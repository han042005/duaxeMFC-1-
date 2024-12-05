#include "pch.h"
#include "Hcn.h"

Hcn::Hcn() {
    x1 = 0; y1 = 0; x2 = 0; y2 = 0;
}

Hcn::Hcn(int x1, int y1, int x2, int y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

void Hcn::setHcn(int x1, int y1, int x2, int y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

void Hcn::draw(CPaintDC* dc) {
    CBrush grayBrush(RGB(169, 169, 169));
    CBrush* pOldBrush = dc->SelectObject(&grayBrush);
    dc->Rectangle(x1, y1, x2, y2);
    dc->SelectObject(pOldBrush);
}

void Hcn::draw(CClientDC* dc) {
    CBrush grayBrush(RGB(169, 169, 169));
    CBrush* pOldBrush = dc->SelectObject(&grayBrush);
    dc->Rectangle(x1, y1, x2, y2);
    dc->SelectObject(pOldBrush);
}