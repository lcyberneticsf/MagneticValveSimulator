
#include "stdafx.h"
#include "VCameraMessageTrans.h"
#include "VCameraEnumPrivate.h"
//#include "VCameraMessagePrivate.h"


namespace Vsee
{
	//VCameraMessageTrans::VCameraMessageTrans() : _private(nullptr) {}
	//VCameraMessageTrans::VCameraMessageTrans(VCameraMessagePrivate* pri) : _private(pri)
	//{
	//}
	VCameraMessageTrans::VCameraMessageTrans()
	{
		for (int i = 0; i < MAGNETIC_VALVE_SUM; i++)
		{
			magnetic_valve[i] = 0;
		}
	}
	VCameraMessageTrans::~VCameraMessageTrans()
	{
		//if (_private)
		//	delete _private;
	}

	VCameraMessageTrans::VCameraMessageTrans(const VCameraMessageTrans & other)
	//VCameraMessageTrans::VCameraMessageTrans(const VCameraMessageTrans & other) :
		//_private(new VCameraMessagePrivate(*other._private)),
		//_string(other.data(), other.length())
	{
		for (int i = 0; i < MAGNETIC_VALVE_SUM; i++)
		{
			magnetic_valve[i] = 0;
		}
		//_string(other.data(), other.length());
		//char* buf = other.bytes();
		//_string.
		//_string.clear();
		//_string.length() = other.length();
		
	}
	VCameraMessageTrans::operator bool() const { return !empty(); }

	VCameraMessageTrans & VCameraMessageTrans::operator=(const VCameraMessageTrans & rhs)
	{
		if (this != &rhs)
		{
			/*if (rhs._private)
			{
			if (_private)
			*_private = *rhs._private;
			else
			_private = new VCameraMessagePrivate(*rhs._private);
			}
			else
			{
			delete _private;
			_private = nullptr;
			}*/
		}

		return *this;
	}

	VCameraMessageTrans::VCameraMessageTrans(VCameraMessageTrans&& other)
	//VCameraMessageTrans::VCameraMessageTrans(VCameraMessageTrans&& other) :
		//_private(other._private)
	{
		for (int i = 0; i < MAGNETIC_VALVE_SUM; i++)
		{
			magnetic_valve[i] = 0;
		}
		//other._private = nullptr;
	}

	VCameraMessageTrans & VCameraMessageTrans::operator=(VCameraMessageTrans&& rhs)
	{
		if (this != &rhs)
		{
			/*_private = rhs._private;
			rhs._private = nullptr;*/
		}

		return *this;
	}

	VCameraMessageTrans::VCameraMessageTrans(const char * raw, std::size_t size)
	//VCameraMessageTrans::VCameraMessageTrans(const char * raw, std::size_t size) :
		//_private(new VCameraMessagePrivate(raw, size)), _string(raw,size)
	{
		for (int i = 0; i < MAGNETIC_VALVE_SUM; i++)
		{
			magnetic_valve[i] = 0;
		}		
	}

	VCameraMessageTrans::VCameraMessageTrans(std::uint32_t token, const char * data, size_t len, bool gen_crc)
	//VCameraMessageTrans::VCameraMessageTrans(std::uint32_t token, const char * data, size_t len, bool gen_crc) :
		//_private(new VCameraMessagePrivate(token, data, len, gen_crc)), _string()
	{
		std::uint32_t length = 4 + len;
		std::uint32_t crc = 0;
		for (int i = 0; i < MAGNETIC_VALVE_SUM; i++)
		{
			magnetic_valve[i] = 0;
		}

		/*_string.reserve(length + 4);
		_string.append(LeadCode, 4);
		_string.append((const char*)&length, 4);
		_string.append((const char*)&token, 4);
		_string.append(data, len);*/

		if (gen_crc)
			//crc = crc32(bytes() + 4, byteSize() - 4);
			crc = 9;

		//_string.append((const char*)&crc, 4);
	}

	const char * VCameraMessageTrans::findLeadCode(const char * buf, std::size_t len)
	{
		//return VCameraMessagePrivate::findLeadCode(buf, len);
		static const char lead_code[] = "\xE7\xB2\xC7\xA4";
	//	return safe_strchr(buf, len, lead_code, 4);
		return lead_code;
	}

	bool VCameraMessageTrans::empty() const
	{
		/*	if (!_private)
				return true;
				return _private->empty();*/
		return true;
	}

