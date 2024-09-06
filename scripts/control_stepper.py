#!/usr/bin/env python3
import rospy
from std_msgs.msg import Int32

import threading


def cli_thread():
    # Create a publisher on the "/field" topic with the magField message type
    pub = rospy.Publisher('/stepper', Int32, queue_size=1)
    
    while not rospy.is_shutdown():
        inputs = []
    
        while not rospy.is_shutdown():
            user_input = input(f"Enter the number of steps you would like to take in mms: ")
            try:
                # Check for the "shutdown" command
                if user_input == "shutdown":
                    rospy.signal_shutdown("User requested shutdown")
                    break  # Exit the inner loop
                # Clean and check the user's input
                rospy.loginfo(f"Received: {user_input}")
                inputs.append(user_input)
                break  # Valid input was received; exit the inner loop
            except ValueError as e:
                rospy.logwarn(str(e))
        
        # rospy.loginfo(f"Received numbers: {inputs}")
        
        # Create a magField message and populate it with the user inputs
        step_msg = Int32()
        step_msg.data = int(user_input)
        # Publish the magField message on the "/field" topic
        pub.publish(step_msg)


def main():
    rospy.init_node('cli_listener', anonymous=True)
    print("This program listens for user commands to control a stepper motor.")
    print("To control the stepper motor, enter the number of steps you would like to take.")
    print("The number of steps should be a positive integer.")
    print("Enter 'shutdown' to exit.")

    # Start the CLI thread
    thread = threading.Thread(target=cli_thread)
    thread.start()
    
    rate = rospy.Rate(10)  # 10 Hz
    while not rospy.is_shutdown():
        # Main loop
        rate.sleep()

    # Ensure the thread is properly joined before exiting
    thread.join()

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass