#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

constexpr size_t size = 8;

int open_and_set_fid(size_t len, struct termios *old_options);

class modbus {
    public:
        modbus() {
            file = open_and_set_fid(size, &old_options);
        }

        ~modbus() {
            tcsetattr(file, TCSANOW, &old_options);
            close(file);
        };

        int send(uint8_t address, uint16_t reg, int16_t value);
        int16_t receive(uint8_t address, uint16_t reg);

    private:
        uint8_t send_buf[size];
        uint8_t receive_buf[size];
        struct termios old_options;
        int file;
}; 