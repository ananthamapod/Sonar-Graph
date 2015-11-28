/*********************************** IMPORTS ***********************************/
import processing.serial.*;

/*******************************************************************************/


/*********************************** GLOBALS ***********************************/
//reference to Serial object
Serial myPort;

//data points for graph, size is pixel width of screen (so each single pixel vertical column is a different interval)
int[] data = new int[800];
//stores the new data point
int newDataPoint = 0;

/*******************************************************************************/

/************************************ MAIN *************************************/

void setup() {
  size(800,400);
  // refresh rate of graph
  frameRate(100);
  // Assign appropriate serial port to variable
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  //smooth out lines and other graphics
  smooth();
}

void draw() {
  background(0);
  stroke(255,255,255);
  strokeWeight(2);
  // x-axis
  line(0,height,width,height);
  // y-axis
  line(0,0,0,height);
  
  
  // if new input, add the datapoint
  if(read()) {
    addNewData();
  }

  strokeWeight(2);
  
  // redraw the graph, each data point is another pixel along the x-axis
  for(int i = width-1; i > 0; i--) {
    stroke(255,0,0);
    line(i,(height - data[i-1]), i+1, (height - data[i]));
  }
  
}

/*******************************************************************************/


/*********************************** UTILITIES ***********************************/

/**
Read Serial input from the Arduino board
*/
boolean read() {
  
  // makes sure only good input is used
  boolean newInput = false;
  // input value from potentiometer
  String val;
  
  // if port is blocking, then don't attempt taking input
  if(myPort.available() > 0) {
    // read Serial input
    val = myPort.readStringUntil('\n');
    // Bad input corrections
    if(val != null) {
      val = val.trim();
      if(!val.equals("")) {
        // This is a good input, can be parsed
        newInput = true;
        newDataPoint = Integer.parseInt(val);
        println(newDataPoint);
      }
    }
  }
  
  return newInput;
}


/**
Shift data array and add new data point at the end
*/
void addNewData() {
    //shift the values in the data array, inverse dependence
    for(int i = 0; i < width-1; i++) {
      data[i] = data[i+1];
    }
    
    // add new data point
    data[width-1] = newDataPoint;
}

/*******************************************************************************/