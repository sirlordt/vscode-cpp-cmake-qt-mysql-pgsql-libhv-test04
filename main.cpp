//#include <QCoreApplication>

//#include <hv/hv.h>
//#include "hv/hssl.h"
//#include "hv/hmain.h"
//#include "hv/iniparser.h"
//#include "hv/HttpServer.h"

//hv::HttpServer  g_http_server;
//hv::HttpService g_http_service;

//void print_version() {
//  printf("%s version %s\n", g_main_ctx.program_name, hv_version());
//}

//int main(int argc, char *argv[])
//{
//    main_ctx_init(argc, argv);

//    QCoreApplication a(argc, argv);

//    qDebug( "Hello World" );

//    print_version();

//    return a.exec();
//}

//#include "hv/TcpServer.h"
//using namespace hv;

//int main() {
//    int port = 1234;
//    TcpServer srv;
//    int listenfd = srv.createsocket(port);
//    if (listenfd < 0) {
//        return -1;
//    }
//    printf("server listen on port %d, listenfd=%d ...\n", port, listenfd);
//    srv.onConnection = [](const SocketChannelPtr& channel) {
//        std::string peeraddr = channel->peeraddr();
//        if (channel->isConnected()) {
//            printf("%s connected! connfd=%d\n", peeraddr.c_str(), channel->fd());
//        } else {
//            printf("%s disconnected! connfd=%d\n", peeraddr.c_str(), channel->fd());
//        }
//    };
//    srv.onMessage = [](const SocketChannelPtr& channel, Buffer* buf) {
//        // echo
//        channel->write(buf);
//    };
//    srv.setThreadNum(4);
//    srv.start();

//    while (1) hv_sleep(1);
//    return 0;
//}

#include "hv/HttpServer.h"

#include <QCoreApplication>
#include <QString>
#include <QDebug>


#include "test01.h"

int main() {
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
