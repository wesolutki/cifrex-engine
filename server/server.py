import pyjsonrpc
import libpycifrex
import datetime

def prepare_engine(kwargs):
    def load_params(name, max_number, kwargs):
        def load_pattern(regexes):
            return [libpycifrex.Vex(regex.encode("ascii")) for regex in regexes if regex!=""]
        return load_pattern([kwargs.pop(name + str(n), "") for n in range(1, max_number + 1)])
    values = load_params("value", 3, kwargs)
    true = load_params("true", 3, kwargs)
    false = load_params("false", 3, kwargs)
    print(values)
    engine = libpycifrex.Engine(values)
    return engine

def run_engine(engine, path, extensions):
    return engine.search(path, extensions)

def searchRequest(kwargs):
    time1 = datetime.datetime.now()
    print('\n\n')
    print("Received params: " + str(kwargs))

    engine = prepare_engine(kwargs)
    print("Engine params:" + str(engine))

    directory = kwargs.pop("katalog", "*").encode('ascii')  # TODO change default to sth smarter:)
    extensions = [val.encode('ascii') for val in kwargs.pop("extensions", [""])]
    print (extensions)
    results = run_engine(engine, directory, extensions)

    print("Not parsed params: " + str(kwargs))
    time2 = datetime.datetime.now()
    elapsedTime = time2 - time1
    print("Elapsed: " + str(elapsedTime.total_seconds()) + " seconds")
    return results

class RequestHandler(pyjsonrpc.HttpRequestHandler):

    @pyjsonrpc.rpcmethod
    def search(self, kwargs):
        """Test method"""
        print(kwargs)
        return searchRequest(kwargs)

if __name__ == '__main__':
    http_server = pyjsonrpc.ThreadingHttpServer(
        server_address = ('localhost', 4000),
        RequestHandlerClass = RequestHandler)
    http_server.serve_forever()

