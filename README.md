# cifrex-engine
You need:
- cmake
- g++ (withj c++11 support)
- re2
- boost (program_options, filesystem, python)
- python (now only 2.7)
- pip (or easy_install)
- python packages (sudo pip install package):
    - Werkzeug
    - json-rpc
    - requests

Download some library you want to check, to repos directory
ex.
mkdir repos
cd repos
curl http://ftp.piotrkosoft.net/pub/mirrors/ftp.apache.org//httpd/httpd-2.4.12.tar.bz2 -o httpd-2.4.12.tar.bz2
tar -xjvf httpd-2.4.12.tar.bz2

Run build-engine.sh
it will compile everything and start server

To run server:
cd server
python2 server.py

To run client example request:
python2 example-client/client.py

# TODOs
- https://pypi.python.org/pypi/python-jsonrpc

