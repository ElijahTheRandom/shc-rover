// ROS Instance Object
var ros;

// ROS Subscriber
var pico_sub;

// ROS Publisher
var command_pub;

// Text box reference
var pico_log;

var movement_log;

function setup() {
    pico_log = $("#pico_log");
    movement_log = $("#movement_log");

    ros = new ROSLIB.Ros();
    var rosbridge_status = $("#rosbridge_status");
    ros.on('connection', function () {
        console.log('Connected to websocket server.');
        rosbridge_status.val("Connected");
    });

    ros.on('error', function (error) {
        console.log('Error connection to websocket server: ' + error);
        rosbridge_status.val("Error");
    });

    ros.on('close', function () {
        console.log('Connection to websocket server closed.');
        rosbridge_status.val("Closed");
    });

    pico_sub = new ROSLIB.Topic({
        ros: ros,
        name: '/pico/output',
        messageType: 'std_msgs/String'
    });
    pico_sub.subscribe(update_log);

    command_pub = new ROSLIB.Topic({
        ros: ros,
        name: '/pico/command', 
        messageType: 'std_msgs/String'
    }); 

    $("#rosbridge_connect").click(connect_rosbridge);

    // Command Publishing
    $("#btn_led_on").click(() => {
        var command = new ROSLIB.Message({
            data:"led_on"
        });
        command_pub.publish(command);
    });

    $("#btn_led_off").click(() => {
        var command = new ROSLIB.Message({
            data:"led_off"
        });
        command_pub.publish(command);
    });

    $("#btn_ping").click(() => {
        var command = new ROSLIB.Message({
            data:"ping"
        });
        command_pub.publish(command);
    });
    
    

    $("#btn_graph").click(() => {
        pico_log.text(thedata)
        var thedata = Serial.readStringUntil('\n');
        if (thedata.startsWith("acel")){
            thedata = thedata.replace('acel','');
            Acceleration.push(thedata);
        }
    });


    document.onkeydown = function(e) {
        var key_press = e.key;
        var command = new ROSLIB.Message({
            data:key_press
        });
        command_pub.publish(command); 
        movement_log.text(e.key);
      }
    document.onkeyup = function(e) {
        var command = new ROSLIB.Message({
            data:"Brake"
        });
        command_pub.publish(command);
        movement_log.text(e.key);
      }

}

 

function update_log(message) {
    var log = message.data;
    var time = new Date().toTimeString().split(' ')[0];
    pico_log.text('[' + time + '] ' + log + pico_log.text());
}

function connect_rosbridge() {
    var address = "ws://" + $("#rosbridge_address").val();

    ros.connect(address);
}

const video = document.getElementById("webcam")

async function getMedia() {
  let stream = null

  try {
    stream = await navigator.mediaDevices.getUserMedia({ 
        video: true 

    })
    video.srcObject = stream
  } catch (err) {
    console.log("error")
  }
}

getMedia()



var temperature = [70,69,70,70,69,70,71,70,69,71];
var Acceleration = []
var time = [1,2,3,4,5,6,7,8,9,10];


//ALL THE CHARTS

new Chart("accelerometerChart", {
    type: "line",
    data: {
      labels: time,
      datasets: [{
        label:"Accelerometer",
        fill: false,
        lineTension: 0,
        backgroundColor: "rgba(0,0,255,1.0)",
        borderColor: "rgba(0,0,255,0.1)",
        data: Acceleration
      }]
    },
    options: {
        plugins: {
            legend: {
                display: true,
                title:{
                    text:"M/S^2",
                    display:true
                }
            }
        }
    }
  });

new Chart("tempChart", {
    type: "line",
    data: {
      labels: time,
      datasets: [{
        label:"Temperature",
        fill: false,
        lineTension: 0,
        backgroundColor: "rgba(0,0,255,1.0)",
        borderColor: "rgba(0,0,255,0.1)",
        data: temperature
      }]
    },
    options: {
        plugins: {
            legend: {
                display: true,
                title:{
                    text:"Celcius",
                    display:true
                }
            }
        }
    }
  });

new Chart("pressureChart", {
    type: "line",
    data: {
      labels: time,
      datasets: [{
        label:"Pressure",
        fill: false,
        lineTension: 0,
        backgroundColor: "rgba(0,0,255,1.0)",
        borderColor: "rgba(0,0,255,0.1)",
        data: temperature
      }]
    },
    options: {
        plugins: {
            legend: {
                display: true,
                title:{
                    text:"hPa",
                    display:true
                }
            }
        }
    }
  });

  new Chart("altitudeChart", {
    type: "line",
    data: {
      labels: time,
      datasets: [{
        label:"Altitude",
        fill: false,
        lineTension: 0,
        backgroundColor: "rgba(0,0,255,1.0)",
        borderColor: "rgba(0,0,255,0.1)",
        data: temperature
      }]
    },
    options: {
        plugins: {
            legend: {
                display: true,
                title:{
                    text:"Meters",
                    display:true
                }
            }
        }
    }
  });
  
  function addData(chart, label, data) {
      chart.data.labels.push(label);
      chart.data.datasets.forEach((dataset) => {
          dataset.data.push(data);
      });
      chart.update();
  }
$("#btn_test").click(() => {
    var mychart = Chart.getChart("tempChart")
    addData(mychart, 11, 72)
});

window.onload = setup;