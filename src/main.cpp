#include <cstdlib>
#include <sstream>

#include "file/File.h"
#include "sockets/Sockets.h"

using namespace std;

void testSocket();
void testFile();

int main(int argc, char** argv) {

    testSocket();
    testFile();

    cout << endl << "done." << endl;

    return 1;// cin.get();
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