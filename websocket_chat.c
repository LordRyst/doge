/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include "mongoose.h"
#include "players.h"
#include "messages.h"
#include "game.h"

static sig_atomic_t s_signal_received = 0;
static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

static void signal_handler(int sig_num) {
  signal(sig_num, signal_handler);  // Reinstantiate signal handler
  s_signal_received = sig_num;
}

static int is_websocket(const struct mg_connection *nc) {
  return nc->flags & MG_F_IS_WEBSOCKET;
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  switch (ev) {
    case MG_EV_WEBSOCKET_HANDSHAKE_DONE: {
      /* New websocket connection. Tell everybody. */
      //broadcast(nc, mg_mk_str("++ joined"));
	  PlayersAdd(nc);
      break;
    }
    case MG_EV_WEBSOCKET_FRAME: {
      struct websocket_message *wm = (struct websocket_message *) ev_data;
      /* New websocket message. Tell everybody. */
      struct mg_str d = {(char *) wm->data, wm->size};
      //broadcast(nc, d);
	  MessagesAdd(nc, (char *) wm->data, wm->size);
      break;
    }
    case MG_EV_CLOSE: {
      /* Disconnect. Tell everybody. */
      if (is_websocket(nc)) {
        //broadcast(nc, mg_mk_str("-- left"));
		PlayersRemove(nc);
      }
      break;
    }
	case MG_EV_HTTP_REQUEST: {
		mg_serve_http(nc, (struct http_message *) ev_data, s_http_server_opts);
	}
  }
}

int main(void) {
    struct mg_mgr mgr;
  	struct mg_connection *nc;

  	signal(SIGTERM, signal_handler);
 	signal(SIGINT, signal_handler);
  	setvbuf(stdout, NULL, _IOLBF, 0);
  	setvbuf(stderr, NULL, _IOLBF, 0);

  	mg_mgr_init(&mgr, NULL);

  	nc = mg_bind(&mgr, s_http_port, ev_handler);
  	s_http_server_opts.document_root = ".";
  	mg_set_protocol_http_websocket(nc);

  	printf("Started on port %s\n", s_http_port);
  	while (s_signal_received == 0) {
	  mg_mgr_poll(&mgr, 200);//0 to make faster.
		GameLoop();
  	}
  	mg_mgr_free(&mgr);

  	return 0;
}
