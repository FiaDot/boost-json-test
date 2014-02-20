// boost-json-test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <boost/foreach.hpp>


int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		using boost::property_tree::ptree;
		using std::string;

		ptree props;
		boost::property_tree::read_json("Config.json", props);


		string encoding = props.get<string>("encoding");
		std::cout << "Encoding=" << encoding << std::endl;

		string config_type = props.get<string>("config_type");
		std::cout << "config_type=" << config_type << std::endl;


		unsigned short port = props.get<unsigned short>("port");
		std::cout << "port=" << port << std::endl;


		std::cout << "[Log]" << std::endl;
		ptree &log_child = props.get_child("log");
		int size = log_child.get<int>("max_size"); 
		std::cout << "size=" << size << std::endl;


		bool write_file = log_child.get<bool>("write_file"); 
		std::cout << "write_file=" << std::boolalpha << write_file << std::endl;

		std::cout.setf(std::ios::boolalpha);
		bool print_screen = log_child.get<bool>("print_screen"); 
		std::cout << "print_screen=" << print_screen << std::endl;



		std::cout << "[Database]" << std::endl;
		ptree &db_child = props.get_child("database");

		// array!
		int idx = 0;
		BOOST_FOREACH(ptree::value_type &vt, db_child)
		{
			string desc = vt.second.get<string>("desc");
			string address = vt.second.get<string>("address");
			unsigned short port = vt.second.get<unsigned short>("port");
			string instance = vt.second.get<string>("instance");
			string id = vt.second.get<string>("id");
			string password = vt.second.get<string>("password");

			std::cout << idx++ << " " << desc << " " << address << " " << port << " " << instance << " " << id << " " << password << std::endl;
		}

	}
	catch (std::exception& e)
	{
		std::cout << e.what(); 
	}

	return 0;
}

