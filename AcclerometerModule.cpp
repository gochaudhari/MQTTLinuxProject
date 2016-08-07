/*
 * AcclerometerModule.cpp
 *
 *  Created on: Aug 7, 2016
 *      Author: gochaudhari
 */


#include "AcclerometerModule.hpp"



upm::MMA7660 *accel = new upm::MMA7660(MMA7660_I2C_BUS,
24
                                         MMA7660_DEFAULT_I2C_ADDR);
25

26
  // place device in standby mode so we can write registers
27
  accel->setModeStandby();
28

29
  // enable 64 samples per second
30
  accel->setSampleRate(upm::MMA7660::AUTOSLEEP_64);
31

32
  // place device into active mode
33
  accel->setModeActive();
34

35
  while (shouldRun)
36
    {
37
      int x, y, z;
38

39
      accel->getRawValues(&x, &y, &z);
40
      cout << "Raw values: x = " << x
41
           << " y = " << y
42
           << " z = " << z
43
           << endl;
44

45
      float ax, ay, az;
46

47
      accel->getAcceleration(&ax, &ay, &az);
48
      cout << "Acceleration: x = " << ax
49
           << "g y = " << ay
50
           << "g z = " << az
51
           << "g" << endl;
52

53
      usleep(500000);
54
    }
55

56
//! [Interesting]
57

58
  cout << "Exiting..." << endl;
59

60
  delete accel;
61
  return 0;


