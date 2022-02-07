#include "mainwindow.h"

#include "qtsingleapplication.h"
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QtSingleApplication a(argc, argv);

    if (a.isRunning())
             return !a.sendMessage("It is running!");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Dailek_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    a.setActivationWindow(&w);
    if(w.init()) {
        w.show();
        return a.exec();
    }
    a.exit();
    return 0;
}
