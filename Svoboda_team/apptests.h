#ifndef APPTESTS_H
#define APPTESTS_H

#include <QtTest/QtTest>
#include "dbmanager.h"

class AppTests: public QObject
{
    Q_OBJECT
public:
    AppTests();
    ~AppTests();
private:
    DBManager* m_dbManager;
private slots:
    void authTest();
    void userFieldsTest();
    void setCurrentUserTest();
    void updateLeaveCountTest();
    void retrieveLeaveCountTest();
    void testSessionActive();
};

#endif // APPTESTS_H
