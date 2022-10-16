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
    
    $("#btn_time").click(() => {
        var command = new ROSLIB.Message({
            data:"time"
        });
        command_pub.publish(command);
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
        var key_press = e.key;
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

/* navigator.mediaDevices.enumerateDevices()
.then((devices) => {
  devices.forEach((device) => {
    console.log(`${device.kind}: ${device.label} id = ${device.deviceId}`);
  });
})
.catch((err) => {
  console.error(`${err.name}: ${err.message}`);
});
 */
getMedia()

window.onload = setup;