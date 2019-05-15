#include "msudevicedriver.h"

#include <iostream>
#include <cassert>
#include <cstring>

#include <elogger.h>

EthernetDeviceDriver::EthernetDeviceDriver(uint16_t port1, uint16_t port2) :
    UDPSocket1(NULL), UDPSocket2(NULL)
{
    UDPSocket1 = new DatagramSocket(port1, "255.255.255.255", TRUE, TRUE); ;
    assert(Socket1 != NULL);
    UDPSocket2 = new DatagramSocket(port2, "255.255.255.255", TRUE, TRUE); ;
    assert(Socket2 != NULL);
}

EthernetDeviceDriver::~EthernetDeviceDriver() {
    if (UDPSocket1 != NULL) {
        delete UDPSocket1;
    }
    if (UDPSocket2 != NULL) {
        delete UDPSocket2;
    }
}

ERROR_CODE EthernetDeviceDriver::getData(byte_array &response, uint32_t read_timeout)
{
  uint8_t buf[PACKET_READ_BUF_SIZE];

      // Чтение доступных байт из порта устройства
      uint16_t bytesReaded = portIO->read(buf, sizeof(buf), read_timeout*1000);
      uint16_t packetLen = 0;

      // Если в порт ничего не пришло, выходим из цикла
      if (bytesReaded <= 0) {
		  printf("Не пришло ничего в порт: %d\n", bytesReaded);
          return E_TIMEOUT;
      }
/*
      printf("Прочитано байт: %d\n", bytesReaded);
      for (size_t i = 0; i < bytesReaded; i++) {
          printf(" %X", buf[i]);
      }
      printf("\n");
*/  
    return E_OK;
}

ERROR_CODE MSUDeviceDriver::sendData(const can_data_t &CANData) {
    byte_array packet;      // Байтовый буфер данных для отправки в сеть
    
    ssize_t bytesWritten;

    // Добавление данных тела пакета в буфер для отправки
    packet.append(reinterpret_cast<const uint8_t *>(&CANData), sizeof(CANData));

    /*
    std::cerr << "Writing packet: ";

    for (size_t i = 0; i < packet.size(); i++) {
        fprintf(stderr, "%.2X ", packet.at(i));
    }

    std::cerr << std::endl;
    */

	// Тут определяем в какой порт отправлять данные

    // Отправка сформированного буфера в нужный UDP порт 
    bytesWritten = UDPSocket1->send(packet.c_str(), packet.size());
    bytesWritten = UDPSocket2->send(packet.c_str(), packet.size());
	
	ELOG(ELogger::INFO_DEVICE, ELogger::LEVEL_TRACE) << "Отправлен пакет (" << packet.size() << " байт ):" << packet;

    if ((bytesWritten >= 0) && (bytesWritten == packet.size())) {
        return E_OK;
    } else {
        return E_WRITE_ERROR;
    }
}