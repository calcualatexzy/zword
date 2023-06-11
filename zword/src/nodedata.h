
#ifndef NODEDATA_H
#define NODEDATA_H

#include <QObject>
#include <QFile>
#include <vector>
#include <map>
#include <sstream>
#include <qnamespace.h>
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
    const vector<pair<int, QString>>& getItalic();
    void resetFormat();

    void setStyle(QString styleStr);
    void setStyle_Key(std::string key, std::string value);
    std::string getStyle(std::string key);

private:
    vector<QString> z_content;
    QString z_primate;
    QString z_filename;
    vector<pair<int, QString>> z_bold;
    vector<pair<int, QString>> z_italic;
    int z_alignFlag = Qt::AlignLeft;
    int z_listrow;
    std::map<std::string, std::string> z_styleMap;
};

Q_DECLARE_METATYPE(NodeData)

#endif // NODEDATA_H
