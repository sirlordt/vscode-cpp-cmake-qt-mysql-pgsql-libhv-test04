#include "hv/HttpServer.h"

#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPluginLoader>
#include <QString>
#include <QtPlugin>

#include "test01.h"

Q_IMPORT_PLUGIN(QMYSQLDriverPlugin)
Q_IMPORT_PLUGIN(QPSQLDriverPlugin)

bool connectToMySQLDB() {

  bool result = false;

  qInfo() << "Opening database QMYSQL";

  QSqlDatabase db1 = QSqlDatabase::addDatabase( "QMYSQL", "QMYSQL1" );

  QSqlDatabase db2 = QSqlDatabase::addDatabase( "QMYSQL", "QMYSQL2" );

  db1.setHostName( "127.0.0.1" );
  db1.setDatabaseName( "TestDB" );
  db1.setUserName( "root" );
  db1.setPassword( "dsistemas" );

  db2.setHostName( "127.0.0.1" );
  db2.setDatabaseName( "TestDB" );
  db2.setUserName( "root" );
  db2.setPassword( "dsistemas" );

  if ( !db1.open() || !db2.open()  ) {

    qInfo() << "Failed to connect!" ;
    qInfo() << "1" << db1.lastError().text();
    qInfo() << "2" << db1.lastError().text();

  }
  else {

    result = true;

    qInfo() << "Connected";

    db1.close();

    db2.close();

  }

  return result;

}

bool connectToPGSQLDB() {

  bool result = false;

  qInfo() << "Opening database QPSQL";

  QSqlDatabase db = QSqlDatabase::addDatabase( "QPSQL", "QPSQL1" );

  db.setHostName( "127.0.0.1" );
  db.setDatabaseName( "TestDB" );
  db.setUserName( "root" );
  db.setPassword( "dsistemas" );

  if ( !db.open() ) {

    qInfo() << "Failed to connect!" ;
    qInfo() << db.lastError().text();

  }
  else {

    result = true;

    qInfo() << "Connected";

    db.close();

  }

  return result;

}

int main() 
{ 

    connectToMySQLDB();

    connectToPGSQLDB();

    HttpService router;

    router.GET("/ping", [](HttpRequest* req, HttpResponse* resp) {
        return resp->String("pong");
    });

    router.GET("/data", [](HttpRequest* req, HttpResponse* resp) {
        static char data[] = "0123456789";
        return resp->Data(data, 10);
    });

    router.GET("/paths", [&router](HttpRequest* req, HttpResponse* resp) {
        return resp->Json(router.Paths());
    });

    router.GET("/get", [](HttpRequest* req, HttpResponse* resp) {
        resp->json["origin"] = req->client_addr.ip;
        resp->json["url"] = req->url;
        resp->json["args"] = req->query_params;
        resp->json["headers"] = req->headers;
        return 200;
    });

    router.POST("/echo", [](const HttpContextPtr& ctx) {
        return ctx->send(ctx->body(), ctx->type());
    });

    Test01 test01 = Test01();

    test01.setMessage( "My message" );

    if ( test01.getMessage() == "My message" ) {

      test01.printMessage();

    }

    QString message = "Listen on port 8080";

    qInfo( "%s", message.toStdString().c_str() );

    http_server_t server;
    server.port = 8080;
    server.service = &router;
    http_server_run(&server);
    return 0;

}
