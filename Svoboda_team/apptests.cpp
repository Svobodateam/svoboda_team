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
