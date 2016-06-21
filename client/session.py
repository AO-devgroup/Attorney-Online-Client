from connectionthread import ConnectionThread
import contentmanager


class Session:

    # Constants
    LOAD_ADDON = "LA"
    SET_LAYER = "SL"
    REMOVE_LAYER = "RL"
    ADD_WINDOW = "AW"
    REMOVE_WINDOW = "RW"
    GO_TO = "GT"

    def __init__(self, ip, handshake_message=""):
        self.connection = ConnectionThread(ip)
        self.connection.send("HS", handshake_message)
        self.connection.on_receive = self.receive
        self.connection.start()

    def receive(self, message, *args):
        if message == self.LOAD_ADDON:
            print(contentmanager.has_addon(args[0], args[1]))
        elif message == self.SET_LAYER:
            pass
        elif message == self.REMOVE_LAYER:
            pass
        elif message == self.ADD_WINDOW:
            pass
        elif message == self.REMOVE_WINDOW:
            pass
        elif message == self.GO_TO:
            pass

a = Session("127.0.0.1")
