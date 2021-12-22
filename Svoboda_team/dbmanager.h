#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QFile>
#include <QMessageBox>
#include <QApplication>
#include <QSqlQuery>
#include <QtSql>

#define DEFAULT_DB_PATH QString(QDir::currentPath() + "/svoboda_db.sqlite3")

enum LeaveType {
    Vacation = 1,
    UnpaidVacation,
    Sickness75,
    Sickness100

};

struct User {
    int id;
    QMap<LeaveType, int> leavesCount;
    QString userName;
    QString firstName;
    QString lastName;
    QString role;
};

class DBManager
{
public:
    DBManager();
    ~DBManager();
    bool startup();
    QMap <LeaveType, int> retrieveLeaveCount();
    void refreshLeaveCount();
    bool updateLeaveCount(LeaveType, int);
    User* getCurrentUser();
    void setCurrentUser(User*);
    bool getSessionActive();
    void endSession();
    QString leaveTypeToStr(LeaveType);
    bool authorizeUser(User*);
    bool authorizeUser(QString);
private:
    bool m_isSessionActive;
    User* m_currentUser;
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
