import rospy
import numpy as np
from std_msgs.msg import UInt32
from std_msgs.msg import Int32
from ros_coils.msg import magField
# from ros_coils.msg import magFieldArray


class SamplingFunc:

    def __init__(self):
        rospy.init_node('wave_sampling_node', anonymous=True)

        # Create publishers for the "servo" and "field" topics
        self.servo_pub = rospy.Publisher('servo', UInt32, queue_size=10)
        self.field_pub = rospy.Publisher('field', magField, queue_size=10)
        self.stepper_pub = rospy.Publisher('stepper', Int32, queue_size=10)

        # Create a rosparam for ts
        self.ts = rospy.get_param('~ts', default=4)  # Default value is 4
        if (self.ts < 3 or self.ts > 21):
            if (self.ts % 2 == 0):
                self.ts = self.ts - 1
        freq = self.ts / 3
        self.rate = rospy.Rate(freq)  # 10 Hz

        self.field_min = rospy.get_param(
            '/sampler/field_min', default=[0, 0, 0])  # Default value is [0, 0, 0]
        self.field_max = rospy.get_param(
            '/sampler/field_max', default=[0, 0, 0])  # Default value is [0, 0, 0]
        # Default value is [0, 0, 0, 0]
        self.step_min = rospy.get_param(
            '/sampler/step_min', default=[0, 0, 0, 0])
        # Default value is [0, 0, 0, 0]
        self.step_max = rospy.get_param(
            '/sampler/step_max', default=[0, 0, 0, 0])

        self.bxs = self.getInterval(
            self.ts, self.field_min[0], self.field_max[0])
        self.bys = self.getInterval(
            self.ts, self.field_min[1], self.field_max[1])
        self.bzs = self.getInterval(
            self.ts, self.field_min[2], self.field_max[2])
        self.field_to_pub = np.array([self.bxs, self.bys, self.bzs])

        self.step_0 = self.getInterval(
            self.ts, self.step_min[0], self.step_max[0])
        self.step_1 = self.getInterval(
            self.ts, self.step_min[1], self.step_max[1])
        self.step_2 = self.getInterval(
            self.ts, self.step_min[2], self.step_max[2])
        self.step_3 = self.getInterval(
            self.ts, self.step_min[3], self.step_max[3])

        # print("field_to_pub: ", self.field_to_pub)

    def getInterval(self, ts, min, max):
        # print arguments
        dividend = int(np.floor((ts+1) / 2))  # Number of intervals
        # discretised left hand of the curve
        disc_interval = np.linspace(min, max, dividend)
        disc_interval = np.concatenate(
            (disc_interval, disc_interval[::-1][1:]))  # append right hand
        return disc_interval

    def assembleServoInput(self, idx):
        s0 = int(self.step_0[idx] * 255 / 100)
        s1 = int(self.step_1[idx] * 255 / 100)
        s2 = int(self.step_2[idx] * 255 / 100)
        s3 = int(self.step_3[idx] * 255 / 100)
        uint32_value = (s0 << 24) | (s1 << 16) | (s2 << 8) | s3
        msg = UInt32()
        msg.data = uint32_value
        return msg

    def run(self):
        i = 0
        counter = 0
        # stepperOut = True
        while not rospy.is_shutdown():
            servo_msg = UInt32()
            field_msg = magField()
            stepper_msg = Int32()
            # print("i: ", i, "counter: ", counter)
            # if(counter == 0):
            #     print("inserting")

                # counter = counter + 1

            servo_msg = self.assembleServoInput(i)
            # print("servo_msg: ", servo_msg)
            field_msg.bx = self.field_to_pub[0, i]
            field_msg.by = self.field_to_pub[1, i]
            field_msg.bz = self.field_to_pub[2, i]

            # Publish to the "servo" topic
            self.servo_pub.publish(servo_msg)
            # Set the value of the message
            self.field_pub.publish(field_msg)

            i = i + 1
 
            if (i == self.ts):
                i = 1
                stepper_msg.data = 5
                self.stepper_pub.publish(stepper_msg)
                # counter = counter + 1
                # if(counter == 10):
                #     counter = 0
            self.rate.sleep()


if __name__ == '__main__':
    sampling_func = SamplingFunc()
    sampling_func.run()
