#include <boost/interprocess/sync/named_mutex.hpp>

using namespace boost::interprocess;

named_mutex* uniqInstance = NULL;

void __bst_create(const char* name)
{
    try
    {
        uniqInstance = new named_mutex(open_or_create, name);
    }
    catch (interprocess_exception& e)
    {
        printf("ERROR %s\n", e.what());
    }
    if (uniqInstance == NULL)
        exit(-22);
}

bool __bst_tryToLock()
{
    if (uniqInstance)
        return uniqInstance->try_lock();
    else
        return true;
}

void __bst_unlock()
{
    if (uniqInstance)
        uniqInstance->unlock();
}
