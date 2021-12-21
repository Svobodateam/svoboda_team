#include "dbmanager.h"

DBManager::DBManager() : m_currentUser(new User) {
    startup();
}

DBManager::~DBManager() {

    if (m_db.isOpen()) endSession();
    if (m_currentUser) delete m_currentUser;
}

bool DBManager::startup() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");

    if (!QFile::exists(DEFAULT_DB_PATH)) {
        QMessageBox* errBox = new QMessageBox(QMessageBox::Critical, QString("DB not found"), QString("DB cannot be found! Check read settings."),
                                              QMessageBox::Close);
        if (errBox->exec() == QMessageBox::Close)
            QTimer::singleShot(500, Qt::PreciseTimer, &QCoreApplication::quit);
    }

    m_db.setDatabaseName(DEFAULT_DB_PATH);
    if (!m_db.open()) {
        QMessageBox* errBox = new QMessageBox(QMessageBox::Critical, QString("DB cannot be opened"), QString("DB cannot be opened! Check execute settings."),
                                              QMessageBox::Close);
        if (errBox->exec() == QMessageBox::Close)
            QTimer::singleShot(500, Qt::PreciseTimer, &QCoreApplication::quit);
    }

    m_isSessionActive = true;
    return true;
}

QMap<LeaveType, int> DBManager::retrieveLeaveCount() {

    QMap<LeaveType, int> result;
    QString rawSelect = QString("SELECT * FROM timeoffs WHERE user = %1").arg(m_currentUser->id);
    QSqlQuery retrieveCountQuery(rawSelect, m_db);
    bool ok = retrieveCountQuery.exec();
    if (!ok) {
        QMessageBox* errBox = new QMessageBox(QMessageBox::Critical, QString("DB data cannot be retrieved"), QString("DB data cannot be retrieved! Check execute settings."),
                                              QMessageBox::Close);
        if (errBox->exec() == QMessageBox::Close)
            QTimer::singleShot(500, Qt::PreciseTimer, &QCoreApplication::quit);
    }

    while (retrieveCountQuery.next()) {
        result[Vacation] = retrieveCountQuery.value(Vacation).toInt();
        result[UnpaidVacation] = retrieveCountQuery.value(UnpaidVacation).toInt();
        result[Sickness75] = retrieveCountQuery.value(Sickness75).toInt();
        result[Sickness100] = retrieveCountQuery.value(Sickness100).toInt();
    }

    return result;
}

bool DBManager::updateLeaveCount(LeaveType type, int newValue) {

    QString colName = leaveTypeToStr(type);
    QString rawUpdate = QString("UPDATE timeoffs SET %1=%2 WHERE user=%3;")
            .arg(colName)
            .arg(newValue)
            .arg(m_currentUser->id);
    QSqlQuery retrieveCountQuery(rawUpdate, m_db);
    bool ok = retrieveCountQuery.exec();
    if (!ok) {
        QMessageBox* errBox = new QMessageBox(QMessageBox::Critical, QString("DB data cannot be retrieved"), QString("DB data cannot be retrieved! Check execute settings."),
                                              QMessageBox::Close);
        if (errBox->exec() == QMessageBox::Close)
            QTimer::singleShot(500, Qt::PreciseTimer, &QCoreApplication::quit);
    }

    return ok;
}

User* DBManager::getCurrentUser() {
    return m_currentUser;
}

void DBManager::setCurrentUser(User *user) {
    if (user) m_currentUser = user;
}

void DBManager::endSession() {
    m_db.close();
    m_isSessionActive = false;
}

QString DBManager::leaveTypeToStr(LeaveType type) {
    switch (type) {
        case Vacation: return QString("days_paid");
        case UnpaidVacation: return QString("days_unpaid");
        case Sickness75: return QString("days_sick_75pr");
        case Sickness100: return QString("days_sick_100pr");
    }
    return QString();
}

bool DBManager::authorizeUser(User *user) {

    return authorizeUser(user->userName);
}

bool DBManager::authorizeUser(QString username) {

    QString rawSelect = QString("SELECT * FROM users WHERE username = '%1'").arg(username);
    QSqlQuery retrieveCountQuery(rawSelect, m_db);
    bool ok = retrieveCountQuery.exec();
    bool userExist = false;
    if (!ok) {
        QMessageBox* errBox = new QMessageBox(QMessageBox::Critical, QString("DB data cannot be retrieved"), QString("DB data cannot be retrieved! Check execute settings."),
                                              QMessageBox::Close);
        if (errBox->exec() == QMessageBox::Close)
            QTimer::singleShot(500, Qt::PreciseTimer, &QCoreApplication::quit);
    }

    while (retrieveCountQuery.next()) {
        userExist = true;
        m_currentUser->id = retrieveCountQuery.value("userid").toInt();
        m_currentUser->firstName = retrieveCountQuery.value("first_name").toString();
        m_currentUser->lastName = retrieveCountQuery.value("last_name").toString();
        m_currentUser->role = retrieveCountQuery.value("role").toString();
    }
    if (!userExist) return false;
    m_currentUser->leavesCount = retrieveLeaveCount();
    m_currentUser->userName = username;
    return true;
}

