   
//#region BINDING
  var score = {
    "score" : {
      "home" :  42,
      "away" : 100
    },
  };
  
  bind(score, document.querySelector("#scoreboard"));

  var bar = 100;

//#endregion BINDINGs

function format(time) {   
    var hrs = ~~(time / 3600);
    var mins = ~~((time % 3600) / 60);
    var secs = ~~time % 60;

  var ret = "";
    if (hrs > 0) {
        ret += "" + hrs + ":" + (mins < 10 ? "0" : "");
    }
    ret += "" + mins + ":" + (secs < 10 ? "0" : "");
    ret += "" + secs;
    return ret;
};

//#region WEARDOWNBAR
function tickBar(){
    setInterval(()=>{
        let progress = document.querySelector('#weardown-bar');
        let updatesPerSecond = 1000 / 30;

        var height = document.getElementById('weardown-bar').offsetHeight;
        var parentHeight = document.getElementById('weardown-bar').offsetParent.height;
        var percent = Math.ceil(100*height/parentHeight);
      
        function animator () { 
            if(percent !== bar){
                 $(progress).css('width', bar +'%');
            }
        }
      
        setTimeout(() => {
          animator();
        }, updatesPerSecond);

    }, 1000);
};

tickBar();
//#endregion

//#region UI CONTROLS 

    var homeScoreboard = document.getElementById('home-score');
    var awayScoreboard = document.getElementById('away-score');

    function onRestart() {
        triggerUE4EventBlank('restartEvent');
    }

//#endregion UI CONTROLS

//#region UE4 EVENTS
    function updateScore(home, away){
        
        if(home !== game.score.home){
            homeScoreboard.classList.remove('heartbeat');
            void homeScoreboard.offsetWidth;
            homeScoreboard.classList.add('heartbeat');
        }
        else if(away !== game.score.away){
            awayScoreboard.classList.remove('heartbeat');
            void awayScoreboard.offsetWidth;
            awayScoreboard.classList.add('heartbeat');
        }
        
        let newScore = {
          "score" : {
            "home" : home,
            "away" : away
          }
        };

        bind(newScore, document.querySelector("#app"));
        
    }

    function displayMessage(message){
        data.message = message;
    }

    function updateBar(value){
        bar = value;
    }
    
    function updateShotClock(value){
        data.shotClock = value;
    }

    // function updateGameClock(value){
    //     let number = new Number(value)
    //     let str = format(number)
    //     bindings.gameClock = str;
    // }

    function clearMessage(){
        data.message = "";
    }
//#endregion