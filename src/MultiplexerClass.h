//=============================================================================
//
// file :         MultiplexerClass.h
//
// description :  Include for the MultiplexerClass root class.
//                This class is represents the singleton class for
//                the Multiplexer device class.
//                It contains all properties and methods which the 
//                Multiplexer requires only once e.g. the commands.
//			
// project :      TANGO Device Server
//
// $Author$
//
// $Revision$
//
// $Log$
// Revision 1.2  2007/09/03 11:01:51  rsune
// Added support for terminated modes
// Added a mutex to the static members
// TODO: Now only one multiplexer (with up to two tango devices) can be used with one server
//
// Revision 1.1.1.1  2007/08/31 14:15:24  rsune
// Minor changes over original Soleil device
//
// Revision 1.1.1.1  2004/11/08 14:14:19  root
// initial import
//
//
// copyleft :     European Synchrotron Radiation Facility
//                BP 220, Grenoble 38043
//                FRANCE
//
//=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================

#ifndef _MULTIPLEXERCLASS_H
#define _MULTIPLEXERCLASS_H

#include <tango.h>
#include <Multiplexer.h>

namespace Multiplexer_ns
{

//=====================================
//	Define classes for attributes
//=====================================
//=========================================
//	Define classes for commands
//=========================================
class GetSelectionByChannelCmd : public Tango::Command
{
public:
	GetSelectionByChannelCmd(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	GetSelectionByChannelCmd(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~GetSelectionByChannelCmd() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return true; (static_cast<Multiplexer *>(dev));/*->is_GetSelectionByChannel_allowed(any);*/}
};



class GetSelectionByNameCmd : public Tango::Command
{
public:
	GetSelectionByNameCmd(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	GetSelectionByNameCmd(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~GetSelectionByNameCmd() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<Multiplexer *>(dev))->is_GetSelectionByName_allowed(any);}
};



class GetSignalsMappingCmd : public Tango::Command
{
public:
	GetSignalsMappingCmd(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	GetSignalsMappingCmd(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~GetSignalsMappingCmd() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<Multiplexer *>(dev))->is_GetSignalsMapping_allowed(any);}
};



class SelectByChannelCmd : public Tango::Command
{
public:
	SelectByChannelCmd(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	SelectByChannelCmd(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~SelectByChannelCmd() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<Multiplexer *>(dev))->is_SelectByChannel_allowed(any);}
};



class SelectByNameCmd : public Tango::Command
{
public:
	SelectByNameCmd(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	SelectByNameCmd(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~SelectByNameCmd() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<Multiplexer *>(dev))->is_SelectByName_allowed(any);}
};



//
// The MultiplexerClass singleton definition
//

class MultiplexerClass : public Tango::DeviceClass
{
public:
//	properties member data

//	add your own data members here
//------------------------------------

public:
	Tango::DbData	cl_prop;
	Tango::DbData	cl_def_prop;
	Tango::DbData	dev_def_prop;

//	Method prototypes
	static MultiplexerClass *init(const char *);
	static MultiplexerClass *instance();
	~MultiplexerClass();
	Tango::DbDatum	get_class_property(string &);
	Tango::DbDatum	get_default_device_property(string &);
	Tango::DbDatum	get_default_class_property(string &);
	
protected:
	MultiplexerClass(string &);
	static MultiplexerClass *_instance;
	void command_factory();
	void get_class_property();
	void write_class_property();
	void set_default_property();

private:
	void device_factory(const Tango::DevVarStringArray *);
};


}	//	namespace Multiplexer_ns

#endif // _MULTIPLEXERCLASS_H
