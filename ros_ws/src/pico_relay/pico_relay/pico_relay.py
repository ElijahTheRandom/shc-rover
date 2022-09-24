import rclpy
from rclpy.node import Node

from std_msgs.msg import String

class SerialPublisher(Node):
    def __init__(self):
        super().__init__("serial_publisher")
        self.publisher = self.create_publisher(String, '/pico/serial', 10)
        

def main(args=None):
    rclpy.init(args=args)

    serial_pub = SerialPublisher()

    rclpy.spin(serial_pub)


if __name__ == '__main__':
    main()
