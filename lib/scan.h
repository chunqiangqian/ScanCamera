#ifndef SCANE_H
#define SCANE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <iostream>
#include <linux/videodev2.h>
#include <stdint.h>
#include <dirent.h>
#include <vector>

struct v4l2_buf_unit {
    int                index;
    void*              start;
    uint32_t           length;
    uint32_t           offset;
};

struct v4l2_buf {
    struct v4l2_buf_unit* buf;
    int nr_bufs;
    enum v4l2_buf_type type;
};


int usb_camera_open(const char *dev, v4l2_buf** mV4l2Buf, std::string &card);

/*
 * 函数名称：v4l2_open
 * 功能描述：打开v4l2设备
 * 输入参数：name - 设备名字
 * 输入参数：flag - 打开设备标志，与open相同
 * 输出参数：无
 * 返 回 值：失败返回-1;成功返回文家描述符
 */ 
int v4l2_open(const char* name, int flag);



/*
 * 函数名称：v4l2_close
 * 功能描述：关闭v4l2设备
 * 输入参数：fd - v4l2设备的文件描述符
 * 输出参数：无
 * 返 回 值：失败返回-1;成功返回0
 */ 
int v4l2_close(int fd);



/*
 * 函数名称：v4l2_querycap
 * 功能描述：查询v4l2设备功能
 * 输入参数：fd   - v4l2设备的文件描述符
 * 输出参数：cap  - 得到的设备信息
 * 返 回 值：失败返回-1;成功返回0
 */
int v4l2_querycap(int fd, struct v4l2_capability* cap);



/*
 * 函数名称：v4l2_enuminput
 * 功能描述：枚举输入设备
 * 输入参数：fd         - v4l2设备的文件描述符
 * 输入参数：index - 输入设备的索引
 * 输出参数：name       - 返回输入设备的名称(此函数必须是一个buf)
 * 返 回 值：失败返回-1;成功返回0
 */
int v4l2_enuminput(int fd, int index, char* name);



/*
 * 函数名称：ScaneCameras
 * 功能描述：scane camera path
 * 输入参数：two eye camera and one field camera
 */
//void ScaneCameras(std::string &Path_CamL, std::string &Path_CamR, std::string &Path_Field);

/*
 * 函数名称：ScaneCameras
 * 功能描述：扫描所有可用摄像头
 * 输出结果：camCards为摄像头设备信息，camPaths为摄像头路径
 */
void ScanCameras(std::vector<std::string> &camCards, std::vector<std::string> &camPaths);


#endif