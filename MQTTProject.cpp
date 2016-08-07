
#include "mraa.hpp"
#include "gpio.hpp"
#include "MQTTProject.hpp"
#include "iostream"
#include "linux.cpp"
#include "json/json.h"
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>

using namespace mraa;
using namespace std;
using namespace Json;

#define MQTTCLIENT_QOS2 		1

#define DEFAULT_STACK_SIZE 		-1
#define PORT_NUM				1883
int arrivedcount = 0;

int rc = 0;
IPStack ipStackVar = IPStack();
MQTT::Client<IPStack, Countdown> client = MQTT::Client<IPStack, Countdown>(ipStackVar);
float version;

void messageArrived(MQTT::MessageData& md)
{
	MQTT::Message &message = md.message;
	Gpio blinkPin(4, true);
	blinkPin.dir(DIR_OUT);

	blinkPin.write(1);
	sleep(1);
	blinkPin.write(0);
	sleep(1);

	printf("Message %d arrived: qos %d, retained %d, dup %d, packetid %d\n",
			++arrivedcount, message.qos, message.retained, message.dup, message.id);
	printf("Payload %.*s\n", message.payloadlen, (char*)message.payload);
}

void InitializeMQTTCommunication()
{
	version = 0.3;
	printf("Version is %f\n", version);

	const char* hostname = "52.207.148.30";						// iot.eclipse.org
	printf("Connecting to %s:%d\n", hostname, PORT_NUM);
	rc = ipStackVar.connect(hostname, PORT_NUM);
	if (rc != 0)
		printf("rc from TCP connect is %d\n", rc);

	printf("MQTT connecting\n");
	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	data.MQTTVersion = 3;
	data.clientID.cstring = (char*)"mbed-icraggs";
	rc = client.connect(data);
	if (rc != 0)
		printf("rc from MQTT connect is %d\n", rc);
	printf("MQTT connected\n");
}

unsigned char* GetMacIDOfMachine()
{
	struct ifreq ifr;
	struct ifconf ifc;
	char buf[1024];
	int success = 0;

	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock == -1) { /* handle error*/ };

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = buf;
	if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) { /* handle error */ }

	struct ifreq* it = ifc.ifc_req;
	const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));

	for (; it != end; ++it) {
		strcpy(ifr.ifr_name, it->ifr_name);
		if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
			if (! (ifr.ifr_flags & IFF_LOOPBACK)) { // don't count loopback
				if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
					success = 1;
					break;
				}
			}
		}
		else { /* handle error */ }
	}

	unsigned static char mac_address[6];

	if (success) memcpy(mac_address, ifr.ifr_hwaddr.sa_data, 6);

	return mac_address;
}

bool PublishToTopic(mqttMessageType &mqttMessage, const char* topic, MQTT::QoS qos)
{
	MQTT::Message message;
	message.qos = qos;
	message.retained = false;
	message.dup = false;

	mqttMessage.host = "XYZ";
	mqttMessage.shortMessage = "This is a short_message";
	char buffer[250];
	sprintf(buffer,
			"{\"host\": \"%s\", "
			"\"short_message\": \"%s\", "
			"\"Lattitude\": \"%f\", "
			"\"Longitude\": \"%f\", "
			"\"Message Title\": \"%s\", "
			"\"Message\": \"%s\" "
			"}",
			mqttMessage.host, mqttMessage.shortMessage.c_str(),
			mqttMessage.lattitude, mqttMessage.longitude,
			mqttMessage.messageTitle.c_str(), mqttMessage.message.c_str()
			);

	cout << buffer;
	message.payload = (void*)buffer;
	message.payloadlen = strlen(buffer) + 1;

	rc = client.publish(topic, message);
	if (rc != 0) {
		printf("Error %d from sending QoS 0 message\n", rc);
	}
	else
	{
		cout << "Message published successfully to " << topic << endl;
	}

	return true;
}

bool SubscribeToTopic(const char* topic, MQTT::QoS qos)
{
	rc = client.subscribe(topic, qos, messageArrived);
	if (rc != 0)
	{
		printf("rc from MQTT subscribe is %d\n", rc);
		return false;
	}
	else
	{
		cout << "Subscribed to " << topic << " successfully" << endl;
		return true;
	}
}

bool UnsubscribeFromTopic(const char* topic)
{
	// If the controller reaches here, it would unsubscribe and disconnect
	rc = client.unsubscribe(topic);
	if (rc != 0)
	{
		printf("rc from unsubscribe was %d\n", rc);
	}
}

void ReceiveData()
{
	client.yield(100);
	sleep(1);
}

void Disconnect()
{
	rc = client.disconnect();
	if (rc != 0)
		printf("rc from disconnect was %d\n", rc);
	else
		printf("Disconnected now.", rc);

	ipStackVar.disconnect();

}
