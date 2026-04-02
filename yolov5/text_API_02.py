import cv2
import torch
import requests
import time
import threading
import queue


# ================= 华为云配置 =================
class HuaweiCloudConfig:
    def __init__(self):
        # 填写配置信息
        self.iam_endpoint = "***"
        self.iot_endpoint = "***"
        self.project_id = "******"
        self.device_id = "******"

        # 认证信息
        self.iam_user = "****"
        self.iam_password = "****"
        self.domain_name = "*****"

        # Token相关
        self.x_auth_token = None
        self.token_expire = 0


config = HuaweiCloudConfig()


# ================= 华为云服务接口 =================
def get_cloud_token():
    """获取华为云访问令牌"""
    url = f"https://{config.iam_endpoint}/v3/auth/tokens"
    data = {
        "auth": {
            "identity": {
                "methods": ["password"],
                "password": {
                    "user": {
                        "domain": {"name": config.domain_name},
                        "name": config.iam_user,
                        "password": config.iam_password
                    }
                }
            },
            "scope": {
                "project": {
                    "id": config.project_id
                }
            }
        }
    }

    try:
        response = requests.post(url, json=data)
        if response.status_code == 201:
            config.x_auth_token = response.headers['X-Subject-Token']
            config.token_expire = time.time() + 86400  # 假设token有效期24小时
            print("华为云Token获取成功")
            return True
        print(f"Token获取失败: {response.text}")
    except Exception as e:
        print(f"Token请求异常: {str(e)}")
    return False


# ================= 华为云服务接口（保持原有参数）=================
def send_cloud_command(cmd_value):
    """向华为云发送设备命令（保留原有正确参数）"""
    if time.time() > config.token_expire and not get_cloud_token():
        return False

    url = f"https://{config.iot_endpoint}/v5/iot/{config.project_id}/devices/{config.device_id}/commands"
    headers = {
        "X-Auth-Token": config.x_auth_token,
        "Content-Type": "application/json"
    }

    # 保持原有正确的参数结构（根据原设备模型定义）
    payload = {
        "service_id": "control",  # 需与设备模型完全一致
        "command_name": "TTL",  # 需与设备模型定义的命令名称一致
        "paras": {
            "value": cmd_value  # 参数名称需与模型定义一致
        }
    }

    try:
        response = requests.post(url, headers=headers, json=payload)
        if response.status_code == 200:
            print(f"命令发送成功: {cmd_value}")
            return True
        print(f"命令发送失败[{response.status_code}]: {response.text}")
    except Exception as e:
        print(f"命令请求异常: {str(e)}")
    return False


# ================= 视频检测模块（添加防抖+状态变化检测）=================
class TTLDetector:
    def __init__(self):
        self.model = torch.hub.load('ultralytics/yolov5', 'custom',
                                    path='runs/train/exp4/weights/best.pt')
        self.model.conf = 0.35
        self.model.iou = 0.45

        # 新增状态跟踪参数（防抖机制）
        self.last_reported_state = None  # 上次成功上报的状态
        self.current_state = False  # 当前检测状态
        self.state_counter = 0  # 状态持续计数器
        self.state_threshold = 3  # 需要连续3帧确认

    def detect_ttl(self, frame):
        """执行检测并返回处理后的帧"""
        results = self.model(frame)
        new_state = any(self.model.names[int(det[5])] == 'TTL' for det in results.pred[0])

        # 防抖机制（连续3帧相同状态才确认）
        if new_state == self.current_state:
            self.state_counter = 0
        else:
            self.state_counter += 1

        # 确认状态变化
        if self.state_counter >= self.state_threshold:
            self._handle_state_change(new_state)
            self.current_state = new_state
            self.state_counter = 0

        return results.render()[0]

    def _handle_state_change(self, new_state):
        """处理实际状态变化（保留原有参数结构）"""
        if self.last_reported_state is None or new_state != self.last_reported_state:
            state_str = "ON" if new_state else "OFF"
            print(f"状态确认变化: {state_str}")
            command_queue.put(state_str)  # 把命令放入队列中，由另一个线程处理


# ================= 多线程部分 =================
def detection_thread(frame_queue, result_queue, detector):
    while True:
        if not frame_queue.empty():
            frame = frame_queue.get()
            processed_frame = detector.detect_ttl(frame)
            result_queue.put(processed_frame)


def command_sender_thread():
    while True:
        if not command_queue.empty():
            cmd = command_queue.get()
            send_cloud_command(cmd)
        time.sleep(0.1)  # 控制频率防止过载


# ================= 主函数 =================
if __name__ == "__main__":
    # 初始化华为云连接
    if not get_cloud_token():
        exit("华为云认证失败")

    # 初始化检测器
    detector = TTLDetector()

    # 初始化队列
    frame_queue = queue.Queue(maxsize=10)
    result_queue = queue.Queue(maxsize=10)
    command_queue = queue.Queue()

    # 启动子线程
    threading.Thread(target=detection_thread, args=(frame_queue, result_queue, detector), daemon=True).start()
    threading.Thread(target=command_sender_thread, daemon=True).start()

    # 初始化摄像头
    #cap = cv2.VideoCapture(" ***")
    cap = cv2.VideoCapture(" *** ")
    #cap = cv2.VideoCapture(0)
    cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)

    while True:
        ret, frame = cap.read()
        if not ret:
            print("视频流中断，尝试重连...")
            cap.release()
            cap = cv2.VideoCapture(0)
            continue

        # 放入检测线程队列
        if frame_queue.qsize() < 10:
            frame_queue.put(frame)

        # 显示结果
        if not result_queue.empty():
            rendered_frame = result_queue.get()
            cv2.imshow('TTL Detection', rendered_frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()