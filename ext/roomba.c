#include "ruby.h"
#include "roombalib.h"

static VALUE cRoomba;

static void 
roomba_destroy(Roomba *roomba)
{
        roomba_free(roomba);
}

static VALUE 
roomba_new(VALUE klass, VALUE rb_portname)
{
    const char *portname;
    struct Roomba *roomba;

    portname = STR2CSTR(rb_portname);
    roomba = roomba_init(portname);
    return Data_Wrap_Struct(klass, 0, roomba_destroy, roomba);
}

static VALUE 
close(VALUE self)
{
    struct Roomba *roomba;

    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_close(roomba);
    return Qnil;
}

static VALUE 
valid(VALUE self)
{
    struct Roomba *roomba;

    Data_Get_Struct(self, struct Roomba, roomba);
    return INT2NUM(roomba_valid(roomba));
}

static VALUE 
get_portpath(VALUE self)
{
    struct Roomba *roomba;

    Data_Get_Struct(self, struct Roomba, roomba);
    return rb_str_new2(roomba_get_portpath(roomba));
}

static VALUE 
send(VALUE self, VALUE rb_cmd, VALUE rb_len)
{
    struct Roomba *roomba;
    const uint8_t *cmd;
    int len;

    cmd = STR2CSTR(rb_cmd);
    len = NUM2INT(rb_len);
    Data_Get_Struct(self, struct Roomba, roomba);

    return INT2NUM(roomba_send(roomba, cmd, len));
}

static VALUE 
drive(VALUE self, VALUE rb_vel, VALUE rb_rad)
{
    struct Roomba *roomba;
    int vel, rad;

    vel = NUM2INT(rb_vel);
    rad = NUM2INT(rb_rad);
    Data_Get_Struct(self, struct Roomba, roomba);

    roomba_drive(roomba, vel, rad);
    return Qnil;
}

static VALUE 
stop(VALUE self)
{
    struct Roomba *roomba;

    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_stop(roomba);
    return Qnil;
}

static VALUE 
forward(VALUE self)
{
    struct Roomba *roomba;

    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_forward(roomba);
    return Qnil;
}

static VALUE 
forward_at(VALUE self, VALUE rb_vel)
{
    struct Roomba *roomba;
    int vel;

    vel = NUM2INT(rb_vel);
    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_forward_at(roomba, vel);
    return Qnil;
}

static VALUE 
backward(VALUE self)
{
    struct Roomba *roomba;

    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_backward(roomba);
    return Qnil;
}

static VALUE 
backward_at(VALUE self, VALUE rb_vel)
{
    struct Roomba *roomba;
    int vel;

    vel = NUM2INT(rb_vel);
    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_backward_at(roomba, vel);
    return Qnil;
}

static VALUE 
spinleft(VALUE self)
{
    struct Roomba *roomba;

    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_spinleft(roomba);
    return Qnil;
}

static VALUE 
spinleft_at(VALUE self, VALUE rb_vel)
{
    struct Roomba *roomba;
    int vel;

    vel = NUM2INT(rb_vel);
    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_spinleft_at(roomba, vel);
    return Qnil;
}

static VALUE 
spinright(VALUE self)
{
    struct Roomba *roomba;

    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_spinright(roomba);
    return Qnil;
}

static VALUE 
spinright_at(VALUE self, VALUE rb_vel)
{
    struct Roomba *roomba;
    int vel;

    vel = NUM2INT(rb_vel);
    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_spinright_at(roomba, vel);
    return Qnil;
}

static VALUE 
set_velocity(VALUE self, VALUE rb_vel)
{
    struct Roomba *roomba;
    int vel;

    vel = NUM2INT(rb_vel);
    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_set_velocity(roomba, vel);
    return Qnil;
}

static VALUE 
get_velocity(VALUE self)
{
    struct Roomba *roomba;

    Data_Get_Struct(self, struct Roomba, roomba);
    return INT2NUM(roomba_get_velocity(roomba));
}

static VALUE 
play_note(VALUE self, VALUE rb_note, VALUE rb_duration)
{
    struct Roomba *roomba;
    uint8_t note, duration;

    note = NUM2INT(rb_note);
    duration = NUM2INT(rb_duration);
    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_play_note(roomba, note, duration);
    return Qnil;
}

