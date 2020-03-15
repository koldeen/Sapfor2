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
    return uniqInstance->try_lock();
}

void __bst_unlock()
{
    uniqInstance->unlock();
}
