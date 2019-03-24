#ifndef CMD_HNDLR_H
#define CMD_HNDLR_H

#ifdef __cplusplus
extern "C" {
#endif

int cmdParser(unsigned char ucmd, int fd_print);

#ifdef __cplusplus
}
#endif
#endif // CMD_HNDLR_H