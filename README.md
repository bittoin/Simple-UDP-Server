# Simple UDP Server

Simple UDP Server to save data from embedded device on a Drone. The embedded device is a M5StickC-Plus board with MPU9250. When the server shuts down, the data is automatically stored in a csv file. The graphical interface will help us understand what the software is capable of.

## Tools

In the development process, some tools was used to make functionalities.

### Qt

Qt was used to make a cross platform graphical interface in order to be used on Linux and Windows. This is a powerful framework that offers a lot of resources that can be helpful on future improvements of the software.

> Qt Creator 5.0.1
> Kit on Linux: Desktop Qt 5.15.2 GCC 64bit
> Internal libraries:
>   - QDateTime
>   - QTimer
>   - QNetworkInterface
>   - QFileDialog
>   - QDesktopServices
> 
> [Download link](https://www.qt.io/download)

### qtcsv

Qtcsv is a small easy-to-use library for reading and writing csv files in Qt.

> Branch used: qt4_qt5
> [Access link](https://github.com/iamantony/qtcsv)

## How it works

<div align='center'>
    <img src="https://github.com/bittoin/Simple-UDP-Server/blob/main/images/interface-signals.png">
    <p>Figura 1. Server features</p>
</div>

#### 1. File Name

The csv file will be saved with this name. If leave blank, will got a random name.

#### 2. Choose Dir Button

Where the file will be saved. If leave blank, file will be saved on the same directory of the executable.

#### 3. Server Port

Server port. Must be set so the client can send data on this port. Default is 6666.

#### 4. Local IP List

Local IP list so it will be easier to see and use on UDP Client. This shows the same ip that you see on 'ifconfig' or 'ipconfig' commands in Linux and Windows.

#### 5. Start Server Button

Starts the UDP server and everytime that receives data in specific format, saves on csv object.

#### 6. Close Server Button

Closes the UDP server. Finishes data collect and automatically saves csv file.

#### 7. Server status

It's *green* when the server is working and *red* when it is off.

#### 8. Collection timer

If this field is active, the collection will last for the amount of seconds that is set. When the timer is over, automatically closes the server.

#### 9. Data file path

Path where the file was saved will be shown here when the server finishes.

#### 10. Open File Path Button

If clicked will open the directory where the file was saved.