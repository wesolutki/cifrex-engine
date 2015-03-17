import requests
import json


def main():
    url = "http://localhost:4000/jsonrpc"
    headers = {'content-type': 'application/json'}

    payload = {
        "method": "foobar",
        "params": {
            "execLog": True,
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
        },
        "jsonrpc": "2.0",
        "id": 0,
    }

    response = requests.post(
        url, data=json.dumps(payload), headers=headers).json()

    import pprint
    pp = pprint.PrettyPrinter(indent=2)
    pp.pprint(response)

if __name__ == "__main__":
    main()
