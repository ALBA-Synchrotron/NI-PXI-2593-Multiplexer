// ============================================================================
//
// = CONTEXT
//    TANGO Project - NI-Switch - MUX
//
// = FILENAME
//    NiSwitchSupport.cpp
//
// = AUTHORS
//    N.Leclercq
//
// ============================================================================

// ============================================================================
// DEPENDENCIES
// ============================================================================
#include <NiSwitchSupport.h>

// ============================================================================
// MACROs
// ============================================================================
#define _CCP(X) static_cast<const char*>(X)

// ============================================================================
// CONSTs
// ============================================================================
#define kNUM_CHANNELS        16
#define kMUX_0               0
#define kMUX_1               1
#define kUNSPECIFIED_DEVICE  _CCP("unknown")
#define kUNSPECIFIED_CHANNEL _CCP("none")
#define kCOMMON0_STR         _CCP("com0")
#define kCOMMON1_STR         _CCP("com1")

// ============================================================================
// STATICs
// ============================================================================
bool Mux::mux_available[2] = {true, true};
// ----------------------------------------------------------------------------
const char * Mux::mux_channels[16] = 
{
  "ch0", 
  "ch1", 
  "ch2", 
  "ch3", 
  "ch4", 
  "ch5", 
  "ch6", 
  "ch7", 
  "ch8", 
  "ch9", 
  "ch10", 
  "ch11", 
  "ch12", 
  "ch13", 
  "ch14", 
  "ch15"
};

// ============================================================================
// Mux::Mux
// ============================================================================
Mux::Mux (Tango::DeviceImpl * _dev)
 : Tango::LogAdapter(_dev),
   topology_ (mux_topology_unknown), 
   id_ (mux_unknown),
   ni_device_name_ (kUNSPECIFIED_DEVICE),
   initialized_(false)
{
  
}

// ============================================================================
// Mux::~Mux
// ============================================================================
Mux::~Mux (void)
{
  this->reset(); // Disconnect the device before closing it!
  this->release();
}

// ============================================================================
// Mux::initialize
// ============================================================================
void Mux::initialize (const std::string& _n, MuxTopology _t, MuxId _i)
    throw (Tango::DevFailed)
{
  this->initialize(_n.c_str(), _t, _i);
}

