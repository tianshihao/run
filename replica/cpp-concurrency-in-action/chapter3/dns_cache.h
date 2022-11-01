/**
 * @file dns_cache.h
 * @author Tian Shihao (shihao.tian@outlook.com)
 * @brief Listing 3.13 Protecting a data stucture with std::shared_mutex
 * @version 0.1
 * @date 2022-09-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>

class DNSEntry {};

class DNSCache {
  std::map<std::string, DNSEntry> entries;
  mutable std::shared_mutex entry_mutex;

 public:
  DNSEntry FindEntry(std::string const& domain) const {
    // Use an instance of std::shared_mutex<> to protect it for shared,
    // read-only access, multiple threads can therefore call FindEntry()
    // simutaneously.
    std::shared_lock<std::shared_mutex> lk{entry_mutex};
    std::map<std::string, DNSEntry>::const_iterator const it{
        entries.find(domain)};

    return (it == entries.end()) ? DNSEntry() : it->second;
  }

  void UpdateOrAddEntry(std::string const& domain,
                        DNSEntry const& dns_details) {
    // Use an instance of std::lock_guard<> to provide exclusive access while
    // the table is updated, not only are other threads prevented from doing
    // updates in a call to UpdateOrAddEntry, but threads that call FindEntry
    // are blocked too.
    std::lock_guard<std::shared_mutex> lk{entry_mutex};
    entries[domain] = dns_details;
  }
};
