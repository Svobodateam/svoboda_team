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
