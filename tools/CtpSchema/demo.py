import json

# 读取类型数据
with open("output6.6.9/types.json", "r", encoding="utf8") as fb:
    schema_types = json.load(fb)
types = schema_types["definitions"]
# 读取struct数据
with open("output6.6.9/structs.json", "r", encoding="utf8") as fb:
    schema_structs = json.load(fb)

structs = schema_structs["definitions"]

# 读取交易API数据
with open("output6.6.9/tdapi.json", "r", encoding="utf8") as fb:
    schema_trader_api = json.load(fb)
# 遍历请求方法
for api, value in schema_trader_api["properties"]["CThostFtdcTraderApi"]["properties"].items():
    print("方法", api, value["title"])

    for key, _values in value.get("properties", {}).items():
        end = " " if _values else "\n"
        print("\t参数", key, end=end)
        for param, param_value in _values.items():
            if "$ref" == param:
                values = param_value.split("/")
                src, name = values[0], values[-1]
                if src == "structs.json#":
                    # 引用自定义结构体
                    struct = structs[name]
                    print(struct["title"])
                    for field, field_props in struct["properties"].items():
                        print("\t\t字段", field, field_props["title"])
                        # 字段的具体类型, 可以通过 field_props 进一步处理
                elif src == "types.json#":
                    # 引用自定义类型
                    pass
            else:
                if param == "title":
                    print(param_value)
                elif param == "type":
                    print("\t\t类型", param_value)
