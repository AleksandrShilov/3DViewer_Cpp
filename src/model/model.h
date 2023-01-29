#ifndef CPP4_3DVIEWER_V2_0_0_SRC_MODEL_MODEL_H_
#define CPP4_3DVIEWER_V2_0_0_SRC_MODEL_MODEL_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

namespace my {

struct data {
  std::vector<double> vertex_coordinates;
  std::vector<unsigned int> vertex_index;
  std::vector<double> normal_coordinates;
};

class Singleton {
 public:
  ~Singleton() = default;
  static std::shared_ptr<Singleton> Instance();
  bool OpenFile(std::string const &path);
  data GetStruct();
  void MoveObject(std::vector<double> &coordinates, size_t elem,
                  double const &value);
  void ChangeScale(std::vector<double> &coordinates, double const &value);
  void RotateAxisX(std::vector<double> &coordinates, double const &value);
  void RotateAxisY(std::vector<double> &coordinates, double const &value);
  void RotateAxisZ(std::vector<double> &coordinates, double const &value);
  void ClearStruct();

 protected:
  Singleton();
  Singleton(const Singleton &other) = delete;
  Singleton &operator=(const Singleton &other) = delete;
  Singleton(Singleton &&other) = delete;
  Singleton &operator=(Singleton &&other) = delete;
  void ParseV(std::string const &str);
  void ParseVN(std::string const &str);
  void ParseF(std::string const &str);
  void WrittenF(std::string const &str);
  void ReadFile(std::ifstream &file);

 private:
  static std::shared_ptr<Singleton> instance_;
  data data_model_;
};

}  // namespace my

#endif  //  CPP4_3DVIEWER_V2_0_0_SRC_MODEL_MODEL_H_
