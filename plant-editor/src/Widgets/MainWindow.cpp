#include <Widgets/MainWindow.hpp>


MainWindow::MainWindow()
	: QMainWindow(nullptr)
{
	menuBar()->addMenu("&File");
	menuBar()->addMenu("&View");
	setCentralWidget(&m_node_editor);
}
