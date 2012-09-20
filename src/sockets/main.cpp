#include <cstdlib>
#include <sstream>

#include "Socket.h"
#include "OutputStream.h"
#include "InputStream.h"

using namespace std;

void shortExample();

int main(int argc, char** argv) {
	shortExample();
	return cin.get();
    Socket sock("tweakers.net", "80");
    //Socket sock("localhost", "80");
    
    OutputStream& out = sock.getOutputStream();
    InputStream& in   = sock.getInputStream();
    
    out.write("GET / HTTP1.0\n\rhost: tweakers.net\n\r\n\r");
    
    stringstream result;
    
    while(true){
        //usleep(1);
        int av = in.available();
        if(av > 0) {
            result << in.read(1024);
        }
        
        string comp = "</html>";
        
        // This mess does a "endsWidth" test.
        if(result.str().length() > comp.length() &&
                result.str().substr(
                    result.str().length() - comp.length(), 
                    comp.length()
                ).compare(comp) == 0) {
            break;
        }
    }

    cout << result.str() << endl;
    
    sock.close();
    cout.flush();
    cout << endl << "Reached a clean ending." << endl;
    
    return 1;// cin.get();
}


void shortExample() {
	Socket sock("tweakers.net", "80");
    
    OutputStream& out = sock.getOutputStream();
    InputStream& in   = sock.getInputStream();

	out.write("GET / HTTP1.0\n\rhost: tweakers.net\n\r\n\r");

	// Permit the server 1 second to come up with a reply.
	Sleep(1000);

	int bytesAvailable = in.available();

	string buff = in.read(bytesAvailable);

	cout << buff << endl;
}