static VALUE 
set_motors(VALUE self, VALUE rb_mainbrush, VALUE rb_vacuum, 
           VALUE rb_sidebrush)
{
    struct Roomba *roomba;
    uint8_t mainbrush, vacuum, sidebrush;

    mainbrush = NUM2INT(rb_mainbrush);
    vacuum = NUM2INT(rb_vacuum);
    sidebrush = NUM2INT(rb_sidebrush);
    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_set_motors(roomba, mainbrush, vacuum, sidebrush);
    return Qnil;
}

static VALUE
set_leds(VALUE self, VALUE rb_status_green, VALUE rb_status_red,
         VALUE rb_spot, VALUE rb_clean, VALUE rb_max, VALUE rb_dirt,
         VALUE rb_power_color, VALUE rb_power_intensity)
{
    struct Roomba *roomba;
    uint8_t status_green, status_red, spot, clean, max, dirt;
    uint8_t power_color, power_intensity;

    status_green = NUM2INT(rb_status_green);
    status_red = NUM2INT(rb_status_red);
    spot = NUM2INT(rb_spot);
    clean = NUM2INT(rb_clean);
    max = NUM2INT(rb_max);
    dirt = NUM2INT(rb_dirt);
    power_color = NUM2INT(rb_power_color);
    power_intensity = NUM2INT(rb_power_intensity);
    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_set_leds(roomba, status_green, status_red, spot, clean,
                    max, dirt, power_color, power_intensity);
    return Qnil;
}

static VALUE
vacuum(VALUE self, VALUE rb_state)
{
    struct Roomba *roomba;
    uint8_t state;

    state = NUM2INT(rb_state);
    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_vacuum(roomba, state);
    return Qnil;
}

static VALUE
read_sensors(VALUE self)
{
    struct Roomba *roomba;

    Data_Get_Struct(self, struct Roomba, roomba);
    return INT2NUM(roomba_read_sensors(roomba));
}

static VALUE
print_sensors(VALUE self)
{
    struct Roomba *roomba;

    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_print_sensors(roomba);
    return Qnil;
}

static VALUE
print_raw_sensors(VALUE self)
{
    struct Roomba *roomba;

    Data_Get_Struct(self, struct Roomba, roomba);
    roomba_print_raw_sensors(roomba);
    return Qnil;
}

static VALUE
delay(VALUE self, VALUE rb_millisecs)
{
    int millisecs;

    millisecs = NUM2INT(rb_millisecs);
    roomba_delay(millisecs);
    return Qnil;
}

void Init_roomba(){
    cRoomba = rb_define_class("Roomba", rb_cObject);
    rb_define_singleton_method(cRoomba, "new", roomba_new, 1);
    rb_define_method(cRoomba, "close", close, 0);
    rb_define_method(cRoomba, "valid", valid, 0);
    rb_define_method(cRoomba, "get_portpath", get_portpath, 0);
    rb_define_method(cRoomba, "send", send, 2);
    rb_define_method(cRoomba, "drive", drive, 2);
    rb_define_method(cRoomba, "stop", stop, 0);
    rb_define_method(cRoomba, "forward", forward, 0);
    rb_define_method(cRoomba, "forward_at", forward_at, 1);
    rb_define_method(cRoomba, "backward", backward, 0);
    rb_define_method(cRoomba, "backward_at", backward_at, 1);
    rb_define_method(cRoomba, "spinleft", spinleft, 0);
    rb_define_method(cRoomba, "spinleft_at", spinleft_at, 1);
    rb_define_method(cRoomba, "spinright", spinright, 0);
    rb_define_method(cRoomba, "spinright_at", spinright_at, 1);
    rb_define_method(cRoomba, "set_velocity", set_velocity, 1);
    rb_define_method(cRoomba, "get_velocity", get_velocity, 0);
    rb_define_method(cRoomba, "play_note", play_note, 2);
    rb_define_method(cRoomba, "set_motors", set_motors, 3);
    rb_define_method(cRoomba, "set_leds", set_leds, 8);
    rb_define_method(cRoomba, "vacuum", vacuum, 1);
    rb_define_method(cRoomba, "read_sensors", read_sensors, 0);
    rb_define_method(cRoomba, "print_sensors", print_sensors, 0);
    rb_define_method(cRoomba, "print_raw_sensors", print_raw_sensors, 0);
    rb_define_method(cRoomba, "delay", delay, 0);
}
