#include <Widgets/Node.hpp>
#include <Widgets/NodeEditorWidget.hpp>



NodeEditorWidget::NodeEditorWidget()
{
	setDragMode(ScrollHandDrag);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setScene(&m_scene);
	m_scene.addItem(new Node());
	m_scene.addItem(new Node());
}

void NodeEditorWidget::enterEvent(QEnterEvent* event)
{
    QGraphicsView::enterEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}

void NodeEditorWidget::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}

void NodeEditorWidget::mouseReleaseEvent(QMouseEvent* event)
{
    QGraphicsView::mouseReleaseEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}
