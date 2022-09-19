/**
 * @file connection_manager.h
 * @author Tian Shihao (shihao.tian@outlook.com)
 * @brief Listing 3.12 Thread-safe lazy initailization of a class member using
 * std::call_once
 * @version 0.1
 * @date 2022-09-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <mutex>
#include <vector>

class DataPacket {
  std::vector<int> data;
};

class ConnectionInfo {
  int info;
};

class ConnectionHandle {
 public:
  ConnectionHandle Open(ConnectionInfo const &) { return ConnectionHandle(); }
  void SendData(DataPacket const &data) {}
  DataPacket ReceiveData() { return DataPacket(); }
};

class ConnectionManager {
 private:
  ConnectionInfo connection_details;
  ConnectionHandle connection;
  std::once_flag connection_init_flag;
  void OpenConnection() {
    connection = connection.Open(connection_details);
    return;
  }

 public:
  ConnectionManager(ConnectionInfo const &connection_details_)
      : connection_details{connection_details_} {}

  // No matter send or receive, the connection only need to be established once.

  void SendData(DataPacket const &data) {
    std::call_once(connection_init_flag, &ConnectionManager::OpenConnection,
                   this);
    connection.SendData(data);

    return;
  }

  DataPacket ReceiveData() {
    std::call_once(connection_init_flag, &ConnectionManager::OpenConnection,
                   this);
    return connection.ReceiveData();
  }
};
