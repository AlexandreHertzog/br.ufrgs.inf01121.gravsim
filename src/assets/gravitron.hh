#include "point.hh"

namespace GravSim {
namespace Assets {
// TODO: move this somewhere else.
const int NUM_DIMENSIONS = 2;

/* 'Gravitron' defines the base class for a particle. There are plans to derive
 * it in the following classes:
 * A class that represents a planet
 * A class that represents an electrically charged element. */
class Gravitron : GravSim::Gui::Point {
public:
  // Constructors and destructor.
  Gravitron(
    // Physical components
    const double mass, const double *velocity, 
    // Render components
    const double *position, const size_t size = 0
  );
  ~Gravitron(void);

  // Access functions
  // Getters
  double GetMass(void);
  // There are no setters.
  
  /* This function will input a force in the particle. This force value won't
   * be stored, as it will be used only to calculate the new speed and position.
   * The input is a force vector. */
  void ApplyForce(const double *force);
  
  /* This function will perform a step in the simulation for the particle. That
   * is, add velocity to the position. */
  void StepPosition(void);

private:
  double _mass;
  double _velocity[NUM_DIMENSIONS];
}; // class Gravitron
}; // namespace GravSim
}; // namespace Assets
