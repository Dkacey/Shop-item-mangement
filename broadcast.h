#ifndef BROADCAST_H
#define BROADCAST_H

#include <QRunnable>

class TreeItem;

class Broadcast : public QRunnable
{
public:
    Broadcast(TreeItem *root);
    void run();

private:
    TreeItem *modelRoot;
};

#endif // BROADCAST_H