// ============================================================================
// Mux::initialize
// ============================================================================
void Mux::initialize (const char * _n, MuxTopology _t, MuxId _i)
    throw (Tango::DevFailed)
{
  //- check topology
  switch (_t) 
  {
    case mux_topology_dual_8x1:
      if (Mux::mux_available[kMUX_0] == false && Mux::mux_available[kMUX_1] == false) {
        Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
                                       _CCP("can't create 8x1 mux. [hardware already reserved]"),
                                       _CCP("Mux::initialize"));
      }
      switch (_i) 
      {
        case mux_com0:
          if (Mux::mux_available[kMUX_0] == false) 
          {
            Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
                                           _CCP("can't create 8x1 mux. [hardware already reserved]"),
                                           _CCP("Mux::initialize"));
          }
          break;
        case mux_com1:
          if (Mux::mux_available[kMUX_1] == false) 
          {
            Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
                                           _CCP("can't create 8x1 mux. [hardware already reserved]"),
                                           _CCP("Mux::initialize"));
          }
          break;
        case mux_unknown:
        default:
          Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
                                         _CCP("invalid mux. identifier specified"),
                                         _CCP("Mux::initialize"));
          break;
      }
      break;
    case mux_topology_single_16x1:
      if (Mux::mux_available[kMUX_0] == false || Mux::mux_available[kMUX_1] == false) {
        Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
                                       _CCP("can't create 16x1-mux. [hardware already reserved]"),
                                       _CCP("Mux::initialize"));
      }
      break;
    case mux_topology_unknown:
    default:
      Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
                                     _CCP("invalid topology specified"),
                                     _CCP("Mux::initialize"));
      break;
  }

  //- store device name
  this->ni_device_name_ = _n;

  //- store topology
  this->topology_ = _t;

  //- store mux id
  this->id_ = _i;

  int32 err = 0;

  //- init the underlying hw 
  switch (this->topology_)
  {
    case mux_topology_dual_8x1:
      {
        if (Mux::mux_available[(this->id_ == mux_com0) ? kMUX_1 : kMUX_0] == true) 
        {
          DEBUG_STREAM << "Mux::initialize::init hw for dual_8x1 mode" << endl;
          err = ::DAQmxSwitchSetTopologyAndReset(this->ni_device_name_.c_str(),
                                                 DAQmx_Val_Switch_Topology_2593_Dual_8x1_Mux);
        }
        if (err == 0) 
        {
          Mux::mux_available[(this->id_ == mux_com0) ? kMUX_0 : kMUX_1] = false;
        }
      }
      break;
    case mux_topology_single_16x1:
      {
        DEBUG_STREAM << "Mux::initialize::init hw for single_16x1 mode" << endl;
        err = ::DAQmxSwitchSetTopologyAndReset(this->ni_device_name_.c_str(),
                                               DAQmx_Val_Switch_Topology_2593_16x1_Mux);
        if (err == 0) 
        {
          Mux::mux_available[kMUX_0] = false;
          Mux::mux_available[kMUX_1] = false;
        }
      }
      break;
    default:
      break;
  }

  //- error handling
  if (err) 
  {
    this->release();
    char err_msg[256];
    ::DAQmxGetErrorString(err, err_msg, 256);
    if (err > 0) 
    { 
      WARN_STREAM << "Mux::initialize::DAQmsxSwitchSetTopologyAndReset::warning " << err << endl;
      WARN_STREAM << err_msg << endl;
    }
    else 
    {
      ERROR_STREAM << "Mux::initialize::DAQmxSwitchSetTopologyAndReset::error " << err << endl;
      ERROR_STREAM << err_msg << endl;
      Tango::Except::throw_exception(_CCP("DRIVER_FAILURE"),
				                             _CCP(err_msg),
				                             _CCP("Mux::initialize"));
    }
  }

  //- init done
  this->initialized_ = true;
}

// ============================================================================
// Mux::release
// ============================================================================
void Mux::release (void)
    throw (Tango::DevFailed)
{
  switch (this->topology_)
  {
    case mux_topology_dual_8x1:
          Mux::mux_available[(this->id_ == mux_com0) ? kMUX_0 : kMUX_1] = true;
      break;
    case mux_topology_single_16x1:
          Mux::mux_available[kMUX_0] = true;
          Mux::mux_available[kMUX_1] = true;
      break;
    default:
      break;
  }

  this->initialized_ = false;
  this->topology_ = mux_topology_unknown; 
  this->id_ = mux_unknown;
  this->ni_device_name_ = kUNSPECIFIED_DEVICE;
  this->signals_.clear();
}

