#include <QApplication>

#include <Widgets/MainWindow.hpp>
#include <Controllers/ModelController.hpp>



int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    ModelController model_controller;
    MainWindow main_window;
    main_window.show();

    return app.exec();
}
