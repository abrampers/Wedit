#include <iostream>  
#include <boost/asio.hpp>  

using namespace std;
using namespace boost::asio;

string read_(ip::tcp::socket & socket) {  
    boost::asio::streambuf buf;  
    boost::asio::read_until( socket, buf, "\n" );  
    string data = boost::asio::buffer_cast<const char*>(buf.data());  
    return data;  
}  

void send_(ip::tcp::socket & socket, const string& message) {  
    const string msg = message + "\n";  
    boost::asio::write( socket, boost::asio::buffer(message) );  
}

int main() {  
    boost::asio::io_service io_service;  
    ip::tcp::acceptor acceptor_(io_service, ip::tcp::endpoint(ip::tcp::v4(), 1234));  
    ip::tcp::socket socket_(io_service);  
    acceptor_.accept(socket_);  

    string message = read_(socket_);  
    cout << message << endl;  

    send_(socket_, "Hello From Server!");  
    cout << "Servent sent Hello message to Client!" << endl;  
    return 0;  
}
