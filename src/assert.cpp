namespace mylib {
    void assert(bool b, const char* err) {
        if(!b) {
            throw err;
        }
    }

    void assert(bool b) {
        assert(b, "Unspecified error");
    }
}
