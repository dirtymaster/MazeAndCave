#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsItem>
#include <QPainter>

class Square : public QGraphicsItem {
public:
    Square(int i, int j, int field_size, int cell_height, int cell_width)
        : i_(i), j_(j), field_size_(field_size), cell_height_(cell_height), cell_width_(cell_width) {}
protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    QRectF boundingRect() const override;
private:
    int i_, j_, field_size_, cell_height_, cell_width_;
};

#endif // SQUARE_H
