#ifndef WIDGET_ABOUT_H
#define WIDGET_ABOUT_H

#include <QObject>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>

class Widget_About : public QObject
{
    Q_OBJECT
public:
    explicit Widget_About(QObject *parent = nullptr);
    ~Widget_About();
    //返回关于界面的函数
    QGroupBox * createGroupBoxAbout();
private:
    QVBoxLayout * layoutMain;
    QHBoxLayout * layoutUp;

    QLabel * labelAbout;
    QLabel * labelLOGO;
    QGroupBox * groupBoxAbout;
};

#endif // WIDGET_ABOUT_H
