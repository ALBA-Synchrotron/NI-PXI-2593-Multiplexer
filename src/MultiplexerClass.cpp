static const char *RcsId = "$Header$";

static const char *TagName = "$Name$";

static const char *FileName= "$Source$"; 

static const char *HttpServer= "http://controle/DeviceServer/doc/";

static const char *RCSfile = "$RCSfile$";
//+=============================================================================
//
// file :        MultiplexerClass.cpp
//
// description : C++ source for the MultiplexerClass. A singleton
//               class derived from DeviceClass. It implements the
//               command list and all properties and methods required
//               by the Multiplexer once per process.
//
// project :     TANGO Device Server
//
// $Author$
//
// $Revision$
//
// $Log$
// Revision 1.3  2007/09/03 12:20:39  rsune
// Now it should be OK with multiple devices on a server too
//
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
// copyleft :   European Synchrotron Radiation Facility
//              BP 220, Grenoble 38043
//              FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================


#include <tango.h>

#include <Multiplexer.h>
#include <MultiplexerClass.h>


namespace Multiplexer_ns
{
//+----------------------------------------------------------------------------
//
// method : 		GetSelectionByChannelCmd::execute()
// 
// description : 	method to trigger the execution of the command.
//                PLEASE DO NOT MODIFY this method core without pogo   
//
// in : - device : The device on which the command must be excuted
//		- in_any : The command input data
//
// returns : The command output data (packed in the Any object)
//
//-----------------------------------------------------------------------------
CORBA::Any *GetSelectionByChannelCmd::execute(Tango::DeviceImpl *device,const CORBA::Any &in_any)
{

	cout2 << "GetSelectionByChannelCmd::execute(): arrived" << endl;

	return insert((static_cast<Multiplexer *>(device))->get_selection_by_channel());
}

//+----------------------------------------------------------------------------
//
// method : 		GetSelectionByNameCmd::execute()
// 
// description : 	method to trigger the execution of the command.
//                PLEASE DO NOT MODIFY this method core without pogo   
//
// in : - device : The device on which the command must be excuted
//		- in_any : The command input data
//
// returns : The command output data (packed in the Any object)
//
//-----------------------------------------------------------------------------
CORBA::Any *GetSelectionByNameCmd::execute(Tango::DeviceImpl *device,const CORBA::Any &in_any)
{

	cout2 << "GetSelectionByNameCmd::execute(): arrived" << endl;

	return insert((static_cast<Multiplexer *>(device))->get_selection_by_name());
}

//+----------------------------------------------------------------------------
//
// method : 		GetSignalsMappingCmd::execute()
// 
// description : 	method to trigger the execution of the command.
//                PLEASE DO NOT MODIFY this method core without pogo   
//
// in : - device : The device on which the command must be excuted
//		- in_any : The command input data
//
// returns : The command output data (packed in the Any object)
//
//-----------------------------------------------------------------------------
CORBA::Any *GetSignalsMappingCmd::execute(Tango::DeviceImpl *device,const CORBA::Any &in_any)
{

	cout2 << "GetSignalsMappingCmd::execute(): arrived" << endl;

	return insert((static_cast<Multiplexer *>(device))->get_signals_mapping());
}

//+----------------------------------------------------------------------------
//
// method : 		SelectByChannelCmd::execute()
// 
// description : 	method to trigger the execution of the command.
//                PLEASE DO NOT MODIFY this method core without pogo   
//
// in : - device : The device on which the command must be excuted
//		- in_any : The command input data
//
// returns : The command output data (packed in the Any object)
//
//-----------------------------------------------------------------------------
CORBA::Any *SelectByChannelCmd::execute(Tango::DeviceImpl *device,const CORBA::Any &in_any)
{

	cout2 << "SelectByChannelCmd::execute(): arrived" << endl;

	Tango::DevUShort	argin;
	extract(in_any, argin);

	((static_cast<Multiplexer *>(device))->select_by_channel(argin));
	return new CORBA::Any();
}



//+----------------------------------------------------------------------------
//
// method : 		SelectByNameCmd::execute()
// 
// description : 	method to trigger the execution of the command.
//                PLEASE DO NOT MODIFY this method core without pogo   
//
// in : - device : The device on which the command must be excuted
//		- in_any : The command input data
//
// returns : The command output data (packed in the Any object)
//
//-----------------------------------------------------------------------------
CORBA::Any *SelectByNameCmd::execute(Tango::DeviceImpl *device,const CORBA::Any &in_any)
{

	cout2 << "SelectByNameCmd::execute(): arrived" << endl;

	Tango::DevString	argin;
	extract(in_any, argin);

	((static_cast<Multiplexer *>(device))->select_by_name(argin));
	return new CORBA::Any();
}

//
//----------------------------------------------------------------
//	Initialize pointer for singleton pattern
//----------------------------------------------------------------
//
MultiplexerClass *MultiplexerClass::_instance = NULL;

//+----------------------------------------------------------------------------
//
// method : 		MultiplexerClass::MultiplexerClass(string &s)
// 
// description : 	constructor for the MultiplexerClass
//
// in : - s : The class name
//
//-----------------------------------------------------------------------------
MultiplexerClass::MultiplexerClass(string &s):DeviceClass(s)
{

	cout2 << "Entering MultiplexerClass constructor" << endl;
	set_default_property();
	get_class_property();
	write_class_property();
	
	cout2 << "Leaving MultiplexerClass constructor" << endl;

}
//+----------------------------------------------------------------------------
//
// method : 		MultiplexerClass::~MultiplexerClass()
// 
// description : 	destructor for the MultiplexerClass
//
//-----------------------------------------------------------------------------
MultiplexerClass::~MultiplexerClass()
{
	_instance = NULL;
}

//+----------------------------------------------------------------------------
//
// method : 		MultiplexerClass::instance
// 
// description : 	Create the object if not already done. Otherwise, just
//			return a pointer to the object
//
// in : - name : The class name
//
//-----------------------------------------------------------------------------
MultiplexerClass *MultiplexerClass::init(const char *name)
{
	if (_instance == NULL)
	{
		try
		{
			string s(name);
			_instance = new MultiplexerClass(s);
		}
		catch (bad_alloc)
		{
			throw;
		}		
	}		
	return _instance;
}

MultiplexerClass *MultiplexerClass::instance()
{
	if (_instance == NULL)
	{
		cerr << "Class is not initialised !!" << endl;
		exit(-1);
	}
	return _instance;
}

//+----------------------------------------------------------------------------
//
// method : 		MultiplexerClass::command_factory
// 
// description : 	Create the command object(s) and store them in the 
//			command list
//
//-----------------------------------------------------------------------------
void MultiplexerClass::command_factory()
{
	command_list.push_back(new SelectByNameCmd("SelectByName",
		Tango::DEV_STRING, Tango::DEV_VOID,
		"The name of the signal to select",
		"N/A",
		Tango::OPERATOR));
	command_list.push_back(new SelectByChannelCmd("SelectByChannel",
		Tango::DEV_USHORT, Tango::DEV_VOID,
		"The channel to select",
		"N/A",
		Tango::OPERATOR));
	command_list.push_back(new GetSignalsMappingCmd("GetSignalsMapping",
		Tango::DEV_VOID, Tango::DEVVAR_LONGSTRINGARRAY,
		"",
		"The signals mapping",
		Tango::OPERATOR));
	command_list.push_back(new GetSelectionByNameCmd("GetSelectionByName",
		Tango::DEV_VOID, Tango::DEV_STRING,
		"",
		"The currently selected signal",
		Tango::OPERATOR));
	command_list.push_back(new GetSelectionByChannelCmd("GetSelectionByChannel",
		Tango::DEV_VOID, Tango::DEV_SHORT,
		"",
		"The currently selected channel",
		Tango::OPERATOR));

	//	add polling if any
	for (unsigned int i=0 ; i<command_list.size(); i++)
	{
	}
}

//+----------------------------------------------------------------------------
//
// method : 		MultiplexerClass::get_class_property
// 
// description : 	Get the class property for specified name.
//
// in :		string	name : The property name
//
//+----------------------------------------------------------------------------
Tango::DbDatum MultiplexerClass::get_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_prop.size() ; i++)
		if (cl_prop[i].name == prop_name)
			return cl_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}
