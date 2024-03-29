#ifndef					__EVENT_MANAGER_HH__
# define				__EVENT_MANAGER_HH__

#include                                <allegro5/allegro.h>
#include				"OptionManager.hpp"
#include				"Singleton.hpp"

class					EventManager : public Singleton<EventManager>
{
public:
  ~EventManager();
  bool					init()
  {
    if (!al_install_keyboard())
      return false;
    if (!al_install_mouse())
      return false;
    this->event_queue_ = al_create_event_queue();
    if (!this->event_queue_)
      return false;
    this->timer_ = al_create_timer(1.0f / 120.0f);
    if (!this->timer_)
      return false;
    if (!al_install_joystick())
      return false;
    al_register_event_source(this->event_queue_, al_get_keyboard_event_source());
    // al_register_event_source(this->event_queue_, al_get_joystick_event_source());
    al_register_event_source(this->event_queue_, al_get_mouse_event_source());
    al_register_event_source(this->event_queue_, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(this->event_queue_, al_get_timer_event_source(this->timer_));
    al_start_timer(this->timer_);

    return true;
  }

  void					uninit()
  {
    if (this->event_queue_)
      al_destroy_event_queue(this->event_queue_);
    if (this->timer_)
      al_destroy_timer(this->timer_);
    al_uninstall_keyboard();
    al_uninstall_mouse();
  }

  void					play()
  {
    bool				draw;
    ALLEGRO_EVENT			 ev;
    float				time;

    this->run_->setValue(true);
    draw = false;
    while (this->run_->getValue())
      {
	time = al_get_time();
	al_wait_for_event(this->event_queue_, &ev);
	if (ev.type == ALLEGRO_EVENT_TIMER)
	  {
	    draw = true;
	  }
	if (upt_)
	  this->upt_(time, ev);
	if (draw && al_is_event_queue_empty(this->event_queue_) && this->draw_)
	  {
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    this->draw_(time, ev);
	    al_flip_display();
	    draw = false;
	  }
	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	  {
	    this->stop();
	  }
      }
  }
  void					stop()
  {
    this->run_->setValue(false);
  }
  void					setUpdateLoop(void (fun)(float, const ALLEGRO_EVENT &))
  {
    this->upt_ = fun;
  }

  void					setDrawLoop(void (fun)(float, const ALLEGRO_EVENT &))
  {
    this->draw_ = fun;
  }

  void					setKeyLoop(void (fun)(float, const ALLEGRO_EVENT &))
  {
    this->key_ = fun;
  }

private:
  void					(*upt_)(float, const ALLEGRO_EVENT &ev);
  void					(*draw_)(float, const ALLEGRO_EVENT &ev);
  void					(*key_)(float, const ALLEGRO_EVENT &ev);
  ALLEGRO_EVENT_QUEUE			*event_queue_;
  ALLEGRO_TIMER				*timer_;
  OptionValue<bool>			*run_;
  EventManager() :
    upt_(NULL),
    draw_(NULL),
    key_(NULL),
    event_queue_(NULL),
    timer_(NULL),
    run_(NULL)
  {
    OptionManager::getInstance()->setOption<bool>("run", true);
    this->run_ = OptionManager::getInstance()->getOption<bool>("run");
  }
  friend class Singleton<EventManager>;
};

#endif					// __EVENT_MANAGER_HH__

