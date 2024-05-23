setInterval(function ( ) {
    var xhttp = new XMLHttpRequest(); 
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) { //wait for response 
        document.getElementById("temperature").innerHTML = this.responseText; //change temp to response value

      }
    };
    xhttp.open("GET", "/temp", true); //get request for temperature
    console.log("refresh")
    xhttp.send();
  }, 5000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function(){
  const d = new Date;
  const hours = d.getHours();
  const minutes = d.getMinutes();
  const seconds = d.getSeconds();
  
  //add leading 0 if less than 2 numbers eg, 03
  let formattedHours = String(hours).padStart(2, '0'); 
  let formattedMinutes = String(minutes).padStart(2, '0');
  let formattedSeconds = String(seconds).padStart(2, '0');

  const time = (formattedHours + ':' + formattedMinutes + ':' + formattedSeconds)
  document.getElementById("currentDate").innerHTML = time
  
}, 1000)
 

