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
            Vector3 avgPos = Vector3.Empty;
            Vector3 avgFor = Vector3.Empty;

            foreach (MovingObject obj in Boids)
            {
                avgPos += obj.Position;
                avgFor += obj.Velocity;
            }

            AveragePosition = avgPos / Boids.Count;
            AverageForward = avgFor / Boids.Count;

            return;
        }

        private Vector3 CalculateAlignmentAcceleration(MovingObject boid)
        {
            Vector3 vec = AverageForward / boid.MaxSpeed;

            if (vec.Length > 1)
            {
                vec.Normalize();
            }

            return vec * AlignmentStrength;
        }

        private Vector3 CalculateCohesionAcceleration(MovingObject boid)
        {
            Vector3 vec = AveragePosition - boid.Position;
            float dis = vec.Length;
            
            vec.Normalize();

            if (dis < FlockRadius)
            {
                vec *= dis / FlockRadius;
            }
            
            return vec * CohesionStrength;
        }

        private Vector3 CalculateSeparationAcceleration(MovingObject boid)
        {
            Vector3 sum = Vector3.Empty;
           
            foreach (MovingObject otherBoid in Boids)
            {
                if (otherBoid == boid)
                {
                    continue;
                }
                
                Vector3 vec = boid.Position - otherBoid.Position;
                float dis = vec.Length;
                float safedis = boid.SafeRadius + otherBoid.SafeRadius;

                if (dis < safedis)
                {
                    vec.Normalize();
                    vec *= (safedis - dis) / safedis;
                    sum += vec;
                }
            }

            if (sum.Length > 1.0f)
            {
                sum.Normalize();
            }

            return sum * SeparationStrength;
        }

        #endregion

        #region TODO

        public virtual void Update(float deltaTime)
        {
            CalculateAverages();

            foreach (MovingObject obj in Boids)
            {
                Vector3 accel = CalculateAlignmentAcceleration(obj);
                accel += CalculateCohesionAcceleration(obj);
                accel += CalculateSeparationAcceleration(obj);
                float accelMult = obj.MaxSpeed;
                accel *= accelMult * deltaTime;

                obj.Velocity += accel;

                if (obj.Velocity.Length > obj.MaxSpeed)
                {
                    obj.Velocity.Normalize();
                    obj.Velocity *= obj.MaxSpeed;
                }

                obj.Update(deltaTime);
            }
            return;
        }
        #endregion
    }
}
