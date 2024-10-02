#include <array>
#include <deque>
#include <string>
#include <QObject>
#include <json-c/json.h>
#include "json_convert.h"

using namespace std;

namespace JsonConvert {
	struct JsonElem
	{
		string key;
		json_object *value;

		JsonElem(string k, json_object *v) : key(k), value(v) {};
	};

	vector<KeyValue *> convertStdStringToKeyValues(string rawJson)
	{
		json_type root_type;
		json_object *root_obj;
		deque<JsonElem> objects = {};
		vector<KeyValue *> keyValues = {};

		root_obj = json_tokener_parse(rawJson.c_str());

		if (root_obj == NULL)
			return keyValues;

		root_type = json_object_get_type(root_obj);

		objects.push_back(JsonElem("", root_obj));

		while (objects.size() > 0)
		{
			JsonElem tail = objects.back();

			objects.pop_back();

			switch (json_object_get_type(tail.value))
			{
			case json_type_object:
			{
				json_object_object_foreach(tail.value, key, val)
				{
					string objPath = tail.key.size() == 0 ? key : tail.key + "." + key;

					if (json_object_get_type(val) == json_type_object || json_object_get_type(val) == json_type_array)
						objects.push_back(JsonElem(objPath, val));
					else
						keyValues.push_back(new KeyValue(objPath, val));
				}
			}
			break;

			case json_type_array:
				for (int i = json_object_array_length(tail.value) - 1; i > -1; i--)
				{
					string curPath = "[" + to_string(i) + "]";
					string objPath = tail.key.size() == 0 ? curPath : tail.key + curPath;
					json_object *val = json_object_array_get_idx(tail.value, (size_t)i);

					objects.push_back(JsonElem(objPath, val));
				}
				break;

			default:
				keyValues.push_back(new KeyValue(tail.key, tail.value));
			}
		}

		json_object_put(root_obj);

		return keyValues;
	}
}