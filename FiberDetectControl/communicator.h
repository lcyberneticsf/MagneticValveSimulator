#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H
#include "VAsyncIO.h"
#include <queue>
#include <mutex>
#include "VTx2Session.h"
#include "VCameraMessageTrans.h"
using namespace asio::ip;


namespace asio {
	class io_service;
	class VTx2Session;
	namespace ip {
		class tcp;
		template <typename InternetProtocol>
		class basic_endpoint;
	}
	template <typename Protocol>
	class stream_socket_service;
	template <typename Protocol,
		typename StreamSocketService = stream_socket_service<Protocol> >
	class basic_stream_socket;
}

namespace Vsee{
	class VCameraFrame;
}

namespace aq {

class Communicator;

enum CMD
{
    SEND_RESULTS   = 71,
    START_RECV_IMG = 1,
    STOP_RECV_IMG  = 2
};

enum RESULT_STATE
{
    NO         = 0,
    OK         = 1,
    V_WRINKLED = 2,
    WRINKLED   = 3,
    V_DEFORMED = 4,
    DEFORMED   = 5
};

//***********Protocol,use to driver Leihang Valve electric board,Begin*******************************
/*
Name : typedef struct _time_calib_req_tag_:
Function: Time correction ask frame;
ʱ��У׼֡������һ��Agent��������I/O-Server������ʱ�̷���ʱ��У׼��,�ð�����ͬ��Agent��I/O-Server��ʱ�������ġ�
Agent��I/O-Server�������µİ���payload_len=8�������� type ������� 0x80000010 ������;src ������� 0xCC880000���������ͣ�Ϊʱ��У׼��;
*/
typedef struct _time_calib_req_tag_
{
	uint32_t type;
	uint32_t src;
}time_calib_req_t;


/*
Name : typedef struct _ack_tag_:
Function: Time correcting frame response
I/O-Server�յ��������󣬻���Agent�������µİ���payload_len=16��, ���� type �� 0x80000000����Ӧ��;
���� ack_src �� 0xCC8800DE����ӦԴ��Ϊʱ��У׼���󣩣�����֮ǰ���͸�I/O-Server��ʱ��У׼�������ͣ�,
��ack_val��һ�� 64-bit�ľ��ԷǸ�����������I/O-Server�ڲ��ľ���ʱ��δ�ֵ��ÿ���δ�Ҳ����ÿ��������1�������� 0.1us����Ӧ�ڲ�10mhz�Ĺ���ʱ��Դ��
ע�⣺ack_val �� int64 Ȼ�����˴��������ľ�����ֵ�����ǷǸ���, ����� ack_src ��ʾ ��Ϊʱ��У׼���� ����ӦԴ;
�� ack_val Ϊ����ʱ����ô����һ��δ����İ�; AgentӦ�����Դ˰�.
*/
typedef struct _ack_tag_
{
	uint32_t type;
	uint32_t ack_src;
	int64_t ack_val;
} ack_t;


/*
Name : typedef struct _io_output_transac_tag_
function: I/O-Server ������֡
Agent �� I/O-Server�������µİ���payload_len=20��, ���� type ������� 0x80000010 ������;src ������� 0xCC880004���������ͣ�ΪI/O��������;
port��ӦӲ������˿ں��룬�Ϸ�ֵΪ��1 ~ 28�����ֵ���Ϸ���ô�ð�������, ͬʱI/O����ҵ�񽫲����κ�һ��Ӳ���˿�ִ��, ref - �ο�ʱ�䣬���ڵ� 1 С���У�
ͨ��ʱ��У׼��õ� ��ack_val��, ����I/O-Server�ڲ��ľ���ʱ��δ�ֵ��ÿ���δ�Ҳ����ÿ��������1��������0.1us����Ӧ�ڲ�10mhz�Ĺ���ʱ��Դ��;
delay - �����ӳ�ֵ����ֵ �� 0.1us����Ϊ��I/O ��������� ref ���ӳ�ֵ, dura - I/O����ʱ�䣬��ֵ �� 0.1us����Ϊ I/O ��������״̬��ON State����ʱ��
*/
typedef struct _io_output_transac_tag_
{
	uint32_t type;
	uint32_t src;
	uint32_t port;
	uint32_t ref;
	uint32_t delay;
	uint32_t dura;
}io_output_transac_t;

typedef struct _io_valve_friver_tag_
{
	uint32_t type;
	uint32_t src;
	int32_t port;
	int32_t ref;
	int32_t delay;
	int32_t dura;
}io_valve_friver_tag;

class Communicator
{
private:
    static std::vector<std::string> split(std::string str, char seg);
    static void print_hex(unsigned char *_buf,int _len);
public:
    Communicator();

    bool tcp_connect(std::string _ip, int _port, std::string& _error_str);

    bool receive_img(std::string& _error_str);
	bool receive_img(std::string &_error_str, asio::basic_stream_socket<asio::ip::tcp>* socket_);
    bool send_cmd(CMD _cmd, std::string& _error_str, std::vector<int> _state = std::vector<int>(), int _sequence = -1);

	bool server(std::string _ip, int _port, std::string &_error_str);
	bool udp_rcv_server(std::string _ip, int _port, std::string &_error_str);
	//bool udp_server(std::string _ip, int _port, std::string &_error_str);
	bool server_run(asio::basic_stream_socket<asio::ip::tcp>* socket_, std::string _ip, int _port, std::string &_error_str);
	bool get_file_list(std::string file_load_path);
	int		get_files(std::string fileFolderPath, std::string fileExtension, int& nFileNum);
	bool run_tcp_connect(std::string _ip, int _port);
	bool tcp_connect_thread(std::string _ip, int _port);

	int     udp_send_server(std::string _ip, int _port);
	int		udp_send_client(std::string _ip, int _port);
	int     streamReadMaxBytesInTime(asio::ip::udp::socket udp_server, char* strBuf, int nMaxBytes, int nMilSec, asio::ip::udp::endpoint send_point);

	std::queue<Vsee::VCameraFrame>* frame_queue_;
	std::mutex m_;

//private:
public:
	asio::io_service* io_service_;
	//asio::ip::basic_endpoint<asio::ip::tcp>* ep_;
	tcp::endpoint  * ep_;
	asio::basic_stream_socket<asio::ip::tcp>* socket_;
	std::string data_buffer_;
	asio::ip::tcp::socket* _socket;

	//asio::tcp::acceptor acceptor_;

	Vsee::VTx2Session* sessions[8];
	tcp::socket* sockets[8];
	asio::io_service* ios[8];
	std::queue<Vsee::InferFrame> infer_queue;
	std::mutex             infer_mutex;
	Vsee::InferFrame infer_frame;
	tcp::endpoint eps[8];
	std::vector<std::string> file_list;
	int file_amount;
	static bool batch_image_load;
	static bool single_image_load;
	static bool    m_bServerSendMode;
	static bool    m_bClientSendMode;
	static bool		m_bServerRun;
	static bool		m_bClientRun;
	int		counter;
	int		camera_scan_speed;
	static  Vsee::VCameraMessageTrans  box_ctrl_msg;
	char   m_strMsgSend[64];
	Vsee::VCameraMessageTrans MsgPost;
	static std::mutex mutex_magnetic_valve;
	static  Vsee::VCameraMessageTrans*  valve_ctrl_msg;

	static _io_valve_friver_tag_  valve_driver[MAGNETIC_VALVE_SUM];
};

}

#endif // COMMUNICATOR_H
