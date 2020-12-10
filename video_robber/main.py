import cv2
import pyzbar.pyzbar as pyzbar
import qrcode
import requests
current = ""
def decodeDisplay(video):
    global current
    # 转为灰度图像
    gray = cv2.cvtColor(video, cv2.COLOR_BGR2GRAY)
    barcodes = pyzbar.decode(gray)
    for barcode in barcodes:
        # 提取二维码的位置,然后用边框标识出来在视频中
        (x, y, w, h) = barcode.rect
        cv2.rectangle(video, (x, y), (x + w, y + h), (0, 255, 0), 2)
        # 字符串转换
        barcodeData = barcode.data.decode("utf-8")
        barcodeType = barcode.type
        # 在图像上面显示识别出来的内容
        img = qrcode.make(barcodeData)
        # 打印识别后的内容
        print("[扫描结果] 二维码类别： {0} 内容： {1}".format(barcodeType, barcodeData))
        #cv2.imshow("cam", video)
        if barcodeData != current:
            current = barcodeData
            requests.post('http://10.20.38.233:3000', data={'code': barcodeData})


def detect(cameraID: int):
    cam = cv2.VideoCapture(cameraID)
    while True:
        # 读取当前帧
        ret, frame = cam.read()
        cv2.imshow('screen', frame)

        decodeDisplay(frame)
        # 按ESC键退出
        if cv2.waitKey(5) == 27:
            break
    cam.release()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    detect(0)