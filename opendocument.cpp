#include "opendocument.h"

#include <QFile>
#include <QPushButton>
#include <QTabWidget>
#include <QTextStream>
#include <QVBoxLayout>

///
/// \brief isFixedPitch
/// \param font
/// \return True if font is monospace
///
static bool isFixedPitch(const QFont &font)
{
    const QFontInfo fi(font);
    return fi.fixedPitch();
}

///
/// \brief Font selection helper
/// \return returns a monospace font
/// \note From stack overflow:
/// http://stackoverflow.com/questions/18896933/qt-qfont-selection-of-a-monospace-font-doesnt-work
///
static QFont getMonospaceFont()
{
    QFont font("monospace");

    if (isFixedPitch(font))
        return font;

    font.setStyleHint(QFont::Monospace);

    if (isFixedPitch(font))
        return font;

    font.setStyleHint(QFont::TypeWriter);

    if (isFixedPitch(font))
        return font;

    font.setFamily("courier");

    if (isFixedPitch(font))
        return font;

    return font;
}

OpenDocument::OpenDocument(const QString &file, QWidget *parent) : QWidget(parent),
    FileName(file)
{
    auto* layout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    Editor = new QTextEdit(this);

    Editor->setFont(getMonospaceFont());

    connect(Editor, SIGNAL (textChanged()), this, SLOT (OnTextChanged()));

    layout->addWidget(Editor);

    setLayout(layout);

    // Load existing text //
    LoadTextFile();
}

bool OpenDocument::LoadTextFile()
{
    QFile f(FileName);

    if (!f.open(QFile::ReadOnly | QFile::Text))
        return false;

    QTextStream in(&f);

    Editor->setText(in.readAll());

    return true;
}

void OpenDocument::Save()
{
    QFile f(FileName);

    if (!f.open(QFile::WriteOnly | QFile::Text))
        return;

    QTextStream out(&f);

    out << Editor->toPlainText();

    Dirty = false;

    UpdateTabTitle();
}

int OpenDocument::FindOurIndex() const
{
    // Get parent container //
    auto* tabs = GetOurParent();

    if(!tabs)
        return -1;

    auto* castedUs = qobject_cast<const QWidget*>(this);

    // Find us //
    for(int i = 0; i < tabs->count(); ++i){

        if(castedUs == tabs->widget(i))
                return i;
    }

    return -1;
}

QTabWidget *OpenDocument::GetOurParent() const
{
    auto* firstParent = parent();

    if(!firstParent)
        return nullptr;

    auto* tabs = qobject_cast<QTabWidget*>(firstParent->parent());

    return tabs;
}

void OpenDocument::OnTextChanged()
{
    // Mark as dirty //
    Dirty = true;

    UpdateTabTitle();
}

void OpenDocument::UpdateTabTitle()
{
    auto* tabs = GetOurParent();

    if(!tabs)
        return;

    int index = FindOurIndex();

    if(index < 0)
        return;

    tabs->setTabText(index, FileName + (Dirty ? "*" : ""));
}
