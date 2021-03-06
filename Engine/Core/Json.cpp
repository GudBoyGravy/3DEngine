#include "Json.h"
#include "istreamwrapper.h"
#include <fstream>

namespace nc
{
	namespace json
	{
		bool Load(const std::string& filename, rapidjson::Document& document)
		{
			bool success = false; 

			std::ifstream stream(filename); 
			if (stream.is_open())
			{
				rapidjson::IStreamWrapper istream(stream);
				document.ParseStream(istream);
				success = document.IsObject();
			}

			return success;
		}
		bool Get(const rapidjson::Value& value, const std::string& name, int& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsInt() == false)
			{
				return false;
			}

			data = value[name.c_str()].GetInt();

			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, float& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsNumber() == false)
			{
				return false;
			}

			data = value[name.c_str()].GetFloat();

			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, bool& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsBool() == false)
			{
				return false;
			}

			data = value[name.c_str()].GetBool();

			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, std::string& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsString() == false)
			{
				return false;
			}

			data = value[name.c_str()].GetString();

			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, glm::vec2& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 2)
			{
				return false;
			}

			auto& array = value[name.c_str()];
			for (rapidjson::SizeType i = 0; i < array.Size(); i++)
			{
				if (array[i].IsNumber())
				{
					data[i] = array[i].GetFloat();
				}
			}

			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, glm::vec3& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 3)
			{
				return false;
			}

			auto& array = value[name.c_str()];
			for (rapidjson::SizeType i = 0; i < array.Size(); i++)
			{
				if (array[i].IsNumber())
				{
					data[i] = array[i].GetFloat();
				}
			}

			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, glm::vec4& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 4)
			{
				return false;
			}

			auto& array = value[name.c_str()];
			data.x = array[0].GetInt();
			data.y = array[1].GetInt();
			data.w = array[2].GetInt();
			data.z = array[3].GetInt();

			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false)
			{
				return false;
			}

			auto& array = value[name.c_str()];
			for (auto &element : array.GetArray())
			{
				data.push_back(element.GetString()); 
			}

			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false)
			{
				return false;
			}

			auto& array = value[name.c_str()];
			for (auto& element : array.GetArray())
			{
				data.push_back(element.GetInt());
			}

			return true;
		}
	}
}