// ============================================================================
// Mux::set_signals
// ============================================================================
void Mux::set_signals (const std::vector<std::string>& _signal_names)
    throw (Tango::DevFailed)
{
  if (this->initialized_ == false) 
  {
      Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
				                             _CCP("multiplexer is not properly initialized"),
				                             _CCP("Mux::set_signals"));
  }

  unsigned short offset;
  unsigned short chan_min;
  unsigned short chan_max;

  switch (this->topology_)
  {
    case mux_topology_dual_8x1:
      switch (this->id_)
      {
        case mux_com0:
          chan_min = 0;
          chan_max = 7;
          offset = 0;
          break;
        case mux_com1:
          chan_min = 8;
          chan_max = 15;
          offset = 8;
          break;
      }
      break;
    case mux_topology_single_16x1:
      chan_min = 0;
      chan_max = 15;
      offset = 0;
      break;
    default:
      break;
  }

  std::pair<SignalsIterator, bool> result;

  for (unsigned short i = 0; i < _signal_names.size(); i++) 
  {
    std::string::size_type pos = _signal_names[i].find(":", 0);
    if (pos == std::string::npos) 
    {
      this->signals_.clear();
      Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
				                             _CCP("signal name syntax error [should be <chan-id>:<signal-name>]"),
				                             _CCP("Mux::set_signals"));
    }
    else 
    {
      std::string channel;
      channel.assign(_signal_names[i].begin(), _signal_names[i].begin() + pos);
      if (channel.size() == 0)
      {
        this->signals_.clear();
        Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
				                               _CCP("signal name syntax error [should be <chan-id>:<signal-name>]"),
				                               _CCP("Mux::set_signals"));
      }
      unsigned short chan_id = 0;
      std::istringstream is(channel); 
      if ((is >> chan_id) == false) 
      {
        this->signals_.clear();
        Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
				                               _CCP("signal name syntax error [should be <chan-id>:<signal-name>]"),
				                               _CCP("Mux::set_signals"));
      }
      chan_id += offset;
      if (chan_id < chan_min || chan_id > chan_max)
      {
        this->signals_.clear();
        Tango::Except::throw_exception(_CCP("DATA_OUT_OF_RANGE"),
				                               _CCP("invalid channel identifier [valid range is [0..7]"),
				                               _CCP("Mux::set_signals"));
      }
      std::string signal;
      signal.assign(_signal_names[i].begin() + pos + 1, _signal_names[i].end());
      if (signal.size() == 0)
      {
        this->signals_.clear();
        Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
				                               _CCP("signal name syntax error [should be <chan-id>:<signal-name>]"),
				                               _CCP("Mux::set_signals"));
      }
      DEBUG_STREAM << "Mux::set_signals:: chan: " << chan_id << " - sig-name: " << signal << std::endl;
      result = this->signals_.insert(Signals::value_type(signal, chan_id));
      if (result.second == 0) 
      {
        this->signals_.clear();
        Tango::Except::throw_exception(_CCP("SOFTWARE_FAILURE"),
				                               _CCP("could not store signal name [std:map::insert failed]"),
				                               _CCP("Mux::set_signals"));
      }
    } //- else
  } //- for
}

// ============================================================================
// Mux::select
// ============================================================================
void Mux::select (unsigned short _channel, bool use_logical_chan_id)
    throw (Tango::DevFailed)
{
  if (this->initialized_ == false) 
  {
      Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
				                             _CCP("multiplexer is not properly initialized"),
				                             _CCP("Mux::select"));
  }

  unsigned short offset;
  unsigned short chan_min;
  unsigned short chan_max;


  switch (this->topology_)
  {
    case mux_topology_dual_8x1:
      switch (this->id_)
      {
        case mux_com0:
          offset = 0;
          chan_min = 0;
          chan_max = 7;
          break;
        case mux_com1:
          offset = 8;
          chan_min = 8;
          chan_max = 15;
          break;
      }
      break;
    case mux_topology_single_16x1:
      offset = 0;
      chan_min = 0;
      chan_max = 15;
      break;
    default:
      break;
  }

  if (use_logical_chan_id)
  {
    _channel += offset; 
  }

  if (_channel < chan_min || _channel > chan_max)
  {
        Tango::Except::throw_exception(_CCP("DATA_OUT_OF_RANGE"),
				                               _CCP("invalid channel identifier for specified topology"),
				                               _CCP("Mux::select"));
  }

  //- disconnect any existing connection
  this->reset();

  //- build input and output string
  const std::string k_separator("/");

  std::string input = k_separator 
                    + this->ni_device_name_ 
                    + k_separator 
                    + Mux::mux_channels[_channel];

  std::string output = k_separator 
                     + this->ni_device_name_ 
                     + k_separator;

  switch (this->topology_)
  {
    case mux_topology_dual_8x1:
      switch (this->id_) 
      {
        case mux_com0:
          output += kCOMMON0_STR;
          break;
        case mux_com1:
          output += kCOMMON1_STR;
          break;
      }
      break;
    case mux_topology_single_16x1:
      output += kCOMMON0_STR;
      break;
  }

  DEBUG_STREAM << "Mux::select::connecting " << input << " to " << output << endl;

  //- connect
  long err = ::DAQmxSwitchConnect(input.c_str(), output.c_str(), (bool32)1);
  if (err) 
  {
    char err_msg[256];
    ::DAQmxGetErrorString(err, err_msg, 256);
    if (err > 0) 
    { 
      WARN_STREAM << "Mux::select::DAQmxSwitchConnect::warning " << err << endl;
      WARN_STREAM << err_msg << endl;
    }
    else 
    {
      ERROR_STREAM << "Mux::initialize::DAQmxSwitchConnect::error " << err << endl;
      ERROR_STREAM << err_msg << endl;
      Tango::Except::throw_exception(_CCP("DRIVER_FAILURE"),
				                             _CCP(err_msg),
				                             _CCP("Mux::select"));
    }
  }
}

