
#ifndef NOTEEDITORLOGIC_H
#define NOTEEDITORLOGIC_H

#include <QObject>
#include "customDocument.h"
#include "dbmanager.h"

class CustomDocument;
class DBManager;
class NodeData;

class NoteEditorLogic : public QObject
{
    Q_OBJECT
public:
    NoteEditorLogic(CustomDocument* textEdit, DBManager* dbManager);
    void saveNoteToDB();

public slots:
    void onTextEditTextChanged();

private:
    CustomDocument* z_textEdit;
    DBManager* z_dbManager;
    NodeData z_currentNote;

signals:
    void requestCreateUpdateNote(const NodeData &note);

};

#endif // NOTEEDITORLOGIC_H
