#include "server.h"
#include "dataprocessor.h"

int main() {
    DataProcessor processor;
    Server server(8080, processor);

    server();

    return 0;
}