import rospy
from std_msgs.msg import UInt32
from ros_coils.msg import magField

class SamplingFunc:


    def __init__(self):
        rospy.init_node('my_node', anonymous=True)

        # Create publishers for the "servo" and "field" topics
        self.servo_pub = rospy.Publisher('servo', UInt32, queue_size=10)
        self.field_pub = rospy.Publisher('field', magField, queue_size=10)

        # Create subscribers for the "inputMotor" and "fieldIn" topics
        self.input_motor_sub = rospy.Subscriber('inputMotor', UInt32, self.input_motor_callback)
        self.field_in_sub = rospy.Subscriber('fieldIn', magField, self.field_in_callback)

        self.rate = rospy.Rate(10)  # 10 Hz

        # Create a rosparam for ts
        self.ts = rospy.get_param('~ts', default=1)  # Default value is 1

    def input_motor_callback(self, msg):
        # Callback function for the "inputMotor" topic
        # Do something with the received message
        pass

    def field_in_callback(self, msg):
        # Callback function for the "fieldIn" topic
        # Do something with the received message
        pass

    def run(self):
        while not rospy.is_shutdown():
            # Publish to the "servo" topic
            servo_msg = UInt32()
            # Set the value of the message
            self.servo_pub.publish(servo_msg)

            # Publish to the "field" topic
            field_msg = magField()
            # Set the value of the message
            self.field_pub.publish(field_msg)

            self.rate.sleep()

if __name__ == '__main__':
    sampling_func = SamplingFunc()
    sampling_func.run()
