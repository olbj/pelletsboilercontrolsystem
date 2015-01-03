<map version="1.0.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1390035169047" ID="ID_747987858" MODIFIED="1390044653683" TEXT="Arduino project">
<node CREATED="1390035181916" ID="ID_296693084" MODIFIED="1390035186049" POSITION="right" TEXT="Tasks">
<node CREATED="1390035186589" ID="ID_349484376" MODIFIED="1390035200649" TEXT="Temp measurement"/>
<node CREATED="1390035200915" ID="ID_1402684901" MODIFIED="1390035224143" TEXT="Temp logging"/>
<node CREATED="1390035225355" ID="ID_934570927" MODIFIED="1390035234616" TEXT="PID-regulator"/>
<node CREATED="1390035235354" ID="ID_1272502488" MODIFIED="1390035246915" TEXT="Web-interface"/>
<node CREATED="1390035249039" ID="ID_1482586925" MODIFIED="1390035268555" TEXT="Time setting"/>
<node CREATED="1390035260663" ID="ID_167475488" MODIFIED="1390035264451" TEXT="Internet interface"/>
<node CREATED="1390035390617" ID="ID_505021949" MODIFIED="1390035396252" TEXT="Display presentation"/>
</node>
<node CREATED="1390035275143" ID="ID_1660016715" MODIFIED="1390035640901" POSITION="left" TEXT="Temp measurement">
<node CREATED="1390035645122" ID="ID_815223104" MODIFIED="1390035647581" TEXT="Links">
<node CREATED="1390035649576" ID="ID_1399523906" LINK="http://playground.arduino.cc/Learning/OneWire" MODIFIED="1390035674569" TEXT="http://playground.arduino.cc/Learning/OneWire"/>
<node CREATED="1390035695031" ID="ID_1104709405" LINK="http://www.pjrc.com/teensy/td_libs_OneWire.html" MODIFIED="1390035705478" TEXT="http://www.pjrc.com/teensy/td_libs_OneWire.html"/>
</node>
<node CREATED="1390035283446" ID="ID_1736015941" MODIFIED="1390035285579" TEXT="Device">
<node CREATED="1390035285926" ID="ID_782733336" MODIFIED="1390035345715" TEXT="DS18B20">
<node CREATED="1390331221432" MODIFIED="1390331221432" TEXT="Device 0 Address: 2812A64605000058"/>
<node CREATED="1390331221434" MODIFIED="1390331221434" TEXT="Device 1 Address: 28BD207A0500002D"/>
<node CREATED="1390331221435" MODIFIED="1390331221435" TEXT="Device 2 Address: 2817C1470500007C"/>
<node CREATED="1390331221436" MODIFIED="1390331221436" TEXT="Device 3 Address: 28EFEA46050000A8"/>
</node>
</node>
<node CREATED="1390035487693" ID="ID_1292286210" MODIFIED="1390035492473" TEXT="Sketche source"/>
</node>
<node CREATED="1390037678126" ID="ID_1324057921" MODIFIED="1390037681657" POSITION="left" TEXT="PID-regulator">
<node CREATED="1390037684069" ID="ID_571064639" MODIFIED="1390037686569" TEXT="Links">
<node CREATED="1390037948587" ID="ID_923006377" LINK="http://playground.arduino.cc/Code/PIDLibrary" MODIFIED="1390037952795" TEXT="http://playground.arduino.cc/Code/PIDLibrary"/>
<node CREATED="1390038597577" ID="ID_1436246937" LINK="http://playground.arduino.cc//Code/PIDAutotuneLibrary" MODIFIED="1390038606696" TEXT="Autotune"/>
<node CREATED="1390038625664" ID="ID_1932324649" LINK="http://arduino-pid-library.googlecode.com/files/PID_FrontEnd_v03.zip" MODIFIED="1390038645773" TEXT="Frontend"/>
<node CREATED="1390039808319" ID="ID_411073295" LINK="http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/" MODIFIED="1390039813251" TEXT="http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/"/>
<node CREATED="1390038785339" ID="ID_1828523465" MODIFIED="1390038791504" TEXT="Examples">
<node CREATED="1390038793450" ID="ID_1453347523" LINK="http://fermentationriot.com/arduinopid.php" MODIFIED="1390038798723" TEXT="http://fermentationriot.com/arduinopid.php"/>
<node CREATED="1390039413617" ID="ID_448697548" LINK="http://learn.adafruit.com/sous-vide-powered-by-arduino-the-sous-viduino/pid" MODIFIED="1390039419091" TEXT="http://learn.adafruit.com/sous-vide-powered-by-arduino-the-sous-viduino/pid"/>
<node CREATED="1390045204333" ID="ID_610813089" LINK="http://www.barnesian.com/arduino-powered-smart-fan-controller/" MODIFIED="1390045392697" TEXT="Fan"/>
<node CREATED="1390045354350" ID="ID_1223805154" LINK="http://www.instructables.com/id/Cheap-Arduino-Controled-Yogurt-Maker/step2/Programing-the-Arduino/" MODIFIED="1390045383304" TEXT="Yoghurt maker"/>
</node>
</node>
<node CREATED="1390046341477" ID="ID_404695289" MODIFIED="1390046344458" TEXT="Calculation">
<node CREATED="1390046345148" ID="ID_512789369" MODIFIED="1390046351066" TEXT="y=kx+m">
<node CREATED="1390046359011" ID="ID_1522920496" MODIFIED="1390046375015" TEXT="ymax=kx,max+m"/>
<node CREATED="1390046375403" ID="ID_705718671" MODIFIED="1390046384351" TEXT="ymin=kxmin+m">
<node CREATED="1390046388706" ID="ID_715709370" MODIFIED="1390046400351" TEXT="ymax-ymin=kxmax-kxmin">
<node CREATED="1390046400761" ID="ID_818909504" MODIFIED="1390046420695" TEXT="k=(ymax-ymin)/(xmax-xmin)"/>
</node>
</node>
</node>
</node>
</node>
<node CREATED="1390044654042" ID="ID_885024775" MODIFIED="1390044656473" POSITION="right" TEXT="Variables">
<node CREATED="1390044657150" ID="ID_1115176455" MODIFIED="1390044669595" TEXT="Temp devices">
<node CREATED="1390044669949" ID="ID_1637356456" MODIFIED="1390044799718" TEXT="radiatorinThermometer"/>
<node CREATED="1390044669949" ID="ID_272686838" MODIFIED="1390044805518" TEXT="radiatoroutThermometer"/>
<node CREATED="1390044669949" ID="ID_1334946786" MODIFIED="1390044816181" TEXT="tapwaterThermometer"/>
<node CREATED="1390044669949" ID="ID_1648478060" MODIFIED="1390044832453" TEXT="outsideThermometer"/>
</node>
<node CREATED="1390045491880" ID="ID_544155531" MODIFIED="1390045495526" TEXT="Temp curve">
<node CREATED="1390045496551" ID="ID_587559503" MODIFIED="1390047418300" TEXT="TempRadOutMax"/>
<node CREATED="1390045505431" ID="ID_704433977" MODIFIED="1390047382806" TEXT="TempRadOutMin"/>
<node CREATED="1390047185866" ID="ID_1976492101" MODIFIED="1390047457556" TEXT="TempOutsideMin"/>
<node CREATED="1390045512807" ID="ID_74663453" MODIFIED="1390047174367" TEXT="kCurve"/>
<node CREATED="1390045672821" ID="ID_802829709" MODIFIED="1390047181681" TEXT="mCurve"/>
</node>
<node CREATED="1390047484900" ID="ID_1765037681" MODIFIED="1390047488635" TEXT="Temperatures">
<node CREATED="1390047489059" ID="ID_1145351746" MODIFIED="1390047493209" TEXT="TempOutside">
<node CREATED="1390047580649" ID="ID_255554244" MODIFIED="1390047582957" TEXT="Measured"/>
</node>
<node CREATED="1390047494236" ID="ID_1577510213" MODIFIED="1390047498152" TEXT="TempRadIn">
<node CREATED="1390047590264" ID="ID_1867508955" MODIFIED="1390047596652" TEXT="Measured"/>
</node>
<node CREATED="1390047499010" ID="ID_891242730" MODIFIED="1390047502648" TEXT="TempRadOut">
<node CREATED="1390047597800" ID="ID_1001030131" MODIFIED="1390047603452" TEXT="Measured"/>
</node>
<node CREATED="1390047567825" ID="ID_208505710" MODIFIED="1390047571158" TEXT="TempRadOutSet">
<node CREATED="1390047571665" ID="ID_335057761" MODIFIED="1390047578597" TEXT="Setpoint. Derived"/>
</node>
<node CREATED="1390047502948" ID="ID_1700096717" MODIFIED="1390047649083" TEXT="TempTapwaterOut">
<node CREATED="1390047609695" ID="ID_248924598" MODIFIED="1390047614100" TEXT="Measured"/>
</node>
</node>
</node>
<node CREATED="1390330749012" ID="ID_1764106238" MODIFIED="1390330751731" POSITION="right" TEXT="Board">
<node CREATED="1390330752306" ID="ID_1078146124" MODIFIED="1390330777654" TEXT="Arduino MEGA 2560 Rev3"/>
</node>
</node>
</map>