//+----------------------------------------------------------------------------
//
// method : 		MultiplexerClass::get_default_device_property()
// 
// description : 	Return the default value for device property.
//
//-----------------------------------------------------------------------------
Tango::DbDatum MultiplexerClass::get_default_device_property(string &prop_name)
{
	for (unsigned int i=0 ; i<dev_def_prop.size() ; i++)
		if (dev_def_prop[i].name == prop_name)
			return dev_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//+----------------------------------------------------------------------------
//
// method : 		MultiplexerClass::get_default_class_property()
// 
// description : 	Return the default value for class property.
//
//-----------------------------------------------------------------------------
Tango::DbDatum MultiplexerClass::get_default_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_def_prop.size() ; i++)
		if (cl_def_prop[i].name == prop_name)
			return cl_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}
//+----------------------------------------------------------------------------
//
// method : 		MultiplexerClass::device_factory
// 
// description : 	Create the device object(s) and store them in the 
//			device list
//
// in :		Tango::DevVarStringArray *devlist_ptr : The device name list
//
//-----------------------------------------------------------------------------
void MultiplexerClass::device_factory(const Tango::DevVarStringArray *devlist_ptr)
{

	//	Create all devices.(Automatic code generation)
	//-------------------------------------------------------------
	for (unsigned long i=0 ; i < devlist_ptr->length() ; i++)
	{
		cout4 << "Device name : " << (*devlist_ptr)[i].in() << endl;
						
		// Create devices and add it into the device list
		//----------------------------------------------------
		device_list.push_back(new Multiplexer(this, (*devlist_ptr)[i]));							 

		// Export device to the outside world
		// Check before if database used.
		//---------------------------------------------
		if ((Tango::Util::_UseDb == true) && (Tango::Util::_FileDb == false))
			export_device(device_list.back());
		else
			export_device(device_list.back(), (*devlist_ptr)[i]);
	}
	//	End of Automatic code generation
	//-------------------------------------------------------------

}


