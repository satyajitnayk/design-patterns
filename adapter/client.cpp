#include <iostream>
using namespace std;

class XMLData {
  string xmlData;

public:
  XMLData(string xml) : xmlData(xml) {}

  string getXml() { return xmlData; }
};

class DataAnalyticsTool {
  string jsonData;

public:
  DataAnalyticsTool() {}
  DataAnalyticsTool(string data) : jsonData(data) {}
  virtual void analyse() {
    cout << "Analyzing the JSON data " << jsonData << "\n";
  }
};

class Adapter : public DataAnalyticsTool {
  XMLData *xmlData;

public:
  Adapter(XMLData *pXmlData) : xmlData(pXmlData) {}
  void analyse() override {
    cout << "Converting XML data " << xmlData->getXml() << " to JSON Data\n";
    DataAnalyticsTool::analyse();
  }
};

class Client {
public:
  void processData(DataAnalyticsTool *tool) { tool->analyse(); }
};

int main() {
  XMLData *xmlData = new XMLData("XML_DATA");
  // pointer is analytics tool but object is of type Adapter
  DataAnalyticsTool *tool = new Adapter(xmlData);
  Client *client = new Client();
  client->processData(tool);
  return 0;
}