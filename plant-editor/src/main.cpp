#include <QApplication>

#include <Widgets/MainWindow.hpp>



int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    MainWindow main_window;
    main_window.show();

    return app.exec();
}
