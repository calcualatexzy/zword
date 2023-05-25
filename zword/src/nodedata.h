
#ifndef NODEDATA_H
#define NODEDATA_H

#include <QObject>

class NodeData
{
public:
    NodeData();

    QString content() const;
    void setContent(const QString& content);
private:
    QString z_content;
};

Q_DECLARE_METATYPE(NodeData)

#endif // NODEDATA_H
