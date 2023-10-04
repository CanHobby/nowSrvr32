
// const MQTT     = 0  ;
const Table    = 3;
const BedSide  = 5;
const Fan      = 9;
const Coffee   = 7;

var Boxes = [
 ["Table",   [ Table,    0,  0 ] ],
 ["Sofa",    [ "Sofa",   0,  0 ] ],
// ["BedSide", [BedSide,   0,  0 ] ],
 ["Coffee",  ["Coffee", "ON",0 ],["Coffee", "OFF", 10] ],
 ["Fan",     [ Fan,     0,  0  ] ],

// [ "TV"  ,   ["Sofa","ON",0],  [Table,"OFF",2] ],
// [ "Work",   ["Sofa","OFF",0], [Table,"ON",0]  ],
// [ "Bed2",   [0x502,2,0 ] ],
// [ "Sofa1",  ["Sofa","OFF",1 ] ],
// [ "All OFF",["OFF", 255, 0  ] ],
            ] ;
