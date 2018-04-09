/* =====================================================================================================================
 * Пример SimpleActionServer с поддержкой отмены
 *
 * Все описание в комментах
 * =====================================================================================================================
 */


#include <ros/ros.h>
#include <actionlib_test/TestAction.h>
#include <actionlib/server/simple_action_server.h>
#include <string>

using namespace std;

// Должна ли новая задача прерывать текущую
#define CANCEL_ON_NEW

class TestServer
{
public:
    TestServer(ros::NodeHandle& nh, string server_name)
            :as_(nh, server_name, boost::bind(&TestServer::execute_cb, this, _1), false)
    {
        as_.registerPreemptCallback(boost::bind(&TestServer::preempt_cb, this));
        as_.start();
    }


private:

    void preempt_cb()
    {
        // Либо отправлена новая задача, либо текущая задача отменена
        ROS_WARN_STREAM("preempt_cb");
    }

    void execute_cb(const actionlib_test::TestGoalConstPtr& goal)
    {
        ros::Rate rate(1);
        ROS_INFO_STREAM("execute_cb: New goal: " << goal->a);

        // Выполняем задачу
        for(int i = 0; i<goal->a; i++)
        {

            if(!ros::ok())
            {
                // Если нода завершилась, то прерываем текущую задачу
                result_.b = -1;
                as_.setAborted(result_, "Server node is stopped");
                ROS_INFO("Stopping...");
                return;
            }

            // Проверяем новую задачу или отмену
            if(as_.isPreemptRequested() && as_.isNewGoalAvailable())
            {
                // Текущая задача была "вытеснена" (preempted) и доступна новая - значит поставлена новая задача
#ifdef CANCEL_ON_NEW
                // Текущая задача будет преврана и начата новая
                ROS_WARN("New goal available, but current is not finished. Cancel old, start new");
                result_.b = -1;
                as_.setPreempted(result_, "New task received");

                i = 0; // Типо начали новую задачу
                return;
#else
                // Текущая задача будет продолжена, новая начнется автоматически после ее завершения
                // ВНИМАНИЕ: В таком режиме не работает отмена, если ожидает еще одна задача!!!
                // Потому что новая задача устанавливает флаг isNewGoalAvailable
                ROS_WARN("New goal available, but current is not finished. WAITING");
#endif
            }
            else if(as_.isPreemptRequested())
            {
                // Текущая задача была "вытеснена" (preempted) и нет новой - значит текущая задача просто прервана
                // Прерываем текущую задачу
                ROS_WARN("Current goal canceled");
                result_.b = -1;
                as_.setAborted(result_, "Cancelled");
                return;
            }

            ROS_INFO_STREAM(i);
            feedback_.c = i;
            as_.publishFeedback(feedback_);
            rate.sleep();
        }

        // Готово
        result_.b = goal->a;
        as_.setSucceeded(result_, "zaebis");
        ROS_INFO_STREAM("Result sent for goal " << goal->a);
    }


    actionlib::SimpleActionServer<actionlib_test::TestAction> as_;
    actionlib_test::TestResult result_;
    actionlib_test::TestFeedback feedback_;

};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "server");
    ros::NodeHandle nh;
    TestServer server(nh, "server");
    ros::spin();

    return 0;
}