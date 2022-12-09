/******************************************************************************
 * Copyright (C) 2022 by Gschwind, Weber, Schoch, Niederberger                *
 *                                                                            *
 * This file is part of linescaleGUI.                                         *
 *                                                                            *
 * LinescaleGUI is free software: you can redistribute it and/or modify       *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation, either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * LinescaleGUI is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with linescaleGUI. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/
/**
 * @file commDevice.h
 * @authors Gschwind, Weber, Schoch, Niederberger
 *
 * @brief Abstract base class for each type of connection
 *
 */

#pragma once
#ifndef COMMDEVICE_H_
#define COMMDEVICE_H_

#include <QDebug>
#include <QObject>

/**
 * @brief Enum to describe the type used for a specific connection
 *
 */
enum connType {
    BLE,  ///< Bluetooth low energy
    USB,  ///< Serial port via USB-mini
};

/**
 * @brief Struct to identify a device
 * Used to connect to one device.
 *
 */
struct deviceInfo {
    connType type;  ///< Type of connection
    QString ID;     ///< Identifier of a given connection; e.g. COM101
    int baudRate;   ///< Baudrate, used by USB connection
};

/**
 * @brief Base class for every connection
 *
 */
class CommDevice : public QObject {
    Q_OBJECT

   public:
    /**
     * @brief Connect device to host
     * Implemented in USB or BLE class
     *
     * @return true Connection established successfully
     * @return false Connection failed
     */
    virtual bool connectDevice() { return false; };

    /**
     * @brief Disconnect device from host
     * Implemented in USB or BLE class
     *
     */
    virtual void disconnectDevice(){};

    /**
     * @brief Send date to the connected device
     *
     * @param data HEX values as a QByteArray to send
     */
    virtual void sendData(QByteArray data) { qDebug() << data; };

    /**
     * @brief Method to read data from the connected device.
     *
     * Called by e.g. SerialPort::readReady
     *
     */
    virtual void readData(){};

    /**
     * @brief Set a new frequency
     *
     * @param newFreq New freq in Hertz, 10, 40, 640 or 1280
     */
    void setFreq(int newFreq) { freq = newFreq; };

    /**
     * @brief Get the Freq object
     *
     * @return int Current frequency in Hertz
     */
    int getFreq() { return freq; };

    /**
     * @brief Get the Identifier of the connection
     *
     * @return QString Unique identifier for this connection
     */
    QString getIdentifier() { return identifier; };

    /**
     * @brief Get the connection type of the connection
     *
     * @return connType enum with the type
     */
    connType getConnType() { return type; };

    /**
     * @brief Get the connection status
     *
     * @return true if connected
     */
    bool getStatus() { return connected; };

   signals:
    /**
     * @brief Emit after a package was received and parsed
     *
     * @param value
     */
    void newForceDevice(float value);

    /**
     * @brief Emit after connection / disconnection to trigger UI changes
     *
     * @param connected
     */
    void changedStateDevice(bool connected);

   protected:
    int freq = 10;                  ///< Sample frequency of the connection
    QString identifier;             ///< Unique identifier
    connType type = connType::USB;  ///< USB or BLE
    bool connected;
};

#endif  // COMMDEVICE_H_
