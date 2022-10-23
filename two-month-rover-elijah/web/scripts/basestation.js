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
    pico_sub.subscribe(updateGraph);

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
        console.log('LED on');
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
/*
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
*/


var temperature = [20];
var acceleration = [0];
var pressure = [990];
var altitude = [160];
var time = [0];
var time2 = [0];
var time3 = [0];
var time4 = [0];
var ovrltime = [0];
var ovrltimeacl = [0];
var alltemperature = [20];
var allacceleration = [0];
var allpressure = [990];
var allaltitude = [160];
var overalldata = []


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
        data: acceleration
      }]
    },
    options: {
        animation:{
            duration: 0
        },
        plugins: {
            legend: {
                display: true,
                title:{
                    text:"(M/S^2)*100",
                    display:true
                }
            }
        }
    }
  });

new Chart("tempChart", {
    type: "line",
    data: {
      labels: time2,
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
        animation:{
            duration: 0
        },
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
      labels: time3,
      datasets: [{
        label:"Pressure",
        fill: false,
        lineTension: 0,
        backgroundColor: "rgba(0,0,255,1.0)",
        borderColor: "rgba(0,0,255,0.1)",
        data: pressure
      }]
    },
    options: {
        animation:{
            duration: 0
        },
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
      labels: time4,
      datasets: [{
        label:"Altitude",
        fill: false,
        lineTension: 0,
        backgroundColor: "rgba(0,0,255,1.0)",
        borderColor: "rgba(0,0,255,0.1)",
        data: altitude
      }]
    },
    options: {
        animation:{
            duration: 0
        },
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
  
  function redoData(chart, label, data) {
    chart.data.labels = label;
    chart.data.datasets.forEach((dataset) => {
        dataset.data = data;
    });
    chart.update();
  }
  function addData(chart, data) {
    chart.data.datasets.forEach((dataset) => {
        dataset.data.push(data);
    });
    chart.update();
  }

  function chartAllData(chart, label, data) {
    chart.data.labels = label;
    chart.data.datasets.forEach((dataset) => {
        dataset.data = data;
    });
    chart.update();
  }

  function updateGraph(message){
    var thedata = message.data;
    if (thedata.startsWith("acel")){
        var aceldata = thedata.replace('acel','');
        aceldata = parseInt(aceldata);
        allacceleration.push(aceldata)
        var lastacceltimeint = time[time.length-1];
        lastacceltimeint = lastacceltimeint + 1;
        time.push(lastacceltimeint)
        ovrltimeacl.push(lastacceltimeint)
        var accelchart = Chart.getChart("accelerometerChart");
        addData(accelchart, aceldata);
    }
    if (thedata.startsWith("temp")){
        var tempdata = thedata.replace('temp','');
        tempdata = parseInt(tempdata);
        alltemperature.push(tempdata)
        var lasttemptimeint = time2[time2.length-1];
        lasttemptimeint = lasttemptimeint + 1;
        time2.push(lasttemptimeint)
        var tempchart = Chart.getChart("tempChart");
        addData(tempchart, tempdata);
    }
    if (thedata.startsWith("pres")){
        var presdata = thedata.replace('pres','');
        presdata = parseInt(presdata);
        allpressure.push(presdata)
        var lastpressuretimeint = time3[time3.length-1];
        lastpressuretimeint = lastpressuretimeint + 1;
        time3.push(lastpressuretimeint)
        var presschart = Chart.getChart("pressureChart");
        addData(presschart, presdata);
    }
    if (thedata.startsWith("alti")){
        var altidata = thedata.replace('alti','');
        altidata = parseInt(altidata);       
        allaltitude.push(altidata)
        var lastaltitimeint = time4[time4.length-1];
        lastaltitimeint = lastaltitimeint + 1;
        time4.push(lastaltitimeint)
        ovrltime.push(lastaltitimeint)
        var altichart = Chart.getChart("altitudeChart");
        addData(altichart, altidata);
    }

  }

$("#btn_graph").click(() => {
    time = [time[time.length-1]];
    time2 = [time2[time2.length-1]];
    time3 = [time3[time3.length-1]];
    time4 = [time4[time4.length-1]];
    acceleration = [acceleration[acceleration.length-1]];
    temperature = [temperature[temperature.length-1]];
    pressure = [pressure[pressure.length-1]];
    altitude = [altitude[altitude.length-1]];
    var accelchart = Chart.getChart("accelerometerChart");
    redoData(accelchart, time, acceleration);
    var tempchart = Chart.getChart("tempChart");
    redoData(tempchart, time2, temperature);
    var presschart = Chart.getChart("pressureChart");
    redoData(presschart, time3, pressure);
    var altichart = Chart.getChart("altitudeChart");
    redoData(altichart, time4, altitude);
});

function saveStaticDataToFile() {
    var blob = new Blob([overalldata],
        { type: "text/plain;charset=utf-8" });
    saveAs(blob, "data.txt");
}

function organizedata(acctime,gentime,acce,alti,pres,temp){
    var temporary = []
    for (let i = 0; i <= acctime.length; i++){
        temporary.push("Acceleration," + acctime[i].toString() + "," + acce[i].toString())
        overalldata.push(temporary)
        temporary = []
    }
    for (let i = 0; i <= gentime.length; i++){
        temporary.push("Altitude," + gentime[i].toString() + "," + alti[i].toString())
        overalldata.push(temporary)
        temporary = []
        temporary.push("Pressure," + gentime[i].toString() + "," + pres[i].toString())
        overalldata.push(temporary)
        temporary = []
        temporary.push("Temperature," + gentime[i].toString() + "," + temp[i].toString())
        overalldata.push(temporary)
        temporary = []
    }
}

$("#btn_graph_all").click(() => {
    console.log(ovrltimeacl)
    console.log(ovrltime)
    console.log(allacceleration)
    console.log(allaltitude)
    console.log(allpressure)
    console.log(alltemperature)
    organizedata(ovrltimeacl, ovrltime, allacceleration, allaltitude, allpressure, alltemperature)
    saveStaticDataToFile()

    var accelchart = Chart.getChart("accelerometerChart");
    chartAllData(accelchart, ovrltimeacl, allacceleration);
    var tempchart = Chart.getChart("tempChart");
    chartAllData(tempchart, ovrltime, alltemperature);
    var presschart = Chart.getChart("pressureChart");
    chartAllData(presschart, ovrltime, allpressure);
    var altichart = Chart.getChart("altitudeChart");
    chartAllData(altichart, ovrltime, allaltitude);
});


window.onload = setup;