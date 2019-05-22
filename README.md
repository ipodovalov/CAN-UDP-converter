Есть устройство с Linux в качестве ОС. Данное устройство имеет Ethernet 
и несколько интерфейсов CAN. Необходимо разработать скрипт или программу, 
позволяющую использовать данное устройство как конвертер UDP-to-CAN, 
где каждому CAN-устройству соответствует определенный приемный UDP-порт, 
данные с которого передаются в соответствующий CAN, и наоборот, данные, 
пришедшие из CAN, передаются на другой, заранее определенный UDP-порт 
по заранее определенному IP-адресу. В качестве API работы
с CAN рекомендуется использовать SocketCAN.

Решение увидел следующее:
пишем два процесса:
udp_worker - получает и отправляет данные по UDP;
can_worker - получает и отправляет данные по CAN;
обмениваются данными эти процессы между собой посредством механизма
разделяемой памяти. Сделал так. Однако очевидно:

Это всё-таки не UNIX-way. Еще больше нужно процессов:
во-первых, слушать UDP порты нужно только одним процессом, только слушать
(т.е. принимать) и больше ничего. И этот процесс, кроме того,
должен форкаться (или на потоки его надо делить) для каждого UDP-порта.
Потому что сейчас пока recivefrom() блокирует сокет одного порта, другие
порты в пролёте и мы данные теряем. И ещё так нам будет легче увеличивать
количество портов (сейчас их два только), количество вшито в код,
значит программа не масштабируемая. Что тоже не UNIX-way(((

Во-вторых отправлять данные в UDP нужно ещё одним процессом, но тут надо
вспоминать как делить ресурсы, нужно почитать Стивенса.

Тоже самое нужно сказать про CAN приём/передачу. Так как формат фрейма
данных CAN таков, что приём и передачу можно осуществлять только 
небольшими порциями (8 байт каждая), то следует также разделить приём и
передачу на разные потоки (лучше процессы).

И ещё наверное эту задачу можно ещё легче решить. На каком-нибудь пайтоне.
А может даже на баше.

Исполняемые файлы будут лежать в каталоге overlay/usr/sbin/
Также задействовал две библиотеки: libelogger.so, libini.so
собираются скриптами, лежат в соответствующих libs/<имя_библиотеки>/build 
каталогах. Собранные библиотеки нужно положить по стандартным путям
на устройстве или HOST машине.
Библиотеки для логгирования одна, другая для чтения конфиг-файлов.

<b>
Сборку для реального Embedded устройства на базе процессора<br>
Texas Instruments AM-335 (ARM Cortex-A8) (если установлен необходимый<br>
toolchain) осуществлять командой:<br>
./build_embedded.sh<br>
</b>
<br>
<b>
Сборку для host-машины командой:<br>
./build_host.sh<br>
</b>
