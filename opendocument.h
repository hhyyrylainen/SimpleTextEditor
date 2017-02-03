#ifndef OPENDOCUMENT_H
#define OPENDOCUMENT_H

#include <QTabWidget>
#include <QTextEdit>
#include <QWidget>

class OpenDocument : public QWidget
{
    Q_OBJECT
public:
    explicit OpenDocument(const QString &file, QWidget *parent = 0);


    ///
    /// \brief Loads text into this document from disk file
    /// \return True if loaded, false if file didn't exist
    ///
    bool LoadTextFile();

    ///
    /// \brief Saves current text in the file
    ///
    void Save();


    ///
    /// \brief FindOurIndex
    /// \return Our index in our parent TabWidget or -1
    ///
    int FindOurIndex() const;

    ///
    /// \brief GetOurParent
    /// \return Our containing tabs or null
    ///
    QTabWidget* GetOurParent() const;

signals:

private slots:
    ///
    /// \brief Marks this document dirty
    ///
    void OnTextChanged();

public slots:

protected:

    ///
    /// \brief Updates the title of the tab that has this document in it
    ///
    void UpdateTabTitle();

private:

    ///
    /// \brief True when the text has been edited and this file should be saved before closing
    ///
    bool Dirty = false;

    ///
    /// \brief Name of the file that is being edited in this widget
    ///
    QString FileName;


    QTextEdit* Editor;
};

#endif // OPENDOCUMENT_H
