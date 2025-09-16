# FTD-XML

上期所交易所系统及CTP柜台系统均使用FTD协议通讯，FTD协议的接口定义通常用XML文件描述，类似ctp-6.6.7.xml文件中的定义格式。

openctp通过CTPAPI头文件将数据结构定义统一到一个xml定义文件中，通过jinja2等模板脚本可以批量生成相关代码，CTPAPI头文件本身也是从这样的xml定义文件生成出来的。

CTPAPI-6.3.15~6.7.11各个版本接口的xml定义文件均可至openctp官网下载：[CTPAPI接口](http://openctp.cn/CTPAPI.html)

下面的jinja2脚本由ChatGPT生成，可以提取出xml文件中所有函数名：

```
import xml.etree.ElementTree as ET
from jinja2 import Template

# 1. 解析 XML
tree = ET.parse("ctp-6.6.7.xml")
root = tree.getroot()

packages = []
for pkg in root.find("packages").findall("package"):
    packages.append(pkg.attrib["name"])

# 2. Jinja2 模板
template_str = """
{% for name in packages %}
{{ name }}
{% endfor %}
"""

template = Template(template_str)

# 3. 渲染输出
output = template.render(packages=packages)
print(output)
```
