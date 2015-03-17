from werkzeug.wrappers import Request, Response
from werkzeug.serving import run_simple


from jsonrpc import JSONRPCResponseManager, dispatcher

import libpycifrex

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

@dispatcher.add_method
def foobar(**kwargs):
    print('\n\n')
    print("Received params: " + str(kwargs))

    engine = prepare_engine(kwargs)
    print("Engine params:" + str(engine))

    directory = kwargs.pop("katalog", "*").encode('ascii')  # TODO change default to sth smarter:)
    extensions = [val.encode('ascii') for val in kwargs.pop("extensions", [""])]
    print (extensions)
    results = run_engine(engine, directory, extensions)

    print("Not parsed params: " + str(kwargs))
    return results

@Request.application
def application(request):
    response = JSONRPCResponseManager.handle(
        request.data, dispatcher)
    return Response(response.json, mimetype='application/json')


if __name__ == '__main__':
    run_simple('localhost', 4000, application)

