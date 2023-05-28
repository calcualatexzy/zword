
#ifndef NODEDATA_H
#define NODEDATA_H

#include <QObject>
#include <QFile>
#include <vector>
#include <sstream>

using std::vector;

class NodeData
{
public:
    QString content() const;
    void setContent(const QString& content);

    QString primate() const;
    void setPrimate(const QString& primate);

    QString filename() const;
    void setFilename(const QString& filename);

    int listrow() const;
    void setListrow(const int& row);
    vector<QString> vcontent();

private:
    vector<QString> z_content;
    QString z_primate;
    QString z_filename;
    int z_listrow;
};

Q_DECLARE_METATYPE(NodeData)

#endif // NODEDATA_H
