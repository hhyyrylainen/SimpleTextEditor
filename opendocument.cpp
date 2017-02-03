#include "opendocument.h"

#include <QPushButton>

OpenDocument::OpenDocument(QWidget *parent) : QWidget(parent)
{
    QPushButton* button = new QPushButton(
            "Press me", this);
        button->move(100, 100);
        button->show();
}