//+----------------------------------------------------------------------------
//
// method : 		MultiplexerClass::get_class_property()
// 
// description : 	Read the class properties from database.
//
//-----------------------------------------------------------------------------
void MultiplexerClass::get_class_property()
{
	//	Initialize your default values here (if not done with  POGO).
	//------------------------------------------------------------------

	//	Read class properties from database.(Automatic code generation)
	//------------------------------------------------------------------

	//	Call database and extract values
	//--------------------------------------------
	if (Tango::Util::instance()->_UseDb==true)
		get_db_class()->get_property(cl_prop);
	Tango::DbDatum	def_prop;
	int	i = -1;


	//	End of Automatic code generation
	//------------------------------------------------------------------

}

//+----------------------------------------------------------------------------
//
// method : 	MultiplexerClass::set_default_property
// 
// description: Set default property (class and device) for wizard.
//              For each property, add to wizard property name and description
//              If default value has been set, add it to wizard property and
//              store it in a DbDatum.
//
//-----------------------------------------------------------------------------
void MultiplexerClass::set_default_property()
{
	string	prop_name;
	string	prop_desc;
	string	prop_def;

	vector<string>	vect_data;
	//	Set Default Class Properties
	//	Set Default Device Properties
	prop_name = "Signals";
	prop_desc = "Name of signals attached to mux. inputs.\nSyntax <channel-id>:<signal_name>. For instance: 0:camera_1";
	prop_def  = "";
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "NiDAQmxDeviceName";
	prop_desc = "The name of NI-DAQmx device [use NI-MAX device name]";
	prop_def  = "";
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "Topology";
	prop_desc = "The multiplexer topology: \"8x1\", \"16x1\", \"4x1 terminated\", \"8x1 terminated\"";
	prop_def  = "";
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "MuxId";
	prop_desc = "In case Topology is set to 8x1, this property indentifies the 8x1 multiplexer managed by this device.\nShould be 0 [channels[0..7]->com0] or 1 [channels[8..15]->com1].";
	prop_def  = "";
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

}
//+----------------------------------------------------------------------------
//
// method : 		MultiplexerClass::write_class_property
// 
// description : 	Set class description as property in database
//
//-----------------------------------------------------------------------------
void MultiplexerClass::write_class_property()
{
	//	First time, check if database used
	//--------------------------------------------
	if (Tango::Util::_UseDb == false)
		return;

	Tango::DbData	data;
	string	classname = get_name();
	string	header;
	string::size_type	start, end;

	//	Put title
	Tango::DbDatum	title("ProjectTitle");
	string	str_title("NI-Switch Support");
	title << str_title;
	data.push_back(title);

	//	Put Description
	Tango::DbDatum	description("Description");
	vector<string>	str_desc;
	str_desc.push_back("Provides support for the NI-2593 [dual 8x1 or single 16x1 multiplexer]");
	str_desc.push_back("Important:");
	str_desc.push_back("TOPOLOGY PORT MAPPINGS:");
	str_desc.push_back("");
	str_desc.push_back("Real is the channel on device documentation");
	str_desc.push_back("Virtual is the channel that the tango device expects");
	str_desc.push_back("");
	str_desc.push_back("FORMAT: \" Real : Virtual \"");
	str_desc.push_back("");
	str_desc.push_back("Topology = \"16x1\":");
	str_desc.push_back("  0  :  0");
	str_desc.push_back("  1  :  1");
	str_desc.push_back("  ...");
	str_desc.push_back("  15 :  15");
	str_desc.push_back("");
	str_desc.push_back("-------------------");
	str_desc.push_back("");
	str_desc.push_back("Topology = \"8x1\":");
	str_desc.push_back("  MuxId = 0");
	str_desc.push_back("    0  :  0");
	str_desc.push_back("    1  :  1");
	str_desc.push_back("    ...");
	str_desc.push_back("    7  :  7");
	str_desc.push_back("  MuxId = 1");
	str_desc.push_back("    8  :  0");
	str_desc.push_back("    9  :  1");
	str_desc.push_back("    ...");
	str_desc.push_back("    15 :  7");
	str_desc.push_back("");
	str_desc.push_back("--------------------");
	str_desc.push_back("");
	str_desc.push_back("Topology = \"8x1 terminated\":");
	str_desc.push_back("  0  :  0");
	str_desc.push_back("  2  :  1");
	str_desc.push_back("  ...");
	str_desc.push_back("  14 :  7");
	str_desc.push_back("");
	str_desc.push_back("-------------------");
	str_desc.push_back("");
	str_desc.push_back("Topology = \"4x1 terminated\":");
	str_desc.push_back("  MuxId = 0");
	str_desc.push_back("    0  :  0");
	str_desc.push_back("    2  :  1");
	str_desc.push_back("    4  :  2");
	str_desc.push_back("    6  :  3");
	str_desc.push_back("  MuxId =1");
	str_desc.push_back("    8  :  4");
	str_desc.push_back("    10 :  5");
	str_desc.push_back("    12 :  6");
	str_desc.push_back("    14 :  7");
	description << str_desc;
	data.push_back(description);
		
	//	put cvs location
	string	rcsId(RcsId);
	string	filename(classname);
	start = rcsId.find("/");
	if (start!=string::npos)
	{
		filename += "Class.cpp";
		end   = rcsId.find(filename);
		if (end>start)
		{
			string	strloc = rcsId.substr(start, end-start);
			//	Check if specific repository
			start = strloc.find("/cvsroot/");
			if (start!=string::npos && start>0)
			{
				string	repository = strloc.substr(0, start);
				if (repository.find("/segfs/")!=string::npos)
					strloc = "ESRF:" + strloc.substr(start, strloc.length()-start);
			}
			Tango::DbDatum	cvs_loc("cvs_location");
			cvs_loc << strloc;
			data.push_back(cvs_loc);
		}
	}

	//	Get CVS tag revision
	string	tagname(TagName);
	header = "$Name: ";
	start = header.length();
	string	endstr(" $");
	end   = tagname.find(endstr);
	if (end!=string::npos && end>start)
	{
		string	strtag = tagname.substr(start, end-start);
		Tango::DbDatum	cvs_tag("cvs_tag");
		cvs_tag << strtag;
		data.push_back(cvs_tag);
	}

	//	Get URL location
	string	httpServ(HttpServer);
	if (httpServ.length()>0)
	{
		Tango::DbDatum	db_doc_url("doc_url");
		db_doc_url << httpServ;
		data.push_back(db_doc_url);
	}

	//  Put inheritance
	Tango::DbDatum	inher_datum("InheritedFrom");
	vector<string> inheritance;
	inheritance.push_back("Device_3Impl");
	inher_datum << inheritance;
	data.push_back(inher_datum);

	//	Call database and and values
	//--------------------------------------------
	get_db_class()->put_property(data);
}

}	// namespace