// ============================================================================
// Mux::select
// ============================================================================
void Mux::select (const std::string& signal_name)
    throw (Tango::DevFailed)
{
  if (this->initialized_ == false) 
  {
      Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
				                             _CCP("multiplexer is not properly initialized"),
				                             _CCP("Mux::select"));
  }

  SignalsIterator it = this->signals_.find(signal_name);

  if (it ==  this->signals_.end()) 
  {
    Tango::Except::throw_exception(_CCP("DATA_OUT_OF_RANGE"),
                                   _CCP("no signal by that name"),
			                             _CCP("Mux::select"));
  }

  this->select(it->second);
}

// ============================================================================
// Mux::reset
// ============================================================================
void Mux::reset (void)
    throw (Tango::DevFailed)
{
  short selection = this->get_selection(false);
  if (selection == -1)
  {
    //- no selection return
    return;
  }

  //- build input and output string
  const std::string k_separator("/");

  std::string input = k_separator 
                    + this->ni_device_name_ 
                    + k_separator 
                    + Mux::mux_channels[selection];

  std::string output = k_separator 
                     + this->ni_device_name_ 
                     + k_separator;

  switch (this->topology_)
  {
    case mux_topology_dual_8x1:
      switch (this->id_) 
      {
        case mux_com0:
          output += kCOMMON0_STR;
          break;
        case mux_com1:
          output += kCOMMON1_STR;
          break;
      }
      break;
    case mux_topology_single_16x1:
      output += kCOMMON0_STR;
      break;
  }

  DEBUG_STREAM << "Mux::reset::disconnecting " << input << " to " << output << endl;

  long err = ::DAQmxSwitchDisconnect(input.c_str(), output.c_str(), (bool32)1);
  if (err) 
  {
    char err_msg[256];
    ::DAQmxGetErrorString(err, err_msg, 256);
    if (err > 0) 
    { 
      WARN_STREAM << "Mux::select::DAQmxSwitchDisconnect::warning " << err << endl;
      WARN_STREAM << err_msg << endl;
    }
    else 
    {
      ERROR_STREAM << "Mux::initialize::DAQmxSwitchDisconnect::error " << err << endl;
      ERROR_STREAM << err_msg << endl;
      Tango::Except::throw_exception(_CCP("DRIVER_FAILURE"),
				                             _CCP(err_msg),
				                             _CCP("Mux::reset"));
    }
  }
}


// ============================================================================
// Mux::get_signals_list
// ============================================================================
Tango::DevVarLongStringArray * Mux::get_signals_list (void) throw (Tango::DevFailed)
{
  if (this->initialized_ == false) 
  {
      Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
				                             _CCP("multiplexer is not properly initialized"),
				                             _CCP("Mux::get_signals_list"));
  }

  Tango::DevVarLongStringArray * dvlsa = new Tango::DevVarLongStringArray;
  if (dvlsa == 0) 
  {
    Tango::Except::throw_exception(_CCP("OUT_OF_MEMORY"),
                                   _CCP("memory allocation failed"),
			                             _CCP("Mux::get_signals_list"));
  }

  unsigned short offset;
  switch (this->topology_)
  {
    case mux_topology_dual_8x1:
      switch (this->id_)
      {
        case mux_com0:
          offset = 0;
          break;
        case mux_com1:
          offset = 8;
          break;
      }
      break;
    case mux_topology_single_16x1:
      offset = 0;
      break;
    default:
      break;
  }

  dvlsa->lvalue.length(this->signals_.size());
  dvlsa->svalue.length(this->signals_.size());

  SignalsIterator cur = this->signals_.begin();
  SignalsIterator end = this->signals_.end();

  for (unsigned long i = 0; cur != end; cur++, i++) 
  {
    dvlsa->lvalue[i] = (long)cur->second - offset;
    dvlsa->svalue[i] = CORBA::string_dup(cur->first.c_str());
  } 

  return dvlsa;
}

