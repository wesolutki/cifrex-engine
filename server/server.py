import pyjsonrpc
import libpycifrex
import datetime

from memoized import memoized

@memoized
def load_file(path):
    return open(path, 'r').read()

def load_directory_files(path, extensions):
    import fnmatch
    import os

    matches = []
    for root, dirnames, filenames in os.walk(path):
        for extension in extensions:
            for filename in fnmatch.filter(filenames, extension):
                matches.append(os.path.join(root, filename))
    print("Loaded %d file paths" % len(matches))
    return matches;

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

def run_engine(engine, directory, extensions):
    print("Run engine (file to c++)): " + str(engine))
    res = []
    for path in load_directory_files(directory, extensions):
        v = engine.searchInFile(load_file(path))#open(path, 'r').read())
        if v:
            res.append((path, v))
    print("Matches count: %d" % len(res))
    return res

def run_engine_scan(engine, directory, extensions):
    print("Run engine (directory to c++)): " + str(engine))
    return engine.search(directory, extensions)

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

