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

    ///
    /// \brief GetActiveDocument
    /// \return The active document or null
    ///
    OpenDocument* GetActiveDocument() const;

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionQuit_triggered();

    void on_actionClose_triggered();

private:

    Ui::MainEditor *ui;

    ///
    /// \brief Open documents. These are probably deleted by the tab container
    ///
    std::vector<OpenDocument*> Documents;
};

#endif // MAINEDITOR_H
