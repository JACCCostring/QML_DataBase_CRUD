#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include "databasemodel.h"
#include "dbhandler.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //creating obj for db handler connection
    dbHandler *dbHandler = dbHandler::getDataBaseInstance();
    //assigning driver to db
    dbHandler->initDB("QSQLITE");
    //setting db name
    dbHandler->setDBName("/Users/f1r3544/MyProject/QT Test/build-dataProjectSQL-Desktop_Qt_5_9_9_clang_64bit-Debug/Policy.db");
    //open and veriying db
    if(! dbHandler->openDB()) qDebug()<<"DB can not be open !";
    //creating obj for db QSqlqueryModel model
    dataBaseModel *dbEntity = new dataBaseModel(&app);
    //exposing to QML
    engine.rootContext()->setContextProperty("dbHandler", dbEntity);
    //rest of the code
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
