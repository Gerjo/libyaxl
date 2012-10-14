#include <cstdlib>
#include <sstream>


#include "../yaxl.h"

#include "SomeThread.h"

using namespace yaxl;
using namespace file;
using namespace socket;
using namespace std;
using namespace concurrency;

void getWebsiteHttp();
void testSocket();
void scanFolder();
void readFile();
void writingFiles();
void createFolders();
void threading();

int main(int argc, char** argv) {
    threading();
    #ifdef WIN32
        return cin.get();
    #else
        return 0;
    #endif
}

void threading() {
    SomeThread t;
    t.start();
    t.join();
}

void getWebsiteHttp() {
	try {
		Socket sock("tweakers.net", "80");

		OutputStream& out = sock.getOutputStream();
		InputStream& in   = sock.getInputStream();

		out.write("GET / HTTP1.0\n\rhost: tweakers.net\n\r\n\r");

		// Permit the server 1 second to come up with a reply.
		#ifdef WIN32
			Sleep(500);
		#else
			usleep(500);
		#endif

		int bytesAvailable = in.available();

		string buff = in.read(bytesAvailable);
		cout << buff << endl;
        cout << "That where " << buff.size() << " bytes. (" << bytesAvailable << " bytes according to .available())" << endl;

	} catch(const SocketException& ex) {
		cout << "Exception: " << ex.what() << endl;
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
		cout << ex.what() << endl;
    }
}

void scanFolder() {
	File file("./");

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
        } else {
            cout << " (" << file.computeMD5() << ") ";
        }

        cout << endl;
	}

    cout << endl << "All done." << endl;
}

void readFile() {
    File file("meh");
    cout << "File size: " << file.size() << " bytes" << endl;

    cout << "first char: " << file.readSome(1) << endl;
    cout << "2nd and 3rd char: " << file.readSome(2) << endl;

    for(int i = 1; i < 3; ++i) {
        string tmp = file.readLine();
        cout << "Lines (" << i << "): '" << tmp << "' (" << tmp.length() << " bytes)" << endl;
    }

    cout << "What's left: " << file.readAll() << endl;

    cout << "File size: " << file.size() << " bytes" << endl;
}


void writingFiles() {
    cout << "Writing..." << endl;
    File valid("valid.txt");
    valid.createNewFile();
    valid.write(string("123456"));
    valid.write(string("mehmeh"));
    valid.append(string(" THE END"));
    valid.append(string(" of this file..."));


    cout << "Finished." << endl << endl;

    File invalid("invalid.txt");

    cout << " writing: " << endl;

    invalid.write(string("adasdasdsad"));

    cout << "done!" << endl;
}

void createFolders() {
    cout << "making dirs..." << endl;
    File folder("foo///bar///charlie");

    folder.mkDirs();

    cout << "done with that. " << endl;



    File toDelete("deleteme");
    cout << "deleted? " << (int)toDelete.remove();
}
