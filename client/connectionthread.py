import threading
import socket


class ConnectionThread(threading.Thread):

    DEFAULT_PORT = 27017
    DEFAULT_TIMEOUT = 1

    def __init__(self, ip):
        self.connection = socket.create_connection(self.parse_ip(ip), self.DEFAULT_TIMEOUT)
        self.running = True
        threading.Thread.__init__(self)

    @staticmethod
    def parse_ip(ip):
        if ip.count(":") > 0:
            address = ip.split(":", maxsplit=1)
            try:
                return address[0], int(address[1])
            except ValueError:
                raise ValueError("Incorrect value for port: {}".format(address[1]))
        else:
            return ip, ConnectionThread.DEFAULT_PORT

    def on_receive(self, msg):
        print(msg)

    def send(self, command, *args):

        self.connection.send("{command}{arglist}\r\n".format(
            command=command, arglist=''.join([":{}".format(arg) for arg in args])).encode())

    def run(self):
        while self.running:
            try:
                msg = self.connection.recv(4096)
                self.on_receive(msg)
                if len(msg) == 0:
                    raise ConnectionAbortedError("the server has closed the connection")
            except socket.timeout:
                continue
