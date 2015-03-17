import pyjsonrpc

if __name__ == "__main__":

    http_client = pyjsonrpc.HttpClient(url = "http://localhost:4000",)

    payload = {"execLog": True,
            "printOutput": True,
            "toDb": True,
            "resultName": "thats my name",
            "credit": "To ja",
            "langId": 136,
            "email": "moj mail",
            "filtrName": "moja nazwa filtru",
            "filtrDescription": "a to opis",
            "filtrId": 753,
            "extensions": [".h", ".c"],
            "katalog": "../repos/",
            "value1": "(?P<v1>strcpy.*\))",
            }

    print(http_client.call("search", payload))

