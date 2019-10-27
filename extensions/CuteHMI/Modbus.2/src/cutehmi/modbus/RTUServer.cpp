#include <cutehmi/modbus/RTUServer.hpp>

namespace cutehmi {
namespace modbus {

constexpr int RTUServer::MIN_SLAVE_ADDRESS;
constexpr int RTUServer::MAX_SLAVE_ADDRESS;
const char * RTUServer::INITIAL_PORT = internal::RTUServerConfig::INITIAL_PORT;
constexpr QSerialPort::Parity RTUServer::INITIAL_PARITY;
constexpr QSerialPort::BaudRate RTUServer::INITIAL_BAUD_RATE;
constexpr QSerialPort::DataBits RTUServer::INITIAL_DATA_BITS;
constexpr QSerialPort::StopBits RTUServer::INITIAL_STOP_BITS;
constexpr int RTUServer::INITIAL_SLAVE_ADDRESS;
constexpr int RTUServer::INITIAL_COILS_ADDRESS_RANGE_MIN;
constexpr int RTUServer::INITIAL_COILS_ADDRESS_RANGE_MAX;
constexpr int RTUServer::INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MIN;
constexpr int RTUServer::INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MAX;
constexpr int RTUServer::INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MIN;
constexpr int RTUServer::INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MAX;
constexpr int RTUServer::INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MIN;
constexpr int RTUServer::INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MAX;

RTUServer::RTUServer(QObject * parent):
	AbstractServer(parent),
	m(new Members(& coilData(), & discreteInputData(), & holdingRegisterData(), & inputRegisterData()))
{
	m->backend.moveToThread(& m->thread);

	connect(& m->thread, & QThread::finished, & m->backend, & internal::QtRTUServerBackend::ensureClosed);

	connect(this, & RTUServer::requestReceived, & m->backend, & internal::QtRTUServerBackend::processRequest);

	connect(& m->backend, & internal::AbstractServerBackend::busyUpdated, this, & RTUServer::updateBusy);

	connect(& m->backend, & internal::AbstractServerBackend::replied, this, & RTUServer::handleReply);

	connect(& m->backend, & internal::AbstractServerBackend::stateChanged, this, & RTUServer::setState);

	connect(& m->backend, & internal::QtRTUServerBackend::closed, this, & RTUServer::stopped);

	connect(& m->backend, & internal::QtRTUServerBackend::errored, this, & RTUServer::broke);
	connect(& m->backend, & internal::QtRTUServerBackend::closed, this, & RTUServer::broke);

	connect(& m->backend, & internal::QtRTUServerBackend::opened, this, & RTUServer::started);

	connect(& m->backend, & internal::QtRTUServerBackend::coilsWritten, this, & RTUServer::handleCoilsWritten);
	connect(& m->backend, & internal::QtRTUServerBackend::discreteInputsWritten, this, & RTUServer::handleDiscreteInputsWritten);
	connect(& m->backend, & internal::QtRTUServerBackend::holdingRegistersWritten, this, & RTUServer::handleHoldingRegistersWritten);
	connect(& m->backend, & internal::QtRTUServerBackend::inputRegistersWritten, this, & RTUServer::handleInputRegistersWritten);

	m->thread.start();
}

RTUServer::~RTUServer()
{
	m->thread.quit();
	m->thread.wait();
}

QString RTUServer::port() const
{
	return m->config.port();
}

void RTUServer::setPort(const QString & port)
{
	if (m->config.port() != port) {
		m->config.setPort(port);
		emit portChanged();
	}
}

QSerialPort::Parity RTUServer::parity() const
{
	return m->config.parity();
}

void RTUServer::setParity(QSerialPort::Parity parity)
{
	if (m->config.parity() != parity) {
		m->config.setParity(parity);
		emit parityChanged();
	}
}

QSerialPort::BaudRate RTUServer::baudRate() const
{
	return m->config.baudRate();
}

void RTUServer::setBaudRate(QSerialPort::BaudRate baudRate)
{
	if (m->config.baudRate() != baudRate) {
		m->config.setBaudRate(baudRate);
		emit baudRateChanged();
	}
}

QSerialPort::DataBits RTUServer::dataBits() const
{
	return m->config.dataBits();
}

void RTUServer::setDataBits(QSerialPort::DataBits dataBits)
{
	if (m->config.dataBits() != dataBits) {
		m->config.setDataBits(dataBits);
		emit dataBitsChanged();
	}
}

QSerialPort::StopBits RTUServer::stopBits() const
{
	return m->config.stopBits();
}

void RTUServer::setStopBits(QSerialPort::StopBits stopBits)
{
	if (m->config.stopBits() != stopBits) {
		m->config.setStopBits(stopBits);
		emit stopBitsChanged();
	}
}

int RTUServer::slaveAddress() const
{
	return m->config.slaveAddress();
}

void RTUServer::setSlaveAddress(int slaveAddress)
{
	if (m->config.slaveAddress() != slaveAddress) {
		m->config.setSlaveAddress(slaveAddress);
		emit slaveAddressChanged();
	}
}

void RTUServer::setBusy(bool busy)
{
	emit m->backend.setBusyRequested(busy);
}

void RTUServer::open()
{
	emit m->backend.openRequested();
}

void RTUServer::close()
{
	emit m->backend.closeRequested();
}

}
}

//(c)C: Copyright © 2019, Michal Policht <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
