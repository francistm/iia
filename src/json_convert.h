#pragma once

#include <string>
#include <QObject>
#include <json-c/json.h>

namespace JsonConvert
{
	struct KeyValue
	{
	public:
		std::string key;
		std::string value;

	public:
		KeyValue(std::string key, json_object *obj)
		{
			this->key = key;

			switch (json_object_get_type(obj))
			{
			case json_type_string:
				this->value = json_object_get_string(obj);
				break;

			case json_type_int:
			case json_type_double:
				this->value = std::to_string(json_object_get_int(obj));
				break;

			case json_type_boolean:
				this->value = json_object_get_boolean(obj) ? "TRUE" : "FALSE";
				break;

			case json_type_null:
				this->value = "NULL";
				break;

			default:
				this->value = "[UNKNOWN]";
			}
		}

		~KeyValue()
		{
		}
	};

	std::vector<std::shared_ptr<KeyValue>> convertStdStringToKeyValues(std::string rawJson);
}