#include <cstdlib>
#include <sstream>


#include "sockets/Sockets.h"
#include "file/File.h"

using namespace std;

void shortExample();
void testSocket();
void testFile();

int main(int argc, char** argv) {
	testSocket();
	testFile();

	return cin.get();
}


void shortExample() {
	try {
		Socket sock("tweakers.net", "80");

		OutputStream& out = sock.getOutputStream();
		InputStream& in   = sock.getInputStream();

		out.write("GET / HTTP1.0\n\rhost: tweakers.net\n\r\n\r");

		// Permit the server 1 second to come up with a reply.
		#ifdef WIN32
			Sleep(1000);
		#else
			usleep(1000);
		#endif

		int bytesAvailable = in.available();

		string buff = in.read(bytesAvailable);

		cout << buff << endl;
	} catch(const SocketException& ex) {
		cout << "err" << endl;
	}
}

void testSocket() {
try {
        cout << "Connecting to master server..." << endl;
        Socket socket("cis.gerardmeier.com", "8078");
        cout << "Connected. Checking for updates" << endl;

        OutputStream& out = socket.getOutputStream();
        InputStream& in = socket.getInputStream();

        out.write("{\"builds\":true}\n");

        bool isRunning = true;
        char current = 0;
        char prev    = 0;
        stringstream buff;
        do {
            int available = in.available();
            if(available > 0) {
                prev    = current;
                current = in.read();
                buff << current;
            }

            // Account for escaped newlines.
            isRunning = !(current == '\n' && prev != '\\');

        } while(isRunning);

        cout << " Reply from the server: " << endl;
        cout << buff.str() << endl;

    } catch(const SocketException& ex) {
        cout << "Unable to connect to master server." << endl;
    }
}

void testFile() {
	File file("./");


    file.size();

	if(!file.exists()) {
		cout << " path not found. " << endl;
	}

	cout << " Scanning " << file.getName() << " for files... " << endl;


    vector<File> files = file.listFiles();

    for(vector<File>::iterator it = files.begin(); it != files.end(); ++it) {
        File& file = (*it);
        cout << file.getName();

        if(file.isDirectory()) {
            cout << "/";
        }

        cout << endl;
	}

    cout << endl << "All done." << endl;
}