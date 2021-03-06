#include "sys.h"
#include "debug.h"
#include <libcwd/buf2str.h>
#include "AsyncSerial.h"

#include <iostream>
#include <termios.h>

using namespace std;

void received(const char *data, unsigned int len)
{
    DoutEntering(dc::notice|flush_cf, "received(\"" << libcwd::buf2str(data, len) << "\", " << len << ")");

#if 0
    vector<char> v(data,data+len);
    for(unsigned int i=0;i<v.size();i++)
    {
        if(v[i]=='\n')
        {
            cout<<endl;
        } else {
            if(v[i]<32 || v[i]>=0x7f) cout.put(' ');//Remove non-ascii char
            else cout.put(v[i]);
        }
    }
    cout.flush();//Flush screen buffer
#endif
}

int main(int UNUSED_ARG(argc), char* UNUSED_ARG(argv)[])
{
    Debug(NAMESPACE_DEBUG::init());

    /*
    if(argc!=3)
    {
        cerr<<"Usage: serial port baudrate"<<endl<<
                "To quit type Ctrl-C x"<<endl<<
                "To send Ctrl-C type Ctrl-C Ctrl-C"<<endl;
        return 1;
    }

    termios stored_settings;
    tcgetattr(0, &stored_settings);
    termios new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_lflag &= (~ISIG); // don't automatically handle control-C
    new_settings.c_lflag &= ~(ECHO); // no echo
    tcsetattr(0, TCSANOW, &new_settings);*/

    //cout<<"\e[2J\e[1;1H"; //Clear screen and put cursor to 1;1

    try {
        //CallbackAsyncSerial serial(argv[1],stoi(argv[2]));
        CallbackAsyncSerial serial("/dev/ttyACM0",115200);
        Dout(dc::notice, "Calling serial.setCallback(received)");
        serial.setCallback(received);
        Dout(dc::notice, "Entering for loop...");
        for(;;)
        {
            if(serial.errorStatus() || serial.isOpen()==false)
            {
                Dout(dc::notice, "serial.errorStatus() == " << serial.errorStatus() << "; serial.isOpen() == " << serial.isOpen());
                Dout(dc::notice, "Error: serial port unexpectedly closed");
                break;
            }

        }
//        quit:
        Dout(dc::notice, "Calling serial.close()");
        serial.close();
    } catch (std::exception& e) {
        Dout(dc::notice, "Exception: " << e.what());
    }

    //tcsetattr(0, TCSANOW, &stored_settings);

    Dout(dc::notice, "Leaving main()...");
}
