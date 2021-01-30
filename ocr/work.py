from pathlib import Path
import requests, time

root = Path('./')
for i in root.iterdir():
    if i.is_dir() is False:
        continue

    print(i)

    for j in i.iterdir():
        if str(j).endswith('.txt') is False:
            continue
        txt = ''
        with j.open() as f:
            txt = f.read()

        filename = j.stem

        number = int(filename[:filename.find('.')])

        data = {
                'number': number,
                'text': txt,
                'name': str(i)
        }

        requests.post('http://192.168.1.9:8099/api/data', json=data)

        # sleep for preventing running out of connections
        time.sleep(0.2)

