#include "apptests.h"
#include "dbmanager.h"

QTEST_MAIN(AppTests)

AppTests::AppTests() : m_dbManager(new DBManager()) {

}

AppTests::~AppTests() {
    delete m_dbManager;
}
