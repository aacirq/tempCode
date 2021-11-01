import socket

if __name__ == "__main__":
    # addr = socket.getaddrinfo("www.baidu.com", 80)
    s = socket.socket()
    s.connect(("www.baidu.com", 80))
    msg = "GET /index.html HTTP/1.0\r\nHost: www.baidu.com\r\n\r\n"
    s.send(msg.encode('utf-8'))
    data = s.recv(4096)
    print(data.decode())
 