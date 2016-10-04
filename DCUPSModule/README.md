# DC UPS Module

Most of the equipments in this project run on either 5v or 3.2v DC. Also most of the equipments needs to have power backup, security should be always awake!

The parts for this mini project are -
* LiPo Rechargeable 3.7v cell ([18650](http://www.ebay.in/itm/18650-Battery-3-7-volt-Rechargeable-Lithium-Cell-Li-ion-battery-3000-mAH-/252545729479?hash=item3acce603c7:g:HvYAAOSwYIxX3pJY) extracted from old laptop battery perfectly fits the bill)
* [18650 1S1P case](http://www.ebay.in/itm/3-7V-18650-Battery-Holder-Box-Case-Snap-with-6-Wire-Leads-1x18650-DIY-/272235819479?hash=item3f6284f1d7:g:c6EAAOSwYIhWkha-)
* [TP4056](http://amzn.to/2dq2WUe) micro USB battery charging module with over charge and over load protection
* [XL6009](http://amzn.to/2dq2WUe) DC-DC step up module, boost coverter

You will need some primary soldering technique, or if you want something ready made you can go for an expensive option from adafruit [ADA1904](http://www.ebay.in/itm/3-7V-18650-Battery-Holder-Box-Case-Snap-with-6-Wire-Leads-1x18650-DIY-/272235819479?hash=item3f6284f1d7:g:c6EAAOSwYIhWkha-)

If you have reached this page, I am guessing you want the DIY option rather than the one from adafruit, if so read on.
![Schematics](https://github.com/meetpraveen/HomeAutoSecure/blob/master/DCUPSModule/DC_UPS.png)

As the image shows, we need to connect the input to a 5v input source, I use an old phone charger for this (Most of the standard chargers have 5v output, if unsure read the specs). Cut out the micro usb leaving some 5cm of wire with the usb male connector. Solder the wire coming from the charger to TP4056 input. Conenct the battery + and - with the battery case or if you are running on a tight budget solder it directly to yhe cell.

Now we have a basic battery charging module along with a battery setup. For fun plug in the charger. You will see a red led glow which suggests battery is charging, after a few hours, when battery is fully charged, blue LED in TP4056 glows.

If you have a voltmeter handy check the output volt of TP4056 during the charge-recharge cycle of the battery. It will vary between 3.2v to 4.8v. This is not right for powering your controller devices like Raspberry Pi or Arduino or any of the sensors/relays. We need to condition the output. XL6009 comes to our rescue.

XL6009 is a boost type DC-DC convertor, with adjustable output voltage. It promises stable output and under testing I found that to be true with minor variation. Overall it fits the bill for our requirement. Solder the output of TP4056 to the input of XL6009 and adjust the output using the potentiometer (blue colored component with a screw on top). Clockwise rotation generally increases the voltage and anticlock will decrease. Adjust it carefully to a stable 5v output.

The final cog in the wheel is to conenct the USB male we saved earlier to the output of XL6009, this makes it ready to be connected to your Paspberry Pi. To connect to other boards, wither directly solder or buy/repurpose the connectors. The entire setup cost me 200 INR (< 3$), wow thats really economical.

![Final product](https://github.com/meetpraveen/HomeAutoSecure/blob/master/DCUPSModule/20160928_083656%20(1).jpg)
![Raspberry with UPS](https://github.com/meetpraveen/HomeAutoSecure/blob/master/DCUPSModule/20160928_083743%20(1).jpg)

