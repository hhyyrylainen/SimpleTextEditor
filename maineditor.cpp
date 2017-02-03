#include "maineditor.h"
#include "ui_maineditor.h"

MainEditor::MainEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainEditor)
{
    ui->setupUi(this);
    OpenNewDocument("New1");
}

MainEditor::~MainEditor()
{
    delete ui;
}

void MainEditor::OpenNewDocument(const QString &name)
{
    OpenDocument* newDocument = new OpenDocument();

    ui->tabWidget->addTab(newDocument, name);

    Documents.push_back(newDocument);
}

void MainEditor::on_actionOpen_triggered()
{

}
