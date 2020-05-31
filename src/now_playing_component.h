#ifndef NOW_PLAYING_COMPONENT
#define NOW_PLAYING_COMPONENT

#include <glibmm-2.4/glibmm.h>
#include <gtkmm-3.0/gtkmm/builder.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <gtkmm-3.0/gtkmm/scale.h>
#include <gtkmm-3.0/gtkmm/adjustment.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <sigc++/signal.h>

#include "track.h"

class NowPlayingComponent {

  public:
    typedef sigc::signal<void> sig_button;

    enum State {
      Disabled,
      Playing,
      Paused,
      Stopped
    };

    NowPlayingComponent(Glib::RefPtr<Gtk::Builder> builder);
    ~NowPlayingComponent();

    void set_track(const Track& track, const bool first, const bool last);
    void set_state(const State state);
    State get_state() const;
    void set_seconds(const float seconds);

    sig_button signal_prev();
    sig_button signal_playpause();
    sig_button signal_stop();
    sig_button signal_next();

  private:
    State _state;

    Gtk::Image* _albumArtImage;
    Gtk::Label* _trackTitleLabel;
    Gtk::Label* _trackArtistLabel;
    Gtk::Scale* _seekScale;
    Gtk::Button* _prevButton;
    Gtk::Button* _playPauseButton;
    Gtk::Button* _stopButton;
    Gtk::Button* _nextButton;

    sig_button _signal_prev;
    sig_button _signal_playpause;
    sig_button _signal_stop;
    sig_button _signal_next;

    void on_prev_button_clicked();
    void on_playpause_button_clicked();
    void on_stop_button_clicked();
    void on_next_button_clicked();
};

#endif // NOW_PLAYING_COMPONENT