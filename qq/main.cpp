#include "widget.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <login.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "qq_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    //Widget w;
    //w.show();
    login b;
    b.show();
    return a.exec();
}
