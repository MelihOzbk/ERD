#ifndef OtonomGorev_h
#define OtonomGorev_h


class OtonomGorev
{
private:
    bool armstate=false;
    /* data */
public:
    void IlkGorev();
    void SetARMState(bool state);
};

#endif