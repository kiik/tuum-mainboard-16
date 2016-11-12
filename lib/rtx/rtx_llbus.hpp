/** @file rtx_llbus.hpp
 *  @brief Low-level communication bus interface.
 *
 *  @authors Meelik Kiik
 *  @date 8. October 2016
 *  @version 0.1
 */

#ifndef RTX_LLBUS_H
#define RTX_LLBUS_H

#include <mbed.h>
#include <USBSerial.h>

#define llbus_t Serial

//#define llbus_decl() USBSerial gBus
#define llbus_decl() Serial gBus(USBTX, USBRX)

namespace rtx { namespace llb {

  const size_t PCKBUF_SIZE = 64;
  const size_t PCKBUF_N = 4;

  struct packet_buf_t {
    char buf[PCKBUF_SIZE][PCKBUF_N];
    char* cbuf;

    size_t char_seq, buf_seq ;
    size_t avail_ix;
    volatile size_t bf_lock;

    packet_buf_t():
      cbuf(buf[0]),
      char_seq(0), buf_seq(0),
      avail_ix(PCKBUF_N), bf_lock(PCKBUF_N)
    {

    }

    void stream(const char c) {
      if(c == '\n') {
        cbuf[char_seq] = '\0';
        swap();
        return;
      }

      cbuf[char_seq] = c;
      char_seq = (char_seq + 1) % PCKBUF_SIZE;
    }

    void stream(const char* data) {
      size_t len = strlen(data);

      for(size_t i=0; i < len; i++)
        stream(data[i]);
    }

    void swap() {
      if(avail_ix >= PCKBUF_N) avail_ix = buf_seq;

      buf_seq = (buf_seq + 1) % PCKBUF_N;
      cbuf = buf[buf_seq];
      char_seq = 0;
    }

    int read(char*& out, size_t& len) {
      if(avail_ix >= PCKBUF_N) return -1;
      int res = 0;

      bf_lock = avail_ix;

      char* bf = buf[avail_ix];
      len = strlen(bf);

      if(len < 5) {
        len = 0;
        res = -2;
        goto SKIP;
      }

      out = new char[len];
      strcpy(out, bf);

SKIP:
      size_t ix = (avail_ix + 1) % PCKBUF_N;
      if(ix != buf_seq) avail_ix = ix;
      else avail_ix = PCKBUF_N;

      bf_lock = PCKBUF_N;

      return res;
    }

  };


  extern llbus_t gBus;

  void setup();

  int read(char*&, size_t&);
  int write(char* size_t);

}}

#endif
