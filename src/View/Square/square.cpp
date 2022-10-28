#include "square.h"

void Square::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::black);
    painter->setPen(Qt::black);
    painter->drawPolygon(QRectF(-(field_size_ / 2) + cell_width_ * j_, -(field_size_ / 2) + cell_height_ * i_,
                                cell_width_, cell_height_));
}

QRectF Square::boundingRect() const {
    return QRectF(-(field_size_ / 2) + cell_width_ * j_, -(field_size_ / 2) + cell_height_ * i_, cell_width_,
                  cell_height_);
}
