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
    OpenDocument* newDocument = new OpenDocument(name);

    ui->tabWidget->addTab(newDocument, name);

    Documents.push_back(newDocument);
}

OpenDocument *MainEditor::GetActiveDocument() const
{
     return qobject_cast<OpenDocument*>(
                ui->tabWidget->currentWidget());
}

void MainEditor::on_actionOpen_triggered()
{

}

void MainEditor::on_actionSave_triggered()
{
    OpenDocument* document = GetActiveDocument();

    if(!document)
        return;

    document->Save();
}

void MainEditor::on_actionQuit_triggered()
{
    close();
}

void MainEditor::on_actionClose_triggered()
{
    // TODO: ask if user wants to save
    auto* document = GetActiveDocument();

    if(!document)
        return;

    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());

    // Remove also from Documents //
    for(auto iter = Documents.begin(); iter != Documents.end(); ++iter){


        if((*iter) == document){

            Documents.erase(iter);
            break;
        }
    }
}
