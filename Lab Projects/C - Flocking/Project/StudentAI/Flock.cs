using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FullSailAFI.SteeringBehaviors.Core;

namespace FullSailAFI.SteeringBehaviors.StudentAI
{
    public class Flock
    {
        public float AlignmentStrength { get; set; }
        public float CohesionStrength { get; set; }
        public float SeparationStrength { get; set; }
        public List<MovingObject> Boids { get; protected set; }
        public Vector3 AveragePosition { get; set; }
        protected Vector3 AverageForward { get; set; }
        public float FlockRadius { get; set; }

        #region Constructors
        public Flock()
        {
        }
        #endregion

        #region TODO Suggested helper methods

        private void CalculateAverages()
        {
            return;
        }

        private Vector3 CalculateAlignmentAcceleration(MovingObject boid)
        {
            return Vector3.Empty;
        }

        private Vector3 CalculateCohesionAcceleration(MovingObject boid)
        {
            return Vector3.Empty;
        }

        private Vector3 CalculateSeparationAcceleration(MovingObject boid)
        {
            return Vector3.Empty;
        }

        #endregion

        #region TODO

        public virtual void Update(float deltaTime)
        {
            return;
        }
        #endregion
    }
}
