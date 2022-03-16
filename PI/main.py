import os
import selectors
import socket
import types


def prec():
    HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
    PORT = 65432  # Port to listen on (non-privileged ports are > 1023)

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))  # Occupa la porta e l'ip
        s.listen()  # aspetta una connnesione
        conn, addr = s.accept()  # una volta ricevuta mette in conn e addr i valori di chi si connette e della stream
        with conn:  # error handling
            print('Connected by', addr)  # Debug print

            # Server script

            while True:
                try:
                    data = conn.recv(1024)  # Riceve i dati
                except:
                    print("stu strunz si voleva disconnettere")
                if not data:  # disconnessione

                    break
                conn.sendall(data)


def service_connection(key, mask):
    sock = key.fileobj
    data = key.data
    
    if mask & selectors.EVENT_READ:
        try:
            recv_data = sock.recv(1024)  # Riceve un pacchetto di 1024
        except ConnectionResetError:
            print("[ERROR] stu strunz s'volev disconnett (Connection reset by peer)")
            recv_data = None  # Avoiding fake data from coming in
        except:
            print("[ERROR] E che cazz (Probabilmente no route to host)")
            recv_data = None

        if recv_data:
            # data.outb += recv_data # <-- prec
            data.outb = recv_data  # aggiunge ad outb di data il dato ricevuto
            print('Ricevuto: ', repr(data.outb), 'da', data.addr[0])
        else:  # se non riceve nulla da leggere allora c'è stata una disconnessione
            print('Disconnection from: ', data.addr)
            sel.unregister(sock)  # disassocia l'evento
            sock.close()  # chiude il socket (key)

    if mask & selectors.EVENT_WRITE:  # controlla che sia pronto per scrivere

        if data.outb:  # RICEVE UN MESSAGGIO ######################################################################

            if data.outb is None:
                return

            #database


        data.outb = None



def accept_wrapper(sock):
    conn, addr = sock.accept()  # Should be ready to read
    print('accepted connection from', addr)
    conn.setblocking(False)  # imposta la CONNESSIONE come non bloccante
    data = types.SimpleNamespace(addr=addr, inb=b'', outb=b'')  # crea un qualcosa che tenga il dato
    events = selectors.EVENT_READ | selectors.EVENT_WRITE  # prepara la connessione per lettura e scrittura
    sel.register(conn, events, data=data)  # registra la connessione come evento nei selector


if __name__ == "__main__":

    host = "10.11.137.56"
    port = 8123

    sel = selectors.DefaultSelector()  # inizializza il selettore
    # ...
    lsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # crea il socket
    lsock.bind((host, port))  # occupa le porte e ip
    lsock.listen()  # comincia l'ascolto
    print('listening on', (host, port))
    lsock.setblocking(False)  # L'ascolto non è più bloccante
    sel.register(lsock, selectors.EVENT_READ, data=None)  # registra l'evento per essere controllato dal selettore

    while True:
        events = sel.select(timeout=None)  # Tempo di attesa infinito
        for key, mask in events:  # key = socket
            if key.data is None:  # connessione in arrivo
                accept_wrapper(key.fileobj)  # accetta connessione
            else:
                service_connection(key, mask)  # gestione connessione
