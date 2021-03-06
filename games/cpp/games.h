#ifndef __EVOLVE_FIELD__
#define __EVOLVE_FIELD__

#include "spatgame.h"
#include <sys/types.h>
#include <vector>

class NovakMayGame : public AbstractSpatialGame {
public:
  NovakMayGame(size_t size, double _b = 1.8) : AbstractSpatialGame(size, _b){};
  void calculate_scores(std::vector<double> &scores);
};

class MeanGame : public AbstractSpatialGame {
public:
  MeanGame(size_t size, double _b = 1.8) : AbstractSpatialGame(size, _b){};
  void calculate_scores(std::vector<double> &scores);
};

class NovakMayTriangularGame : public AbstractSpatialGame {
public:
  NovakMayTriangularGame(size_t size, double _b = 1.8)
      : AbstractSpatialGame(size, _b){};
  void calculate_scores(std::vector<double> &scores);
  void update_field(const std::vector<double> &scores, int time_moment,
                    int percfrom = -1, int perctill = -1);
};

class MeanTriangularGame : public AbstractSpatialGame {
public:
  MeanTriangularGame(size_t size, double _b = 1.8)
      : AbstractSpatialGame(size, _b){};
  void calculate_scores(std::vector<double> &scores);
  void update_field(const std::vector<double> &scores, int time_moment,
                    int percfrom = -1, int perctill = -1);
};

/*
 * Double field basic game
 *
 * Two field stored one after th other
 * Density for field 1 has indeces 2n
 * For field 2 indeces 2n+1
 */

class DoubleMeanFieldGame : public AbstractSpatialGame {
protected:
  double b1, b2;

public:
  DoubleMeanFieldGame(size_t size, double _b1 = 1.6, double _b2 = 1.6);

  virtual void calculate_scores(std::vector<double> &scores);
  virtual void update_field(const std::vector<double> &scores, int time_moment,
                            int percfrom = -1, int perctill = -1);
  void evolve(int num_steps = 0, int percfrom = -1, int perctill = -1);

  std::vector<double> get_bs();
  void set_b(double new_b1, double new_b2);
  void set_field(const std::vector<int> &new_field1,
                 const std::vector<int> &new_field2);
  std::vector<double> get_persistences();
};

#endif
