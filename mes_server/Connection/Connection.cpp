

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Connection.h"


using boost::asio::ip::tcp;




//void Connection::start(const boost::system::error_code& error) {
//    if (!error) {
//        socket_.async_read_some(boost::asio::buffer(nickname_, nickname_.size()),
//                                strand_.wrap(boost::bind(&Connection::name_handler,
//                                                         shared_from_this(),
//                                                         _1)));
//    }
//}
//
//void Connection::on_message(std::array<char, MAX_IP_PACK_SIZE> &msg) {
//    bool write_in_progress = !write_msgs_.empty();
//    write_msgs_.push_back(msg);
//    if (!write_in_progress) {
//        boost::asio::async_write(socket_,
//                                 boost::asio::buffer(write_msgs_.front(), write_msgs_.front().size()),
//                                 strand_.wrap(boost::bind(&Connection::write_handler, shared_from_this(), _1)));
//    }
//}
//
//void Connection::name_handler(const boost::system::error_code &error) {
//    std::cout << "username : "<< nickname_.data() << std::endl;
//    room_.enter(shared_from_this(), std::string(nickname_.data()));
//    read_msg_.consume(read_msg_.size());
//    boost::asio::async_read_until(socket_, read_msg_, "\r\n",
//                                  strand_.wrap(boost::bind(&Connection::read_handler, shared_from_this(), _1)));
//}
//
//void Connection::read_handler(const boost::system::error_code &error) {
//    if (!error) {
//        if (!this) {
//            return;
//        }
//        room_.mailing(read_msg_, shared_from_this());
//        read_msg_.consume(read_msg_.size());
//        boost::asio::async_read_until(socket_, read_msg_, "\r\n",
//                                      strand_.wrap(boost::bind(&Connection::read_handler, shared_from_this(), _1)));
//    } else {
//        room_.leave(shared_from_this());
//    }
//}
//
//void Connection::write_handler(const boost::system::error_code &error) {
//    if (!error) {
//        write_msgs_.pop_front();
//
//        if (!write_msgs_.empty())
//        {
//            boost::asio::async_write(socket_,
//                                     boost::asio::buffer(write_msgs_.front(), write_msgs_.front().size()),
//                                     strand_.wrap(boost::bind(&Connection::write_handler, shared_from_this(), _1)));
//        }
//    }
//    else
//    {
//        room_.leave(shared_from_this());
//    }
//}