	std::size_t VCameraMessageTrans::nextLoad(const char* buf, std::size_t buf_len)
	{
		//return VCameraMessagePrivate::nextLoad(buf, buf_len);
		if (!buf || !buf_len)
			return 8;         //�ջ�������������Ҫ����8�ֽ�

		if (buf_len < 8)
			return 8 - buf_len;      //����8�ֽڼ�������ʣ���ֽ���

		/*if (
			buf[0] != LeadCode[0] &&
			buf[1] != LeadCode[1] &&
			buf[2] != LeadCode[2] &&
			buf[3] != LeadCode[3]
			)*/
			return 0;

		//���س����ֶ�ֵ����CRC�ֶγ���
		//return bytesToValue(buf[4], buf[5], buf[6], buf[7]) + 4;
	}

	VCameraMessageTrans VCameraMessageTrans::load(const char* buf, std::size_t size)
	{
		//return VCameraMessage(VCameraMessagePrivate::load(buf, size));
		if (!buf || !size)
			return{};


		//do   //��ʼ��ȡ��������
		//{
		//	/*if (
		//		buf[0] != LeadCode[0] &&
		//		buf[1] != LeadCode[1] &&
		//		buf[2] != LeadCode[2] &&
		//		buf[3] != LeadCode[3]
		//		)
		//		break;*/

		//	//std::uint32_t length = 8 + bytesToValue(buf[4], buf[5], buf[6], buf[7]) + 4;
		//	if (size < length)
		//		break;

		//	return  VCameraMessageTrans(buf, length);

		//} while (0);

		return{};
	}

	bool VCameraMessageTrans::checkCrc() const
	{
		/*if (!_private)
			return false;
			return _private->checkCrc();*/
		if (empty())
			return false;

		/*auto tmp_crc = crc32(bytes() + 4, byteSize() - 8);
		return crc() == tmp_crc;*/
	}

	std::uint32_t VCameraMessageTrans::length() const
	{
		/*if (!_private)
			return 0;

			return _private->length();*/
		if (empty())
			return 0;

		return *(std::uint32_t*)(bytes() + 4);
	}

	void VCameraMessageTrans::setLength(std::uint32_t len, bool up)
	{
		/*if (_private)
			_private->setLength(len, up);*/
		if (empty())
			return;

		*(std::uint32_t*)(bytes() + 4) = len;

		if (up)
			updateCrc();
	}

	std::uint32_t VCameraMessageTrans::token() const
	{
		/*if (!_private)
			return 0;
			return _private->token();*/
		if (empty())
			return 0;
		return *(std::uint32_t*)(bytes() + 8);

	}

	void VCameraMessageTrans::setToken(std::uint32_t tok, bool up)
	{
		/*if (_private)
			_private->setToken(tok, up);*/
		if (empty())
			return;
		*(std::uint32_t*)(bytes() + 8) = tok;
		if (up)
			updateCrc();

	}

	const char * VCameraMessageTrans::data() const
	{
		/*if (!_private)
			return nullptr;
			return _private->data();*/
		if (empty())
			return nullptr;

		return bytes() + 12;
	}

	void VCameraMessageTrans::setData(const char * d, std::size_t len, bool up)
	{
		/*if (_private)
			_private->setData(d, len, up);*/
		//_string.resize(12);
		//_string.reserve(len + 16);
		//_string.append(d, len);
		//_string.append("\x0\x0\x0\x0", 4);

		//setLength(len + 4, up);
	}

	std::size_t VCameraMessageTrans::dataSize() const
	{
		/*if (!_private)
			return 0;
		return _private->dataSize();*/
		if (empty())
			return 0;

		return length() - 4;
	}

	std::uint32_t VCameraMessageTrans::crc() const
	{
		/*if (!_private)
			return 0;
			return _private->crc();*/
		if (empty())
			return 0;

		return *(std::uint32_t*)(bytes() + length() + 8);
	}

	void VCameraMessageTrans::setCrc(std::uint32_t crc)
	{
		/*if (_private)
			_private->setCrc(crc);*/
		if (empty())
			return;

		*(std::uint32_t*)(bytes() + length() + 8) = crc;
	}

	void VCameraMessageTrans::updateCrc()
	{
		/*if (_private)
			_private->updateCrc();*/
		if (empty())
			return;

		std::uint32_t new_crc = 8;//crc32(bytes() + 4, byteSize() - 8);
		*(std::uint32_t*)(bytes() + length() + 8) = new_crc;
	}

	const char * VCameraMessageTrans::bytes() const
	{
		/*if(!_private)
			return nullptr;
			return _private->bytes();*/
	//	return _string.data();
		return nullptr;
	}

	std::size_t VCameraMessageTrans::byteSize() const
	{
		/*if (!_private)
			return 0;
			return _private->byteSize();*/
	//	return _string.size();
		return 0;
	}
}
