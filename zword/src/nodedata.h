
#ifndef NODEDATA_H
#define NODEDATA_H

#include <QObject>
#include <QFile>

class NodeData
{
public:
    NodeData();

    QString content() const;
    void setContent(const QString& content);

    QString primate() const;
    void setPrimate(const QString& primate);

    QString filename() const;
    void setFilename(const QString& filename);
private:
    QString z_content;
    QString z_primate;
    QString z_filename;
};

Q_DECLARE_METATYPE(NodeData)

#endif // NODEDATA_H
