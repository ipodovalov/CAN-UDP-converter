#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <cstdint>
#include <string>

//extern "C" {
#include <embtime.h>
//}

typedef std::basic_string<uint8_t> byte_array;

typedef float float32_t;

//! Коды ошибок
enum ERROR_CODE : uint8_t {
    E_OK                            = 0x00, /*!< Успешное завершение */
    E_ALLOC_ERROR                   = 0x01, /*!< Ошибка выделения памяти */
    E_TIMEOUT                       = 0x02,
    E_NULL                          = 0x03,
    E_DEVICE_NOT_PRESENT            = 0x04,
    E_CHECKSUM_ERROR                = 0x05,
    E_CLOCK_ERROR                   = 0x06,
    E_FAIL                          = 0x07,
    E_INVALID_DATA                  = 0x08,
    E_LEN_ERROR                     = 0x09,
    E_BUFFER_OVERFLOW               = 0x0A,
    E_BUFFER_UNDERFLOW              = 0x0B,
    E_INVALID_LENGTH                = 0x0C,
    E_SYNC_ERROR                    = 0x0D,
    E_LOCK_ERROR                    = 0x0E,
    E_INVALID_ADDRESS               = 0x0F,
    E_TOO_LATE                      = 0x10,
    E_DEVICE_BUSY                   = 0x11,
    E_PORT_CLOSED                   = 0x12,
    E_WRITE_ERROR                   = 0x13,
    E_READ_ERROR                    = 0x14,
    E_INVALID_ANSWER                = 0x15,
    E_DB_OPEN_ERROR                 = 0x16,
    E_DB_ERROR                      = 0x17,
    E_MORE_BYTES                    = 0x18,
    E_SOCKET_ERROR                  = 0x19,
    E_HOSTNAME_ERROR                = 0x1A,
    E_CONNECT_ERROR                 = 0x1B
};

typedef struct __attribute__ ((__packed__)) {
    uint8_t flags;
    // кол-во секунд с 00:00:00 01-01-2010
    embtime_t time;
    // 24 бита (значение XXXX.XXXX >> 3)
    uint8_t latitude[3];
    // 24 бита (значение XXXX.XXXX >> 3)
    uint8_t longitude[3];
    uint8_t speed;
    // значене курса в градусах >> 1
    uint8_t course;
} gps_data_record_t;

typedef struct __attribute__ ((__packed__)) {
    size_t  response_len;
    uint8_t read_result;
} msu_data_record_t;

typedef struct __attribute__ ((__packed__)) {
    embtime_t   time;
    float32_t   left_sensor_raw;
    float32_t   right_sensor_raw;
    uint16_t    fuel_weight;
    int8_t      fuel_temperature;
    float32_t   fuel_density;
    uint16_t    fuel_volume;
} fuel_data_record_t;

typedef struct __attribute__ ((__packed__)) {
    embtime_t   time_stamp;
	int16_t     zerkalo[20];
	uint16_t    zer_size;
} can_data_t;

#define BUF_SIZE 1500                        // длина UDP пакета

typedef struct __attribute__ ((__packed__)) {
    embtime_t  time_stamp ;
    struct timespec nano_time_stamp ;
    uint8_t datagram[BUF_SIZE] ;		    // свежий UDP-пакет
    uint16_t useful_size ;
} msu_karat_bks_data_t;

#endif // TYPEDEFS_H