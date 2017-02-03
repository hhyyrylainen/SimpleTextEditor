#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include <QMainWindow>

#include <vector>

#include "opendocument.h"

namespace Ui {
class MainEditor;
}

class MainEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainEditor(QWidget *parent = 0);
    ~MainEditor();

    void OpenNewDocument(const QString &name);

private slots:
    void on_actionOpen_triggered();

private:

    Ui::MainEditor *ui;

    ///
    /// \brief Open documents. These are probably deleted by the tab container
    ///
    std::vector<OpenDocument*> Documents;
};

#endif // MAINEDITOR_H
