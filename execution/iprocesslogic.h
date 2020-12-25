#ifndef IPROCESSLOGIC_H
#define IPROCESSLOGIC_H
#include <QString>


class IProcessLogic
{
public:
    IProcessLogic();
    virtual void processFile(QString& fileTextContent);
};

#endif // IPROCESSLOGIC_H
