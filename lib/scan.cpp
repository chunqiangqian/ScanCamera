#include "scan.h"

int v4l2_open(const char* name, int flag)
{
    int fd = open(name, flag);
    if(fd < 0)
    {
        printf("ERR(%s):failed to open %s\n", __func__, name);
        return -1;
    }

    return fd;
}


int v4l2_close(int fd)
{
    if(close(fd))
    {
        printf("ERR(%s):failed to close v4l2 dev\n", __func__);
        return -1;
    }

    return 0;
}

int v4l2_querycap(int fd, struct v4l2_capability* cap)
{
    if (ioctl(fd, VIDIOC_QUERYCAP, cap) < 0)
    {
        printf("ERR(%s):VIDIOC_QUERYCAP failed\n", __func__);
        return -1;
    }

    return 0;
}

int v4l2_enuminput(int fd, int index, char* name)
{
    struct v4l2_input input;
    int found = 0;

    input.index = 0;
    while(!ioctl(fd, VIDIOC_ENUMINPUT, &input))
    {
        //printf("input:%s\n", input.name);

        if(input.index == index)
        {
            found = 1;
            strcpy(name, (char*)input.name);
        }

        ++input.index;
    }

    if(!found)
    {
        //printf("%s:can't find input dev\n", __func__);
        return -1;
    }

    return 0;
}


int usb_camera_open(const char *dev, v4l2_buf** mV4l2Buf, std::string &card)
{
	int cameraFd = v4l2_open(dev, O_RDWR);
	if(cameraFd < 0)
	{
		printf("open %s failed\r\n", dev);
		return -1;
	}
    // get camera info
	struct v4l2_capability cap;
	int ret = v4l2_querycap(cameraFd, &cap);
    if(ret < 0)
    {
    	printf("set v4l2_querycap failed\r\n");
		return -1;
	}
    else
    {
        //std::cout << "card: " << cap.card << '\n';
        //std::cout << "driver: " << cap.driver << '\n';
        //std::cout << "bus info: " << cap.bus_info << '\n';
        //std::cout << "device cap: " << cap.device_caps << '\n';
        card = (char*)(cap.card);

    }

	if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
	{
		printf("capabilities failed\r\n");
		return -1;
	}
    
	char devName[100];
	ret = v4l2_enuminput(cameraFd, 0, devName);
    if(ret < 0)
    {
		//printf("v4l2_enuminput failed\r\n");
		return -1;
	}
    
	return cameraFd;

}

void Stringsplit(std::string str, char split, std::vector<std::string>& res)
{
	if (str == "")		return;
	//???????????????????????????????????????????????????????????????
	std::string strs = str + split;
	size_t pos = strs.find(split);
 
	// ???????????????????????????????????????????????? npos
	while (pos != strs.npos)
	{
		std::string temp = strs.substr(0, pos);
		res.push_back(temp);
		//???????????????????????????,????????????????????????????????????
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(split);
	}
}



void ScanCameras(std::vector<std::string> &camCards, std::vector<std::string> &camPaths)
{
    struct v4l2_buf* mV4l2Buf;
    std::string card;
    
    struct dirent *ent;
    char path_[] = "/dev";
    DIR *dir = opendir(path_);
    if (dir != NULL) {
        // ?????????/dev?????????????????????
        while ((ent = readdir(dir)) != NULL){
            // ????????????char?????????????????????5???
            char filename[5];
            strncpy(filename, ent->d_name, 5);
            // ??????????????????????????????????????????????????????/dev/video*
            if (strcmp(filename, "video") == 0) {
                //printf("%s\n", ent->d_name);
                std::string camPath;
                camPath.append("/dev/");
                camPath.append(ent->d_name);
                int cameraDevFd = usb_camera_open(camPath.c_str(), &mV4l2Buf, card);
                if (cameraDevFd > 0) {
                    // ???????????????????????????????????????????????????
                    if(strstr(card.c_str(), ":") != NULL){
                        std::vector<std::string> res;
                        char split = ':';
                        Stringsplit(card, split, res);
                        camCards.push_back(res[0]);
                    } else {
                        camCards.push_back(card);
                    }
                    camPaths.push_back(camPath);
                    // ???????????????
                    printf("%s\n", ent->d_name);
                    // ???????????????
                    std::cout << "card: " << card << '\n';
                    //std::cout << "cameraDevFd: " << cameraDevFd << '\n';
                }
                
            }
        }
        closedir(dir);
        
    } else{
        perror("opendir error");
    }

}