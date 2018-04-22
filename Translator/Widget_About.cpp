#include "Widget_About.h"

Widget_About::Widget_About(QObject *parent) : QObject(parent)
{
    groupBoxAbout = new QGroupBox;
    labelAbout = new QLabel;
    labelLOGO = new QLabel;

    labelLOGO->setPixmap(QPixmap(":/img/resources/ico/ico.png"));
    labelLOGO->setFixedSize(QSize(180, 180));
    labelLOGO->setScaledContents(true);
    labelAbout->setText("<font size=7>迷你翻译机</font><br><br>"
                        "迷你翻译机是一款小巧的词典软件，提供<br>"
                        "快速、准确的单词翻译和长句翻译功能！<br><br>"
                        "版本：V1.0<br>"
                        );
    layoutUp = new QHBoxLayout;
    layoutUp->addWidget(labelAbout);
    layoutUp->addWidget(labelLOGO);
    layoutMain = new QVBoxLayout;
    layoutMain->addLayout(layoutUp);
}

Widget_About::~Widget_About()
{

}

/*返回关于界面*/
QGroupBox *Widget_About::createGroupBoxAbout()
{
    groupBoxAbout->setLayout(layoutMain);
    return groupBoxAbout;
}
