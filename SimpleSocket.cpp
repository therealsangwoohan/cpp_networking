#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>

class SimpleSocket {
private:
    struct sockaddr_in address;
    int sock;
    int connection;
public:
    SimpleSocket(int domain, int service, int protocol, int port, u_long interface) {
        address.sin_family = domain;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = htonl(interface);

        sock = socket(domain, service, protocol);
        test_connection(sock);

        connection = connect_to_network(sock, address);
    }

    virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;

    void test_connection(int item_to_test) {
        if (item_to_test < 0) {
            perror("Failed to connect...");
            exit(EXIT_FAILURE);
        }
    }

    struct sockaddr_in get_address() {
        return address;
    }

    int get_sock() {
        return sock;
    }

    int get_connection() {
        return connection;
    }
};