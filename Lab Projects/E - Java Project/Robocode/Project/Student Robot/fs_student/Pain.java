package fs_student;

import robocode.*;
import robocode.util.Utils;

import java.awt.*;


public class Pain extends TeamRobot {

        private byte moveDirection = 1;
        private double lastEnergy = Double.POSITIVE_INFINITY;

        private int wallMargin = 60;

        public void run() {

                setBodyColor(Color.black);
                setGunColor(Color.black);
                setRadarColor(Color.black);
                setBulletColor(Color.white);
                setScanColor(Color.black);


                while (true) {

                        setAhead(150 * moveDirection);

                        if (getRadarTurnRemaining() == 0) {
                                turnRadarRightRadians(Double.POSITIVE_INFINITY);
                        }

                        if (getVelocity() == 0) {
                                moveDirection *= -1;
                        }

                        execute();
                }
        }


        public void onScannedRobot(ScannedRobotEvent e) {

                double enemyAngle = getHeadingRadians() + e.getBearingRadians();
                double turnRadar = Utils.normalRelativeAngle(enemyAngle - getRadarHeadingRadians());
                double turnExtra = Math.min(Math.atan(36.0 / e.getDistance()), Rules.RADAR_TURN_RATE_RADIANS);

                turnRadar += (turnRadar < 0 ? -turnExtra : turnExtra);
                if (turnRadar < 0) {
                        turnRadar -= turnExtra;
                } else {
                        turnRadar += turnExtra;
                }

                double turnGun = getHeadingRadians() + e.getBearingRadians() - getGunHeadingRadians();

                setTurnGunRightRadians(Utils.normalRelativeAngle(turnGun));
                setTurnRadarRightRadians(turnRadar);


                if (e.getDistance() < 150) {
                        setTurnRight(normalizeBearing(e.getBearing() + 90 + (15 * moveDirection)));
                } else {
                        setTurnRight(normalizeBearing(e.getBearing() + 90 - (15 * moveDirection)));
                }

                double currentEnergy = e.getEnergy();

                // assume it fires
                if (currentEnergy < lastEnergy) {

                        moveDirection *= -1;
                        lastEnergy = currentEnergy;
                        setAhead(150 * moveDirection);
                }

                if (getTime() % 50 == 0 && getEnergy() > 5) {
                        fire(1);
                }

                if (e.getDistance() < 50 && e.getDistance() > 5) {
                        fire(1);
                }

                if (e.getEnergy() == 0) {
                        fire(3);
                }

        }

        public void onHitRobot(HitRobotEvent e) {
                setTurnRight(e.getBearing() + 90);
                setAhead(1000);
                fire(3);
        }

        public void onHitWall(HitWallEvent e){
                setTurnRight(e.getBearing() + 90);
                setAhead(1000);
        }
        public void onHitByBullet(HitByBulletEvent e) {
                lastEnergy += 3 * e.getBullet().getPower();
        }

        double normalizeBearing(double angle) {
                while (angle > 180) angle -= 360;
                while (angle < -180) angle += 360;
                return angle;
        }
}