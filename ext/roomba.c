#include "ruby.h"

static VALUE rb_cRoomba;

static void rspike_mark(struct spike *s){
}

static void rspike_free(struct spike *s){
        spike_free(s);
}

static void roomba_allocate(VALUE klass){
    // fixme
    struct spike *s;

    s = new_spike();
    return Data_Wrap_Struct(klass, rspike_mark, rspike_free, s);
}

void Init_roomba(){
    rb_cRoomba = rb_define_class("Roomba", rb_cObject);
    rb_define_alloc_func(rb_cRoomba, roomba_allocate);
    //rb_define_method(rb_cSpike, "set_spike", rb_set_spike, 0);
    //rb_define_method(rb_cSpike, "binary", rb_binary, 1);
}
