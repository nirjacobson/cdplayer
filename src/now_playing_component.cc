#include "now_playing_component.h"

NowPlayingComponent::NowPlayingComponent(Glib::RefPtr<Gtk::Builder> builder)
  : _state(State::Stopped) {
  builder->get_widget("albumArtImage", _albumArtImage);
  builder->get_widget("trackTitleLabel", _trackTitleLabel);
  builder->get_widget("trackArtistLabel", _trackArtistLabel);
  builder->get_widget("seekScale", _seekScale);
  builder->get_widget("seekScale", _seekScale);
  builder->get_widget("prevButton", _prevButton);
  builder->get_widget("playPauseButton", _playPauseButton);
  builder->get_widget("stopButton", _stopButton);
  builder->get_widget("nextButton", _nextButton);

  _prevButton->signal_clicked().connect(sigc::mem_fun(this, &NowPlayingComponent::on_prev_button_clicked));
  _playPauseButton->signal_clicked().connect(sigc::mem_fun(this, &NowPlayingComponent::on_playpause_button_clicked));
  _stopButton->signal_clicked().connect(sigc::mem_fun(this, &NowPlayingComponent::on_stop_button_clicked));
  _nextButton->signal_clicked().connect(sigc::mem_fun(this, &NowPlayingComponent::on_next_button_clicked));
}

NowPlayingComponent::~NowPlayingComponent() {
  delete _nextButton;
  delete _stopButton;
  delete _playPauseButton;
  delete _prevButton;
  delete _seekScale;
  delete _trackArtistLabel;
  delete _trackTitleLabel;
  delete _albumArtImage;
}

void NowPlayingComponent::set_track(const Track& track, const bool first, const bool last) {
  _trackTitleLabel->set_text(track.title());
  _trackArtistLabel->set_text(track.artist());
  _seekScale->get_adjustment()->set_lower(0);
  _seekScale->get_adjustment()->set_upper(track.length());
  _seekScale->get_adjustment()->set_value(0);
  _prevButton->set_sensitive(!first);
  _nextButton->set_sensitive(!last);
}

void NowPlayingComponent::set_state(const State state) {
  _state = state;

  if (state == State::Disabled || state == State::Stopped) {
    _trackTitleLabel->set_text("");
    _trackArtistLabel->set_text("");
    _seekScale->get_adjustment()->set_value(0);
    _prevButton->set_sensitive(false);
    _nextButton->set_sensitive(false);
  }

  _playPauseButton->set_sensitive(state != State::Disabled);
  _playPauseButton->set_image_from_icon_name((state != State::Playing) ? "gtk-media-play" : "gtk-media-pause");
  _stopButton->set_sensitive(state != State::Stopped && state != State::Disabled);
}

NowPlayingComponent::State NowPlayingComponent::get_state() const {
  return _state;
}

void NowPlayingComponent::set_seconds(const float seconds) {
  _seekScale->get_adjustment()->set_value(seconds);
}

NowPlayingComponent::sig_button NowPlayingComponent::signal_prev() {
  return _signal_prev;
}

NowPlayingComponent::sig_button NowPlayingComponent::signal_playpause() {
  return _signal_playpause;
}

NowPlayingComponent::sig_button NowPlayingComponent::signal_stop() {
  return _signal_stop;
}

NowPlayingComponent::sig_button NowPlayingComponent::signal_next() {
  return _signal_next;
}

void NowPlayingComponent::on_prev_button_clicked() {
  _signal_prev.emit();
}

void NowPlayingComponent::on_playpause_button_clicked() {
  _signal_playpause.emit();
}

void NowPlayingComponent::on_stop_button_clicked() {
  _signal_stop.emit();
}

void NowPlayingComponent::on_next_button_clicked() {
  _signal_next.emit();
}