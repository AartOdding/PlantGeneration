#pragma once

#include <QMainWindow>
#include <QMenuBar>

#include <Widgets/NodeEditorWidget.hpp>



class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	MainWindow();

private:

	NodeEditorWidget m_node_editor;

};
