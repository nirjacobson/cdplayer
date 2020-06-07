#ifndef BLUETOOTH_COMPONENT_H
#define BLUETOOTH_COMPONENT_H

#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

#include <glibmm-2.4/glibmm.h>
#include <gtkmm-3.0/gtkmm/builder.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <gtkmm-3.0/gtkmm/treeview.h>
#include <gtkmm-3.0/gtkmm/treemodel.h>
#include <gtkmm-3.0/gtkmm/liststore.h>
#include <sigc++/signal.h>

#include "adapter.h"

class BluetoothComponent {

  public:
    typedef sigc::signal<void> sig_done;

    BluetoothComponent(Glib::RefPtr<Gtk::Builder> builder);
    ~BluetoothComponent();

    void on_show();
    void on_hide();

    sig_done signal_done();

  private:

    class DevicesListColumnRecord : public Gtk::TreeModel::ColumnRecord {
      public:
        DevicesListColumnRecord() {
          this->add(this->addressColumn);
          this->add(this->nameColumn);
        }

        Gtk::TreeModelColumn<Glib::ustring> addressColumn;
        Gtk::TreeModelColumn<Glib::ustring> nameColumn;
    };

    Bluez::Adapter _adapter;
    std::string _alsaDeviceAddress;
    Bluez::Device* _alsaDevice;

    Gtk::Label* _deviceLabel;
    Gtk::Label* _deviceStatusLabel;
    Gtk::TreeView* _devicesTreeView;
    Glib::RefPtr<Gtk::ListStore> _devicesListStore;
    Gtk::Button* _doneButton;
    Gtk::Button* _connectButton;

    sig_done _signal_done;

    void on_done_button_clicked();
    void on_device_added(const std::string& address);
    void on_device_removed(const std::string& address);
    void on_devices_list_selection_changed();
    void on_connect_button_clicked();
    
    void on_device_status_change();

    void build_devices_list();
    void get_alsa_device_address();
    void try_get_alsa_device();
    void set_device_labels();

    void update_asoundrc(const std::string& address);

};

#endif // BLUETOOTH_COMPONENT_H