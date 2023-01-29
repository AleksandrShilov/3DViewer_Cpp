#include "model.h"

#include <cmath>

namespace my {

Singleton::Singleton() {
  data_model_.vertex_coordinates = {};
  data_model_.vertex_index = {};
  data_model_.normal_coordinates = {};
}

std::shared_ptr<Singleton> Singleton::Instance() {
  static auto inst = std::shared_ptr<Singleton>(new Singleton);
  return inst;
}

void Singleton::ParseV(std::string const &str) {
  if (str[0] == 'v' && str[1] == ' ') {
    std::string number;
    for (size_t i = 2; i < str.size(); ++i) {
      if (std::isdigit(str[i]) || str[i] == '.' || str[i] == '-') {
        number.push_back(str[i]);
      } else {
        data_model_.vertex_coordinates.push_back(std::stod(number));
        number = "";
      }
    }
    if (number != "") {
      data_model_.vertex_coordinates.push_back(std::stod(number));
      number = "";
    }
  }
}

void Singleton::ParseVN(std::string const &str) {
  if (str[0] == 'v' && str[1] == 'n' && str[2] == ' ') {
    std::string number;
    for (size_t i = 3; i < str.size(); ++i) {
      if (std::isdigit(str[i]) || str[i] == '.' || str[i] == '-') {
        number.push_back(str[i]);
      } else {
        data_model_.normal_coordinates.push_back(std::stod(number));
        number = "";
      }
    }
    if (number != "") {
      data_model_.normal_coordinates.push_back(std::stod(number));
      number = "";
    }
  }
}

void Singleton::WrittenF(std::string const &str) {
  if (str[0] == 'f' && str[1] == ' ') {
    bool flag_number = true;
    bool flag_first = true;
    int first_number;
    std::string number;
    for (size_t i = 2; i < str.size(); ++i) {
      if (std::isdigit(str[i]) && flag_number) {
        number.push_back(str[i]);
      } else if (str[i] == '/') {
        flag_number = false;
      } else if (str[i] == ' ') {
        if (flag_first) {
          first_number = std::stoi(number);
          data_model_.vertex_index.push_back(std::stoi(number));
          number = "";
          flag_first = false;
        } else {
          data_model_.vertex_index.push_back(std::stoi(number));
          data_model_.vertex_index.push_back(std::stoi(number));
          number = "";
        }
        flag_number = true;
      }
    }

    if (number != "") {
      data_model_.vertex_index.push_back(std::stoi(number));
      data_model_.vertex_index.push_back(std::stoi(number));
      if (!flag_first) {
        data_model_.vertex_index.push_back(first_number);
        number = "";
      }
    }
  }
}

void Singleton::ReadFile(std::ifstream &file) {
  std::string str;
  data_model_.vertex_coordinates.push_back(0);
  data_model_.vertex_coordinates.push_back(0);
  data_model_.vertex_coordinates.push_back(0);
  while (getline(file, str)) {
    ParseV(str);
    ParseVN(str);
    WrittenF(str);
  }
}

bool Singleton::OpenFile(const std::string &path) {
  std::ifstream file(path, std::ios::in);
  if (file.is_open()) {
    ReadFile(file);
    file.close();
  } else {
    return false;
  }
  return true;
}

data Singleton::GetStruct() { return data_model_; }

void Singleton::MoveObject(std::vector<double> &coordinates, size_t elem,
                           double const &value) {
  for (size_t i = elem; i < coordinates.size(); i += 3) {
    coordinates[i] += value;
  }
}

void Singleton::ChangeScale(std::vector<double> &coordinates,
                            double const &value) {
  for (size_t i = 0; i < coordinates.size(); ++i) {
    coordinates[i] *= value;
  }
}

void Singleton::RotateAxisX(std::vector<double> &coordinates,
                            double const &value) {
  for (size_t i = 3; i < coordinates.size(); i += 3) {
    double y = coordinates[i + 1];
    double z = coordinates[i + 2];
    coordinates[i + 1] = cos(value) * y - sin(value) * z;
    coordinates[i + 2] = sin(value) * y + cos(value) * z;
  }
}

void Singleton::RotateAxisY(std::vector<double> &coordinates,
                            double const &value) {
  for (size_t i = 3; i < coordinates.size(); i += 3) {
    double x = coordinates[i];
    double z = coordinates[i + 2];
    coordinates[i] = cos(value) * x + sin(value) * z;
    coordinates[i + 2] = -sin(value) * x + cos(value) * z;
  }
}

void Singleton::RotateAxisZ(std::vector<double> &coordinates,
                            double const &value) {
  for (size_t i = 3; i < coordinates.size(); i += 3) {
    double x = coordinates[i];
    double y = coordinates[i + 1];
    coordinates[i] = cos(value) * x - sin(value) * y;
    coordinates[i + 1] = sin(value) * x + cos(value) * y;
  }
}

void Singleton::ClearStruct() {
  data_model_.vertex_coordinates.clear();
  data_model_.vertex_index.clear();
  data_model_.normal_coordinates.clear();
}

}  // namespace my
