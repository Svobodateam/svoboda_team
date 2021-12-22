#include "apptests.h"

QTEST_MAIN(AppTests)

AppTests::AppTests() : m_dbManager(new DBManager()) {

}

AppTests::~AppTests() {
    delete m_dbManager;
}

void AppTests::authTest() {
    bool auth = m_dbManager->authorizeUser("userivan");
    QVERIFY(auth);
}

void AppTests::userFieldsTest() {
    m_dbManager->authorizeUser("userivan");
    QCOMPARE(m_dbManager->getCurrentUser()->userName, "userivan");
    QCOMPARE(m_dbManager->getCurrentUser()->firstName, "Ivan");
    QCOMPARE(m_dbManager->getCurrentUser()->lastName, "Ivanov");
    QCOMPARE(m_dbManager->getCurrentUser()->role, "designer");
}

void AppTests::setCurrentUserTest()
{
    QMap<LeaveType, int> tmpLeave;
    tmpLeave[LeaveType::Vacation] = 21;
    tmpLeave[LeaveType::UnpaidVacation] = 15;
    tmpLeave[LeaveType::Sickness75] = 10;
    tmpLeave[LeaveType::Sickness100] = 5;

    User *tmpUser = new User;
    tmpUser->id = 1;
    tmpUser->leavesCount = tmpLeave;
    tmpUser->userName = "userroman";
    tmpUser->firstName = "Roman";
    tmpUser->lastName = "Tuputia";
    tmpUser->role = "Juggernaut";

    m_dbManager->setCurrentUser(tmpUser);
    QCOMPARE(m_dbManager->getCurrentUser()->userName, "userroman");
    QCOMPARE(m_dbManager->getCurrentUser()->firstName, "Roman");
    QCOMPARE(m_dbManager->getCurrentUser()->lastName, "Tuputia");
    QCOMPARE(m_dbManager->getCurrentUser()->role, "Juggernaut");
}

void AppTests::updateLeaveCountTest()
{
    m_dbManager->authorizeUser("userivan");
    bool tmp = m_dbManager->updateLeaveCount(LeaveType::Vacation, 9);
    QVERIFY(tmp);
}

void AppTests::retrieveLeaveCountTest()
{
    m_dbManager->authorizeUser("userivan");
    QMap<LeaveType, int> tmpLeave = m_dbManager->retrieveLeaveCount();

    QCOMPARE(m_dbManager->getCurrentUser()->userName, "userivan");
    QCOMPARE(m_dbManager->getCurrentUser()->firstName, "Ivan");
    QCOMPARE(m_dbManager->getCurrentUser()->lastName, "Ivanov");
    QCOMPARE(m_dbManager->getCurrentUser()->role, "designer");
}

void AppTests::testSessionActive() {
    m_dbManager->authorizeUser("userivan");
    QCOMPARE(m_dbManager->getSessionActive(), true);
}
