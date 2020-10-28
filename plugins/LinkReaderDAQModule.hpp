/**
 * @file LinkReaderDAQModule.hpp FELIX FULLMODE Link reader module
 *
 * This is part of the DUNE DAQ , copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
*/
#ifndef UDAQ_READOUT_SRC_LINKREADERDAQMODULE_HPP_
#define UDAQ_READOUT_SRC_LINKREADERDAQMODULE_HPP_

#include "appfwk/DAQModule.hpp"

// 3rd party felix
#include "packetformat/block_parser.hpp"

// module
#include "ReadoutTypes.hpp"
#include "ReusableThread.hpp"
#include "DefaultParserImpl.hpp"

#include <string>
#include <chrono>
#include <vector>

namespace dunedaq {
namespace readout {

class LinkReaderDAQModule : public dunedaq::appfwk::DAQModule
{
public:
  /**
  * @brief LinkReaderDAQModule Constructor
  * @param name Instance name for this LinkReaderDAQModule instance
  */
  explicit LinkReaderDAQModule(const std::string& name);

  LinkReaderDAQModule(const LinkReaderDAQModule&) =
    delete; ///< LinkReaderDAQModule is not copy-constructible
  LinkReaderDAQModule& operator=(const LinkReaderDAQModule&) =
    delete; ///< LinkReaderDAQModule is not copy-assignable
  LinkReaderDAQModule(LinkReaderDAQModule&&) =
    delete; ///< LinkReaderDAQModule is not move-constructible
  LinkReaderDAQModule& operator=(LinkReaderDAQModule&&) =
    delete; ///< LinkReaderDAQModule is not move-assignable

  void init() override;

private:
  // Commands
  void do_start(const std::vector<std::string>& /*args*/);
  void do_stop(const std::vector<std::string>& /*args*/);

  // Configuration
  bool configured_;
  UniqueBlockPtrSource block_ptr_source_;
  UniqueFrameSink parser_sink_;
  std::chrono::milliseconds source_timeout_;

  // Internals
  std::string info_str_;
  unsigned link_id_;
  unsigned link_tag_;
  std::string parser_type_;
  std::string id_str_;
 
  // Processor
  inline static const std::string dma_processor_name_ = "flx-parser";
  ReusableThread link_processor_;
  std::atomic<bool> run_lock_{false};
  std::atomic<bool> active_{false};

  // Operations
  DefaultParserImpl parser_impl_;
  felix::packetformat::BlockParser<DefaultParserImpl> parser_;
  void processLink();

  //typedef felix::packetformat::BlockParser<LinkParserImpl> LinkParser;
  //typedef felix::packetformat::BlockParser<HitsParserImpl> HitsParser;

  // Operations
  //TParser m_parser_impl;
  //felix::packetformat::BlockParser m_parser;
};

} // namespace dunedaq::readout
}

#endif // UDAQ_READOUT_SRC_LINKREADERDAQMODULE_HPP_