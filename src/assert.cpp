namespace mylib {
    void assert(bool b, const char* err) {
        if(!b) {
            throw err;
        }
    }
}
