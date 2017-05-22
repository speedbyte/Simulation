/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package simpleread;

/**
 *
 * @author mediamarkt
 */
public class Objects {

    public Objects() {


    }

    static byte id(byte ID){
    return ID;
    }

    static byte dlc(byte DLC){
    return DLC;
    }

    static byte request(byte Request){
    return Request;
    }

    static char CRC(char crc){
    return crc; }
   //_____________sensors_______________
    static char accXRaw(char accXRaw){
    return accXRaw;
    }

    static short accX(short accX){
    return accX;
    }

    static char accYRaw(char accYRaw){
    return accYRaw;
    }
    static short accY(short accY){
    return accY;
    }

     static char accZRaw(char accZRaw){
    return accZRaw;
    }
    static short accZ(short accZ){
    return accZ;
    }

    static short velZ(short velZ){
    return velZ;
    }
    static short posZ(short posZ){
    return posZ;
    }
    static char angVelRRaw(char angVelRRaw){
    return angVelRRaw;
    }

    static short angVelR(short angVelR){
    return angVelR;
    }
    static short angR(short angR){
    return angR;
    }
    static char angVelPRaw(char angVelPRaw){
    return angVelPRaw;
    }

    static short angVelP(short angVelP){
    return angVelP;
    }
    static short angP(short angP){
    return angP;
    }
    static char angVelYRaw(char angVelYRaw){
    return angVelYRaw;
    }

    static short angVelY(short angVelY){
    return angVelY;
    }
    static short angY(short angY){
    return angY;
    }

    static char tempRaw(char tempRaw){
    return tempRaw;
    }

    static int temp(byte temp){
    return BytesTransformation.UnsignedbyteToInt(temp);
    }

    static char airPressureRaw(char airPressureRaw){
    return airPressureRaw;
    }

    static int airPressure(byte airPressure){
    return BytesTransformation.UnsignedbyteToInt(airPressure);
    }
    static char batteryRaw(char batteryRaw){
    return batteryRaw;
    }

    static int battery(byte battery){
    return BytesTransformation.UnsignedbyteToInt(battery);
    }

    static char rpmFront(char rpmFront){
    return rpmFront;
    }
    static char rpmLeft(char rpmLeft){
    return rpmLeft;
    }
     static char rpmRear(char rpmRear){
    return rpmRear;
    }
    static char rpmRight(char rpmRight){
    return rpmRight;
    }

    static char forceTotal(char forceTotal){
    return forceTotal;
    }

    static int remoteForceRaw(byte remoteForceRaw){
    return BytesTransformation.UnsignedbyteToInt(remoteForceRaw);
    }
    static char remoteForce(char remoteForce){
    return remoteForce;
    }
    static int remoteYawRaw(byte remoteYawRaw){
    return BytesTransformation.UnsignedbyteToInt(remoteYawRaw);
    }

    static char remoteYaw(char remoteYaw){
    return remoteYaw;
    }

    static int remotePitchRaw(byte remotePitchRaw){
    return BytesTransformation.UnsignedbyteToInt(remotePitchRaw);
    }
    static char remotePitch(char remotePitch){
    return remotePitch;
    }
    static int remoteRollRaw(byte remoteRollRaw){
    return BytesTransformation.UnsignedbyteToInt(remoteRollRaw);
    }
    static char remoteRoll(char remoteRoll){
    return remoteRoll;
    }
    static int error(byte error){
    return BytesTransformation.UnsignedbyteToInt(error);
    }
    
    static char x_axis_p(char x_axis_p){
    return x_axis_p;
    }
    
    static char x_axis_i(char x_axis_i){
    return x_axis_i;
    }
    static char x_axis_d(char x_axis_d){
    return x_axis_d;
    }
    
    static char pitch_p(char pitch_p){
    return pitch_p;
    }
    
    static char pitch_i(char pitch_i){
    return pitch_i;
    }
    
    static char pitch_d(char pitch_d){
    return pitch_d;
    }
    static char yaw_p(char yaw_p){
    return yaw_p;
    }
    static char yaw_i(char yaw_i){
    return yaw_i;
    }
    
     static char yaw_d(char yaw_d){
    return yaw_d;
    }
    static char lpR(char lpR){
    return lpR;
    }
    static char hpR(char hpR){
    return hpR;
    }
    static char lpP(char lpP){
    return lpP;
    }
    static char hpP(char hpP){
    return hpP;
    }
    static char inertiaX(char inertiaX){
    return inertiaX;
    }
    static char inertiaY(char inertiaY){
    return inertiaY;
    }
     static char inertiaZ(char inertiaZ){
    return inertiaZ;
    }
      static char lenBoom(char lenBoom){
    return lenBoom;
    }
     
}
