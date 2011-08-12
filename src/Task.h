#ifndef APO_TASK_H
#define APO_TASK_H


namespace APO {

class Task {
  public:
    void update();


  private:
    Task * subTasks;

    Task * parentTask;

};

} // namespace APO
#endif
