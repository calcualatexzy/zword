
#ifndef NODEDATA_H
#define NODEDATA_H

#include <QObject>
#include <QFile>
#include <vector>
#include <map>
#include <sstream>
#include "customDocument.h"

using std::vector;
using std::pair;

class NodeData
{
public:
    QString content() const;
    void setContent(const QString& content);

    QString primate() const;
    void setPrimate(const QString& primate);

    void PrimateToContent();
    void TextEditToPrimate(CustomDocument * textEdit);

    QString filename() const;
    void setFilename(const QString& filename);

    int listrow() const;
    void setListrow(const int& row);

    std::pair<int, int> IndexToCoor(int index);
    QString rowContent(int row);
    void setRowContent(int row, const QString& content);

    vector<QString> vcontent();

    const vector<pair<int, QString>>& getBold();

private:
    vector<QString> z_content;
    QString z_primate;
    QString z_filename;
    vector<pair<int, QString>> z_bold;
    int z_listrow;
};

Q_DECLARE_METATYPE(NodeData)

#endif // NODEDATA_H
