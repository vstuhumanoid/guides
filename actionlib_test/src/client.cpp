/* =====================================================================================================================
 * Пример SimpleActionClient
 * =====================================================================================================================
 */

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib_test/TestAction.h>

void send(actionlib::SimpleActionClient<actionlib_test::TestAction>& ac, int value, int waiting_time)
{
    actionlib_test::TestGoal goal;
    goal.a = value;
    ROS_INFO("Sending goal...");
    ac.sendGoal(goal);

    bool is_ok = ac.waitForResult(ros::Duration(waiting_time));
    if(is_ok)
    {
        auto state = ac.getState();
        if(state.state_ == state.SUCCEEDED)
        {
            auto result = ac.getResult();
            ROS_INFO_STREAM("State: " << state.toString() << ", " << state.getText());
            ROS_INFO_STREAM("Result: " << result->b);
        }
        else
        {
            ROS_WARN_STREAM("State: " << state.toString() << ", " << state.getText());
        }

    }
    else
    {
        ROS_WARN("Timeout");
        ac.cancelGoal();
        ac.waitForResult();
        auto state = ac.getState();
        auto result = ac.getResult();
        ROS_INFO_STREAM("State: " << state.toString() << ", " << state.getText());
        ROS_INFO_STREAM("Result: " << result->b);
    }
}

int main(int argc, char** argv)
{
    if(argc!=4)
    {
        ROS_ERROR("Not enough arguments");
        ROS_ERROR("Usage: client <name> <task size> <wait time>");
        return -1;
    }

    ros::init(argc, argv, argv[1]);
    actionlib::SimpleActionClient<actionlib_test::TestAction>  ac("server", true);

    int task_count = std::stoi(argv[2]);
    int wait = std::stoi(argv[3]);

    ROS_INFO("Waiting for action server to start...");
    ac.waitForServer();
    ROS_INFO("Server started");

    send(ac, task_count, wait);

    return 0;
}