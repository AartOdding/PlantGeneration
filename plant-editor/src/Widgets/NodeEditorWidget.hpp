#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>



class NodeEditorWidget : public QGraphicsView
{
	Q_OBJECT

public:

	NodeEditorWidget();

protected:

    void enterEvent(QEnterEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:

	QGraphicsScene m_scene{ -10000, -10000, 20000, 20000 };

};
