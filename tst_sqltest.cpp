#include <QSqlQuery>
#include <QtTest>
#include <qdebug.h>

#include <sqlConnector/sqlconnector.h>

class SqlTest : public QObject
{
    Q_OBJECT
private:
    SqlConnector connector;
public:
    SqlTest() { }
    ~SqlTest() { }

private slots:
    void test_connectionOpening();
    void test_tableCreation();
    void test_dataInsertion();
    void test_dataDeletion();
};

void SqlTest::test_connectionOpening()
{
    QVERIFY(connector.open());

}

void SqlTest::test_tableCreation()
{
    QSqlQuery query;
    QVERIFY(query.exec("CREATE TABLE IF NOT EXISTS `main` ("
                                   "`id` INTEGER PRIMARY KEY, "
                                   "`name` varchar(255) NOT NULL"
                             ")"));
}

void SqlTest::test_dataInsertion()
{
    QSqlQuery query;
    QVERIFY(query.exec("INSERT INTO `main` (`name`) VALUES ('Vasya')"));

    QString name;
    query.exec("SELECT name FROM `main` LIMIT 1");
    while (query.next()) {
        name = query.value("name").toString();
    }
    QCOMPARE("Vasya", name);
}

void SqlTest::test_dataDeletion()
{
    QSqlQuery query;
    QVERIFY(query.exec("DELETE FROM `main` WHERE `name` = 'Vasya'"));
}

QTEST_APPLESS_MAIN(SqlTest)

#include "tst_sqltest.moc"
