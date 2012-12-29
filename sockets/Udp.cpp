/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Udp.hh"

namespace network {
    namespace sockets {
        Udp::Udp()
        {}

        Udp::~Udp() {}

        void Udp::bind(const IAddr & pair)
        {

        }

        int Udp::send(const char * packet, int packetSize, const IAddr & pair)
        {
            return 0;
        }

        int Udp::recv(char * packet, int maxPacketSize, IAddr & pair)
        {
            return 0;
        }
    }
}
