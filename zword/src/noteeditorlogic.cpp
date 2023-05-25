
#include "noteeditorlogic.h"
#include "nodedata.h"


NoteEditorLogic::NoteEditorLogic(CustomDocument* textEdit, DBManager* dbManager)
    : z_textEdit(textEdit)
    , z_dbManager(dbManager)
{
    connect(this, &NoteEditorLogic::requestCreateUpdateNote, z_dbManager,
            &DBManager::onCreateUpdateRequestedNoteContent, Qt::QueuedConnection);
    connect(z_textEdit, &QTextEdit::textChanged, this, &NoteEditorLogic::onTextEditTextChanged);
}

void NoteEditorLogic::saveNoteToDB()
{

}

void NoteEditorLogic::onTextEditTextChanged()
{

}

