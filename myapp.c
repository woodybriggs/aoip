#include <pjlib.h>
#include <pjlib-util.h>
#include <pjmedia.h>
#include <pjmedia-codec.h>
#include <pjsip.h>
#include <pjsip_simple.h>
#include <pjsip_ua.h>
#include <pjsua-lib/pjsua.h>
#include <pj/log.h>
#include <stdio.h>

int main() {

  pj_status_t rc;

  rc = pj_init();

  pj_status_t status;
  struct pjmedia_rtp_session session;

  status = pjmedia_rtp_session_init (&session, 1, 0);

  return 0;
}
