#include "GPIOMgr.h"
#include <filesystem>
#include <regex>
#include <fcntl.h>
#include <sys/epoll.h>
#include <unistd.h>

GPIOMgr *GPIOMgr::gInstance(NULL);


// ****************************************************************************
//
// ****************************************************************************
GPIOMgr *GPIOMgr::create_instance()
{
//  std::cout << "LogMgr::create_instance - start" << std::endl;

  if(NULL == gInstance)
  {
    gInstance = new GPIOMgr();
    return gInstance;
  }

  std::cout << "GPIOMgr::create_instance - error - instance already created" << std::endl;
  return NULL;
}

// ****************************************************************************
//
// ****************************************************************************
GPIOMgr *GPIOMgr::get_instance()
{ 
//  std::cout << "LogMgr::get_instance - start" << std::endl;
//  std::cout << "LogMgr::get_instance - finished" << std::endl;
  // Return static instance. Note, if instance is not yet created this will
  // return NULL.
  return gInstance;
}

// ****************************************************************************
//
// ****************************************************************************
GPIOMgr::GPIOMgr()
{
  auto e = std::regex( SYSFS_GPIO_DIR "/gpio\\d+" );

  for (const auto & entry : std::filesystem::directory_iterator(SYSFS_GPIO_DIR)) 
  {
	  if (std::regex_match (entry.path().u8string(), e)) 
    {
		  auto filename = entry.path().filename().u8string();
	    auto pin = filename.erase(0, 4 /* gpio */);
		  int pinID = std::stoi(pin, nullptr, 0);
		    mExportedPins.push_back(pinID);
	  }
  }
}

// ****************************************************************************
//
// ****************************************************************************
GPIOMgr::~GPIOMgr() 
{ 
  clean(); 
}

// ****************************************************************************
//
// ****************************************************************************
// export pin (equivalent to i.e echo "68" > /sys/class/gpio/export)
int GPIOMgr::exportPin(unsigned int gpio) {
    auto ret = writeToSysfs<unsigned int>(SYSFS_GPIO_DIR "/export", gpio);

    if (ret == 0)
        mExportedPins.push_back(gpio);

    return ret;
}

// ****************************************************************************
//
// ****************************************************************************
// unexport pin (equivalent to i.e echo "68" > /sys/class/gpio/unexport)
int GPIOMgr::unexportPin(unsigned int gpio) {
    auto ret = writeToSysfs<unsigned int>(SYSFS_GPIO_DIR "/unexport", gpio);

    if (ret == 0) {
        mExportedPins.erase(
            std::remove(mExportedPins.begin(), mExportedPins.end(), gpio),
            mExportedPins.end());
    }

    return ret;
}

// ****************************************************************************
//
// ****************************************************************************
// set direction (equivalent to i.e echo "in" > /sys/class/gpio68/direction)
int GPIOMgr::setDirection(unsigned int gpio, DIRECTION direction) const {
    return writeToSysfs<const char*>(gpio, "/direction", direction == OUTPUT ? "out" : "in");
}

// ****************************************************************************
//
// ****************************************************************************
// get direction (equivalent to i.e cat /sys/class/gpio68/direction)
int GPIOMgr::getDirection(unsigned int gpio) const {
    char direction;

    auto ret = readFromSysfs<char*>(gpio, "/direction", &direction);
    if (ret == 0)
        return (direction == 'i') ? INPUT : OUTPUT;

    return ret;
}

// ****************************************************************************
//
// ****************************************************************************
// set value (equivalent to i.e echo "1" > /sys/class/gpio68/value)
int GPIOMgr::setValue(unsigned int gpio, PIN_VALUE value) const {
    return writeToSysfs<PIN_VALUE>(gpio, "/value", value);
}

// ****************************************************************************
//
// ****************************************************************************
// get value (equivalent to i.e cat /sys/class/gpio68/value)
int GPIOMgr::getValue(unsigned int gpio) const {
    char value;

    auto ret = readFromSysfs<char*>(gpio, "/value", &value);
    if (ret == 0) {
        return (value == '1') ? HIGH : LOW;
    }

    return ret;
}

// ****************************************************************************
//
// ****************************************************************************
// set edge (equivalent to i.e echo "rising" > /sys/class/gpio68/edge)
int GPIOMgr::setEdge(unsigned int gpio, EDGE_VALUE value) const {
    return writeToSysfs<EDGE_VALUE>(gpio, "/edge", value);
}

// ****************************************************************************
//
// ****************************************************************************
// get edge (equivalent to i.e cat /sys/class/gpio68/edge)
int GPIOMgr::getEdge(unsigned int gpio) const {
    char value[7];

    auto ret = readFromSysfs<char*>(gpio, "/edge", &value[0]);
    if (ret == 0) {
        return getEdgeIndex(value).value_or(-1);
    }

    return ret;
}

// ****************************************************************************
//
// ****************************************************************************
// wait for edge event
int GPIOMgr::waitForEdge(unsigned int gpio) const {
    char path[50], buf;
    int efd, fd;
    struct epoll_event events, ev;

    snprintf(path, sizeof(path), SYSFS_GPIO_DIR "/gpio%u/value", gpio);

    // Get value file descriptor
    fd = open(path, O_RDONLY | O_NONBLOCK);

    // Create epoll instance
    efd = epoll_create(1);

    // Fill the event structure and register
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLET | EPOLLPRI;

    epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ev);

    // Ignore the first read (initial value)
    for (int i = 0; i < 2; i++) {
        if ((epoll_wait(efd, &events, 1, -1)) == -1) {
            return -1;
        }
    }

    lseek(events.data.fd, 0, SEEK_SET);
    if (read(events.data.fd, &buf, sizeof(buf)) != 1) {
        return -1;
    }

    close(efd);
    close(fd);

    return (buf & 1);
}

// ****************************************************************************
//
// ****************************************************************************
std::vector<pins_t> GPIOMgr::getExportedPins() const {
    std::vector<pins_t> out;

    for (auto pinID: mExportedPins) {
        auto pin = getPin(pinID);

        if (pin) {
            out.push_back(pin.value());
        }
    }

    return out;
}

// ****************************************************************************
//
// ****************************************************************************
void GPIOMgr::clean() {
    for (int i = 0; i < static_cast<int>(mExportedPins.size()); i++) {
        auto pin = getPin(mExportedPins[i]);
        
        // avoid unexporting pins allocated by default
        if (pin && !pin.value().is_allocated_by_default) {
            unexportPin(pin.value().gpio);
        }
    }
}