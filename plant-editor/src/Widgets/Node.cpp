#include <QPainter>
#include <QGraphicsSceneEvent>

#include <Widgets/Node.hpp>



QRectF Node::boundingRect() const
{
    constexpr double w = 70;
    constexpr double h = 50;

    return QRectF(-0.5 * w, -0.5 * h, w, h);
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setBrush(QColor(255, 0, 0, 255));
    painter->setPen(QPen(QColor(0, 255, 0, 255), 3));
    painter->drawRoundedRect(boundingRect().marginsRemoved({ 2, 2, 2, 2 }), 5, 5);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    event->accept();
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        setPos(event->scenePos() - event->buttonDownPos(Qt::LeftButton));
    }
}
