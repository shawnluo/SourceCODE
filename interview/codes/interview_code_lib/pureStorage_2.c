/*
                                                 event_fired()
                                                      |
                                                      |
 ----------------------------------------------------------------------------->time
        |                         |                  cb2()            |
        |                         |                  cb1()            |
register_callback(cb1)    register_callback(cb2)              register_callback(cb3)
                                                                       cb3()
*/

Stack st;   // push, pop, isEmpty
/*  push(T obj) -> void
    pop() -> obj
    isEmpty() -> bool
    
    The stack is atomic (concurrent_stack) -> supports multiple read/write at the same time
*/

atomic Bool fired = 0;


void register_callback(callback_t cb)
{
    // fill this in
    //cb();
    
    // thread 1
    pthread_mutex_lock();
    if(fired == 0)       //event is NOT fired, then push to stack
    
        st.push(cb);   
        pthread_mutex_unlock();
        //switched
    else  //fired == 1                  //Event fired, then just execute
        cb();       // 0 100, 200,    1000
                    // 0              1000

}
 
void event_fired()
{
    // thread 2
    fired = 1;
    pthread_mutex_lock();
    pthread_mutex_unlock();   
    //switched 
    // fill this in
    while(!isEmpty)
    {
        fun = pop();
        fun();
    }

    
    
}