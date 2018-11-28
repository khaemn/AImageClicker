#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "selectionmodel.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    qmlRegisterType< SelectionModel >("SelectionModel", 1, 0, "SelectionModel");

    QGuiApplication app(argc, argv);

    SelectionModel model;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("backendModel", &model);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
