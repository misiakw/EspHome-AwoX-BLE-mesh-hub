#pragma once

#ifdef USE_ESP32

#include <map>
#include <vector>

#include "mesh_destination.h"
#include "mesh_connection.h"
#include "device.h"
#include "group.h"

namespace esphome {
namespace awox_mesh {

class AwoxMesh;

class AwoxMeshMqtt {
  AwoxMesh *mesh_;

  bool published_connected = false;

  std::map<int, MeshDestinationState> last_published_state_;
  std::map<int, bool> last_published_availability_;
  int last_published_active_connections_;
  int last_published_online_devices_;

  std::string get_mqtt_topic_for_(MeshDestination *mesh_destination, const std::string &suffix) const;

  //std::string get_discovery_topic_(const esphome::mqtt::MQTTDiscoveryInfo &discovery_info, Device *device) const;

  //void process_incomming_command(MeshDestination *mesh_destination, JsonObject root);

 public:
  AwoxMeshMqtt(AwoxMesh *mesh) { this->mesh_ = mesh; }

  void setup();

  void publish_availability(Device *device);
  void publish_availability(Group *group);
  void send_discovery(Device *device);
  void send_group_discovery(Group *group);
  void publish_connection_sensor_discovery(const std::vector<MeshConnection *> &connections);
  void publish_connected(int active_connections, int online_devices, const std::vector<MeshConnection *> &connections);
  void publish_state(MeshDestination *mesh_destination);
};

}  // namespace awox_mesh
}  // namespace esphome

#endif
