
#include "nodedata.h"

QString NodeData::content() const{
    return z_content;
}

void NodeData::setContent(const QString &content)
{
    z_content = content;
}

QString NodeData::primate() const{
    return z_primate;
}

void NodeData::setPrimate(const QString &primate)
{
    z_primate = primate;
}

QString NodeData::filename() const{
    return z_filename;
}

void NodeData::setFilename(const QString &filename)
{
    z_filename = filename;
}

int NodeData::listrow() const
{
    return z_listrow;
}

void NodeData::setListrow(const int& row)
{
    z_listrow = row;
}


