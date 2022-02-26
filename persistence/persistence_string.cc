#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

static const mode_t kFileMode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

class PersistentString {
 public:
  void Init();
  void EnCoding(std::string str);
  int DeCoding(std::string *data);

  PersistentString(std::string path) : data_path_(path) {}

  ~PersistentString() {}

 private:
  int64_t persistent_fd_;
  std::string data_path_;
};

void PersistentString::Init() {
  int64_t fd = open(data_path_.c_str(), O_RDWR | O_CREAT, kFileMode);
  if (fd < 0) {
    std::cout << "Init failed" << std::endl;
    return;
  }

  persistent_fd_ = fd;
}

void PersistentString::EnCoding(std::string str) {
  int n_size = str.size();
  if (n_size == 0) {
    return;
  }

  if (pwrite(persistent_fd_, str.c_str(), n_size, 0) < n_size) {
    std::cout << "EnCoding failed \n " << std::endl;
  }

  fsync(persistent_fd_);
}

int PersistentString::DeCoding(std::string *data) {
  char buf[4096];
  int n = pread(persistent_fd_, buf, sizeof(buf), 0);
  if (n <= 0) {
    std::cout << "DeCoding failed \n" << std::endl;
    return -1;
  }

  *data = std::string(buf);
  return 0;
}

int main() {
  PersistentString p_string("./p_string");

  p_string.Init();
  p_string.EnCoding("test_string");

  std::string decode_str;
  if (p_string.DeCoding(&decode_str) < 0) {
    std::cout << "Decode null string" << std::endl;
  } else {
    std::cout << "Decode succcess with : " << decode_str << std::endl;
  }
  return 0;
}