// ============================================================================
// Mux::get_selection
// ============================================================================
short Mux::get_selection (bool use_logical_chan_id)
{
  std::string com;
  unsigned short chan_min = 0;
  unsigned short chan_max = 0;
  unsigned short offset;

  switch (this->topology_)
  {
    case mux_topology_dual_8x1:
      switch (this->id_)
      {
        case mux_com0:
          chan_min = 0;
          chan_max = 7;
          com = kCOMMON0_STR;
          offset = 0;
          break;
        case mux_com1:
          chan_min = 8;
          chan_max = 15;
          com = kCOMMON1_STR;
          offset = 8;
          break;
      }
      break;
    case mux_topology_single_16x1:
      chan_min = 0;
      chan_max = 15;
      com = kCOMMON0_STR;
      offset = 0;
      break;
    default:
      break;
  }

  long err;
  char path[256];
  long path_status;
  const unsigned long path_len = 256; 
  const std::string k_separator("/");

  std::string output = k_separator 
                     + this->ni_device_name_ 
                     + k_separator
                     + com;

  for (unsigned short i = chan_min; i <= chan_max; i++)
  {
    //- build input and output string
    std::string input = k_separator 
                      + this->ni_device_name_ 
                      + k_separator 
                      + Mux::mux_channels[i];

    err = ::DAQmxSwitchFindPath(input.c_str(), output.c_str(), path, path_len, &path_status);
    if (err) 
    {
      char err_msg[256];
      ::DAQmxGetErrorString(err, err_msg, 256);
      if (err > 0) 
      { 
        WARN_STREAM << "Mux::get_selection::DAQmxSwitchFindPath::warning " << err << endl;
        WARN_STREAM << err_msg << endl;
      }
      else 
      {
        ERROR_STREAM << "Mux::get_selection::DAQmxSwitchFindPath::error " << err << endl;
        ERROR_STREAM << err_msg << endl;
        Tango::Except::throw_exception(_CCP("DRIVER_FAILURE"),
				                               _CCP(err_msg),
				                               _CCP("Mux::select"));
      }
    }
    if (path_status == DAQmx_Val_PathStatus_AlreadyExists)
    {
      DEBUG_STREAM << "Mux::get_selection::path: DAQmx_Val_PathStatus_AlreadyExists" << endl;
      return (use_logical_chan_id) ? i - offset : i;
    }
  }

  return -1;
}

// ============================================================================
// Mux::get_selection_by_name
// ============================================================================
const std::string& Mux::get_selection_by_name (void)
{
  static std::string anonymous("anonymous signal");
  static const std::string no_selection("no selection");

  if (this->initialized_ == false) 
  {
    Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
				                           _CCP("multiplexer is not properly initialized"),
				                           _CCP("Mux::get_selection_by_name"));
  }

  short selection = this->get_selection(false);
  if (selection == -1) 
  {
    return no_selection;
  }

  SignalsConstIterator cur = this->signals_.begin();
  SignalsConstIterator end = this->signals_.end();

  for (unsigned long i = 0; cur != end; cur++, i++) 
  {
    if (cur->second == (unsigned short)selection)
    {
      return cur->first;
    }
  } 

  unsigned short offset;

  switch (this->topology_)
  {
    case mux_topology_dual_8x1:
      switch (this->id_)
      {
        case mux_com0:
          offset = 0;
          break;
        case mux_com1:
          offset = 8;
          break;
      }
      break;
    case mux_topology_single_16x1:
      offset = 0;
      break;
    default:
      break;
  }

  TangoSys_OMemStream o;
  o << "anonymous signal from channel " << selection - offset << std::ends;

  anonymous = o.str();

  return anonymous;
}

// ============================================================================
// Mux::get_selection_by_channel
// ============================================================================
short Mux::get_selection_by_channel (void)
{
  if (this->initialized_ == false) 
  {
    Tango::Except::throw_exception(_CCP("CONFIGURATION_ERROR"),
				                           _CCP("multiplexer is not properly initialized"),
				                           _CCP("Mux::get_selection_by_channel"));
  }

  return this->get_selection(true);
}





