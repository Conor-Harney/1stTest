function play() {
    console.log("in play");
    var boom = new Audio("sounds/creaking-floor-1.mp3");
    boom.play();
	//due to licensing issues, firefox does not support mp3 in HTML5:
    boom = new Audio("sounds/win_sound.ogg");
    boom.play();

}
function playBackgroundLoop() {
    var b = new Audio("sounds/Last-Resort-8-bit-loopEdit.ogg");
    b.addEventListener('ended', function () {
        this.currentTime = 0;
        this.play();
    }, false);

    b.play()
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
var context;
window.addEventListener('load', init, false);
function init() {
  try {
    // Fix up for prefixing
    window.AudioContext = window.AudioContext||window.webkitAudioContext;
    context = new AudioContext();
  }
  catch(e) {
    alert('Web Audio API is not supported in this browser');
  }
  var completedSoundBuffer = null;
  var url = "http://localhost:8000/ConorHarneyGamesDevices/HTML/lab%206/Sounds/win_sound.ogg";
}



function completedSound(url) {
  var request = new XMLHttpRequest();
  request.open('GET', url, true);
  request.responseType = 'arraybuffer';

  // Decode asynchronously
  request.onload = function() {
    context.decodeAudioData(request.response, function(buffer) {
        completedSoundBuffer = buffer;
    }, onError);
  }
  request.send();
}

// Fix up prefixing

function playSound(buffer) {
  var source = context.createBufferSource(); // creates a sound source
  source.buffer = buffer;                    // tell the source which sound to play
  source.connect(context.destination);       // connect the source to the context's destination (the speakers)
  source.start(0);                           // play the source now
                                             // note: on older systems, may have to use deprecated noteOn(time);
}
*/