// ============================================================================
//
// = CONTEXT
//    TANGO Project - NI-Switch - MUX
//
// = FILENAME
//    NiSwitchSupport.h
//
// = AUTHORS
//    N.Leclercq
//
// ============================================================================

#ifndef _NI_SWITCH_SUPPORT_H_
#define _NI_SWITCH_SUPPORT_H_

// ============================================================================
// DEPENDENCIES
// ============================================================================
#include <NIDAQmx.h>
#include <tango.h>

//=============================================================================
// TYPEDEFs
//=============================================================================
typedef std::map<std::string, unsigned short> Signals;
typedef Signals::iterator SignalsIterator;
typedef Signals::const_iterator SignalsConstIterator;

// ============================================================================
//! The multiplexer class.
// ============================================================================
//! to be written
// ============================================================================
class Mux : public Tango::LogAdapter
{
public:

  //- Multiplexer topology
  //----------------------
  typedef enum {
    mux_topology_unknown,     //- uninitialized mux  
    mux_topology_dual_8x1,    //- 2 multiplexers of 8 channels 
    mux_topology_single_16x1, //- 1 multiplexer of 16 channels 
  } MuxTopology;


  //- Multiplexer IDs (mode mux_topology_2x8 only)
  //----------------------------------------------
  typedef enum {
    mux_unknown, //- uninitialized mux
    mux_com0,    //- chan[00..07] to common 0
    mux_com1,    //- chan[08..16] to common 1
  } MuxId;

  /**
   * Constructor. 
   */
  Mux (Tango::DeviceImpl * dev = 0);
  
  /**
   * Destructor.
   */
  virtual ~Mux (void);

  /**
   * Initializes the multiplexer
   */
  void initialize (const char * n, Mux::MuxTopology t, Mux::MuxId i)
    throw (Tango::DevFailed);

  /**
   * Initializes the multiplexer
   */
  void initialize (const std::string& n, Mux::MuxTopology t, Mux::MuxId i)
    throw (Tango::DevFailed);

  /**
   * Releases any allocated resource (mux becomes unusable)
   */
  void release (void)
    throw (Tango::DevFailed);

  /**
   * Associates a name with each input channel. Syntax <chan-id>:<signal-name>
   */
  void set_signals (const std::vector<std::string>& signals)
    throw (Tango::DevFailed);

  /**
   * Returns the name associated with each input channel
   */
  inline const Signals & get_signals_map (void) const {
    return signals_;
  }

  /**
   * Returns the name associated with each input channel
   */
  Tango::DevVarLongStringArray * get_signals_list (void)
    throw (Tango::DevFailed);

  /**
   * Build a connection between an input channel and the associated "common" output.
   * If the multiplxer was intialized in mode "mux_2x8", channels [0..7] are
   * routed to "common-0" while channels [8..15] are routed to "common-1". In
   * "mux_1x16" all channels are routed to "common-0". May throw an exception 
   * in case the connection can not be established.
   */
  void select (unsigned short channel, bool use_logical_chan_id = false)
    throw (Tango::DevFailed);

  /**
   * Build a connection between a named input channel and the associated "common" output.
   * If the multiplxer was intialized in mode "mux_2x8", channels [0..7] are
   * routed to "common-0" while channels [8..15] are routed to "common-1". In
   * "mux_1x16" all channels are routed to "common-0". May throw an exception 
   * in case the connection can not be established.
   */
  void select (const std::string& signal_name)
      throw (Tango::DevFailed);

  /**
   * Disconnect any existing connection
   */
  void reset (void)
      throw (Tango::DevFailed);

  /**
   * Returns the current selection by name
   * Returns "no selection" if no selection
   */
  const std::string& get_selection_by_name (void);

  /**
   * Returns the current selection by channel indentifier
   * Returns -1 if no selection
   */
  short get_selection_by_channel (void);

  /**
   * Returns the mux topology
   */
  inline const MuxTopology& get_topology (void) const {
    return topology_;
  }

  /**
   * Returns the mux id
   */
  inline const MuxId& get_id (void) const {
    return id_;
  }

  /**
   * Returns the device name (i.e. board name)
   */
  const std::string& get_ni_device_name (void) const {
    return ni_device_name_;
  }

private:
  //- mux topology 
  static bool mux_available[2];

  //- mux channels
  static const char * mux_channels[16];

  /**
   * Returns the currently selected channel or -1 if no selection
   */
  short get_selection (bool use_logical_chan_id = false);

  //- mux topology 
  MuxTopology topology_;

  //- mux id
  MuxId id_;

  //- device name
  std::string ni_device_name_;

  //- signal names  
  Signals signals_;

  //- initialization flag  
  bool initialized_;

  //- Not allowed methods
  Mux (const Mux &);
  Mux& operator= (const Mux &);
};

#endif // _NI_SWITCH_SUPPORT_H_

