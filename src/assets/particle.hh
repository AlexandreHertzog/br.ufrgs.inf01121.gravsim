namespace GravSim {
namespace Assets {
const int NUM_DIMENSIONS = 2;

/* 'Particle' defines the base class for a particle. There are plans to derive
 * it in the following classes:
 * A class that represents a planet
 * A class that represents an electrically charged element. */
class Particle {
public:
  // Constructors and destructor.
  Particle(const double mass, const double *velocity, const double *position);
  Particle(void);
  ~Particle(void);

  // Access functions
  // Getters
  double GetMass(void);
  void   LoadVel(double *out);
  void   LoadPos(double *out);
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
  double _position[NUM_DIMENSIONS];
}; // class Particle
}; // namespace GravSim
}; // namespace Assets
