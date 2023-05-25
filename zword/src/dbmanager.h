
#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QObject>

class NodeData;

class DBManager : public QObject
{
    Q_OBJECT
public:
    explicit DBManager(QObject *parent = nullptr);

public slots:
    void onCreateUpdateRequestedNoteContent(const NodeData &note);

signals:

};

#endif // DBMANAGER_H
